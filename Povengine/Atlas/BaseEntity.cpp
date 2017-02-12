#include "BaseEntity.h"

#include "glew.h"
#include "..\AtlasUtil\ImageLoader.h"

using namespace Atlas;

BaseEntity::BaseEntity(glm::vec3 pos, unsigned int shaderID)
	: Transformable(pos), _shaderProgramID(shaderID)
{
	SetUniformScale(1.0f);
}

BaseEntity::BaseEntity(float x, float y, float z, unsigned int shaderID)
	: Transformable(x,y,z), _shaderProgramID(shaderID)
{
	SetUniformScale(1.0f);
}

void BaseEntity::Initialise(DataFormatEnum dataFormat)
{
	_dataFormat = dataFormat;
	_texLoc = glGetUniformLocation(_shaderProgramID, "outTexture1");

	_viewLoc = glGetUniformLocation(_shaderProgramID, "view");
	_projLoc = glGetUniformLocation(_shaderProgramID, "projection");

	_modelLoc = glGetUniformLocation(_shaderProgramID, "model");

	// Lighting variables
	_objectColour = glGetUniformLocation(_shaderProgramID, "objectColour");
	_positionalLightColour = glGetUniformLocation(_shaderProgramID, "lightColour");
	_positionalLightPos = glGetUniformLocation(_shaderProgramID, "lightPos");
	_viewerPos = glGetUniformLocation(_shaderProgramID, "viewPos");

	_mode = GL_TRIANGLES;

	_indices = nullptr;
	_ibaID = -1;

	InitData();
	glGenVertexArrays(1, &_vbaID);
	glBindVertexArray(_vbaID);

	glGenBuffers(1, &_vbID);
	glBindBuffer(GL_ARRAY_BUFFER, _vbID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (_numVertices * ((int)_dataFormat)), _data, GL_STATIC_DRAW);

	if (_indices != nullptr) {
		glGenBuffers(1, &_ibaID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibaID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * _numIndices, _indices, GL_STATIC_DRAW);
	}
}


BaseEntity::~BaseEntity()
{
	delete[] _indices;
	delete[] _data;
}


void BaseEntity::Render(glm::mat4 view, glm::mat4 proj, glm::vec3 cameraPos)
{
	int format = (int)_dataFormat;
	glBindBuffer(GL_ARRAY_BUFFER, _vbID);

	// Pos
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		format * sizeof(float),
		(void*)0
	);
	glEnableVertexAttribArray(0);

	if (_dataFormat == DataFormatEnum::DataColour || _dataFormat == DataFormatEnum::DataColourTex) {
		// Colour
		glVertexAttribPointer(
			1,
			3,
			GL_FLOAT,
			GL_FALSE,
			format * sizeof(float),
			(void*)(3 * sizeof(float))
		);
		glEnableVertexAttribArray(1);
	}


	glUseProgram(_shaderProgramID);

	if (_dataFormat == DataFormatEnum::DataColourTex) {
		glVertexAttribPointer(
			2,
			2,
			GL_FLOAT,
			GL_FALSE,
			format * sizeof(float),
			(void*)(6 * sizeof(float))
		);
		glEnableVertexAttribArray(2);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _texID);
		glUniform1i(_texLoc, 0);
	}

	if (_dataFormat == DataFormatEnum::DataColourTexNorm) {
		glVertexAttribPointer(
			3,
			3,
			GL_FLOAT,
			GL_FALSE,
			format * sizeof(float),
			(void*)(8 * sizeof(float)));
		glEnableVertexAttribArray(3);
	}

	glUniformMatrix4fv(_viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(_projLoc, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(_modelLoc, 1, GL_FALSE, glm::value_ptr(GetTransform()));

	glUniform3f(_objectColour, _material.diffuseColour.r, _material.diffuseColour.g, _material.diffuseColour.b);

	//glUniform3f(_objectColour, 1.0f, 0.5f, 0.31f);
	glUniform3f(_positionalLightColour, 1.0f, 1.0f, 1.0f);
	glUniform3f(_positionalLightPos, 0.0f, 5.0f, 0.0f);
	glUniform3f(_viewerPos, cameraPos.x, cameraPos.y, cameraPos.z);

	if (_indices == nullptr) {
		glDrawArrays(_mode, 0, _numVertices);
	}
	else {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibaID);

		glDrawElements(GL_TRIANGLES, _numIndices, GL_UNSIGNED_SHORT, (void*)0);
	}

	glDisableVertexAttribArray(0);
}

void BaseEntity::SetVertex(int &dataPos, float x, float y, float z, float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
	// Vertex position
	_data[dataPos++] = x;
	_data[dataPos++] = y;
	_data[dataPos++] = z;

	// Colour
	_data[dataPos++] = r;
	_data[dataPos++] = g;
	_data[dataPos++] = b;
}

void BaseEntity::SetIndex(int &indexPos, unsigned short a, unsigned short b, unsigned short c)
{
	_indices[indexPos++] = a;
	_indices[indexPos++] = b;
	_indices[indexPos++] = c;
}
