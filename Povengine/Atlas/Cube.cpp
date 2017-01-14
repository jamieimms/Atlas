#include "Cube.h"
#include "glew.h"

using namespace Atlas;

///
Cube::Cube(float size, float x, float y, float z, unsigned int shaderProgramID)
	:BaseEntity(x, y, z, shaderProgramID)
{
	SetUniformScale(size);

	Initialise();
}

void Cube::InitData()
{
	_numIndices = 36;
	_indices = new unsigned short[_numIndices]
	{
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		7, 3, 0,
		0, 4, 7,

		6, 2, 1,
		1, 5, 6,

		0, 1, 5,
		5, 4, 0,

		3, 2, 6,
		6, 7, 3
	};

	_numVertices = 8;
	// An array of 3 vectors which represents 3 vertices
	_data = new float[_numVertices * 6]{

		-0.25f, -0.25f, -0.25f, 1.0f, 0.0f, 0.0f,	// 0
		0.25f, -0.25f, -0.25f,  1.0f, 0.0f, 0.0f,	// 1
		0.25f,  0.25f, -0.25f, 1.0f, 0.0f, 0.0f,	// 2
		-0.25f,  0.25f, -0.25f,   1.0f, 0.0f, 0.0f,	// 3

		-0.25f, -0.25f,  0.25f,   0.0f, 1.0f, 0.0f,	// 4
		0.25f, -0.25f,  0.25f,   0.0f, 1.0f, 0.0f,	// 5
		0.25f,  0.25f,  0.25f,  0.0f, 1.0f, 0.0f,	// 6
		-0.25f,  0.25f,  0.25f,  0.0f, 1.0f, 0.0f,	// 7
	};
}