#include "BaseEntity.h"

#include "glew.h"
#include "..\AtlasUtil\ImageLoader.h"
#include "Light.h"

using namespace Atlas;

BaseEntity::BaseEntity()
	: Transformable(glm::vec3())
{
}

BaseEntity::BaseEntity(glm::vec3 pos, Shader* shader)
	: Transformable(pos), _shader(shader)
{
	SetUniformScale(1.0f);
}

BaseEntity::BaseEntity(float x, float y, float z, Shader* shader)
	: Transformable(x,y,z), _shader(shader)
{
	SetUniformScale(1.0f);
}

void BaseEntity::Initialise(DataFormatEnum dataFormat)
{
	_dead = false;
	_dataFormat = dataFormat;

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

	SetVisibility(true);
}


BaseEntity::~BaseEntity()
{
	glDeleteBuffers(1, &_ibaID);
	glDeleteBuffers(1, &_vbID);
	glDeleteVertexArrays(1, &_vbaID);
	delete[] _indices;
	delete[] _data;
}

void BaseEntity::Update()
{

}

void BaseEntity::Render(glm::mat4& view, glm::mat4& proj, glm::vec3& cameraPos, std::vector<Light*>& lights)
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

	glUseProgram(_shader->glProgramID);

	if (_dataFormat == DataFormatEnum::DataColourTex || _dataFormat == DataFormatEnum::DataColourTexNorm) {
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
		glUniform1i(_shader->texLoc, 0);
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

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _texID);
		glUniform1i(_shader->texLoc, 0);
	}

	glUniformMatrix4fv(_shader->viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(_shader->projLoc, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(_shader->modelLoc, 1, GL_FALSE, glm::value_ptr(GetTransform()));

	glUniform3f(_shader->objectColour, _material.diffuseColour.r, _material.diffuseColour.g, _material.diffuseColour.b);

	auto temp = lights[0]->GetColour();

	glUniform3f(_shader->ambientLightColour, temp.r, temp.g, temp.b);

	temp = lights[1]->GetColour();
	glUniform3f(_shader->positionalLightColour, temp.r, temp.g, temp.b);
	temp = lights[1]->GetPosition();
	glUniform3f(_shader->positionalLightPos, temp.x, temp.y, temp.z);
	glUniform3f(_shader->viewerPos, cameraPos.x, cameraPos.y, cameraPos.z);

	if (_indices == nullptr) {
		glDrawArrays(_mode, 0, _numVertices);
	}
	else {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibaID);

		glDrawElements(_mode, _numIndices, GL_UNSIGNED_SHORT, (void*)0);
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
