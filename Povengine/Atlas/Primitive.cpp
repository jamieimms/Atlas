#include "Primitive.h"
#include "glew.h"

using namespace Atlas;

///
Primitive::Primitive(float size, float x, float y, float z, unsigned int shaderProgramID)
	:Transformable(x, y, z), _data(nullptr), _shaderProgramID(shaderProgramID)
{

	SetUniformScale(size);

	int numVertices = 9;
	// An array of 3 vectors which represents 3 vertices
	_data = new float[numVertices] {
		-0.5f, -0.5f, 0,
	     0, 0.5f, 0,
		 0.5f, -0.5f, 0
	};

	glGenVertexArrays(1, &_vbaID);
	glBindVertexArray(_vbaID);

	glGenBuffers(1, &_vbID);
	glBindBuffer(GL_ARRAY_BUFFER, _vbID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertices, _data, GL_STATIC_DRAW);

	_transformLoc = glGetUniformLocation(_shaderProgramID, "transform");
}

Primitive::~Primitive()
{
	delete[] _data;
}

void Primitive::Render()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vbID);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glUseProgram(_shaderProgramID);

	SetRenderTransform(_transformLoc);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	

	glDisableVertexAttribArray(0);
}