#include "Origin.h"
#include "glew.h"

using namespace Atlas;

///
Origin::Origin(float size, unsigned int shaderProgramID)
	:Transformable(0, 0, 0), _data(nullptr), _shaderProgramID(shaderProgramID)
{

	SetUniformScale(size);

	int numVertices = 6;
	// An array of 3 vectors which represents 3 vertices
	_data = new float[numVertices * 6] {
		// Pos			// Colours
		0, 0, 0,		1.0f, 0.0f, 0.0f,
		1.0f, 0,0,		1.0f, 0.0f, 0.0f,
		0, 0, 0,		0.0f, 1.0f, 0.0f,
		0, 1.0f, 0,		0.0f, 1.0f, 0.0f,
		0, 0, 0,		0.0f, 0.0f, 1.0f,
		0, 0, 1.0f,		0.0f, 0.0f, 1.0f,
	};

	glGenVertexArrays(1, &_vbaID);
	glBindVertexArray(_vbaID);

	glGenBuffers(1, &_vbID);
	glBindBuffer(GL_ARRAY_BUFFER, _vbID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (numVertices*6), _data, GL_STATIC_DRAW);

	_transformLoc = glGetUniformLocation(_shaderProgramID, "transform");
}

Origin::~Origin()
{
	delete[] _data;
}

void Origin::Render()
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
		(void*)(3*sizeof(float))
	);
	glEnableVertexAttribArray(1);

	glUseProgram(_shaderProgramID);

	SetRenderTransform(_transformLoc);

	glDrawArrays(GL_LINES, 0, 6);

	glDisableVertexAttribArray(0);
}