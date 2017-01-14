#include "BaseEntity.h"

#include "glew.h"

using namespace Atlas;


BaseEntity::BaseEntity(float x, float y, float z, unsigned int shaderID)
	: Transformable(x,y,z), _shaderProgramID(shaderID)
{

	SetUniformScale(1.0f);

	_modelLoc = glGetUniformLocation(_shaderProgramID, "model");

	_mode = GL_TRIANGLES;

	_indices = nullptr;
	_ibaID = -1;
}

void BaseEntity::Initialise()
{
	InitData();
	glGenVertexArrays(1, &_vbaID);
	glBindVertexArray(_vbaID);

	glGenBuffers(1, &_vbID);
	glBindBuffer(GL_ARRAY_BUFFER, _vbID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (_numVertices * 6), _data, GL_STATIC_DRAW);

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


void BaseEntity::Render(glm::mat4 view, glm::mat4 proj)
{
	glBindBuffer(GL_ARRAY_BUFFER, _vbID);

	// Pos
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(float),
		(void*)0
	);
	glEnableVertexAttribArray(0);

	// Colour
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(float),
		(void*)(3 * sizeof(float))
	);
	glEnableVertexAttribArray(1);

	glUseProgram(_shaderProgramID);

	auto viewLoc = glGetUniformLocation(_shaderProgramID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	auto projLoc = glGetUniformLocation(_shaderProgramID, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

	SetRenderTransform(_modelLoc);

	if (_indices == nullptr) {
		glDrawArrays(_mode, 0, _numVertices);
	}
	else {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibaID);

		glDrawElements(GL_TRIANGLES, _numIndices, GL_UNSIGNED_SHORT, (void*)0);
	}

	glDisableVertexAttribArray(0);
}
