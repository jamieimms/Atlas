#include "Sphere.h"

#include "glew.h"

using namespace Atlas;

Sphere::Sphere(float size, float x, float y, float z, unsigned int shaderProgramID)
	:BaseEntity(x, y, z, shaderProgramID)
{
	SetUniformScale(size);

	Initialise();
}

void Sphere::InitData()
{
	int segments = 4;



	_numVertices = 6;

	_data = new float[_numVertices * 6]
	{
		0, 0.5f, 0,		1.0f, 0.0f, 1.0f,

		0, 0, -0.5f,		1.0f, 1.0f, 1.0f,
		0.5f, 0, 0,		1.0f, 1.0f, 1.0f,
		0, 0, 0.5f,		1.0f, 1.0f, 1.0f,
		-0.5f, 0, 0,		1.0f, 1.0f, 1.0f,

		0, -0.5f, 0,		0.0f, 1.0f, 1.0f,
	};

	_numIndices = 24;
	_indices = new unsigned short[_numIndices]
	{
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 1,

		5, 2, 1,
		5, 3, 2,
		5, 4, 3,
		5, 1, 4
	};
}