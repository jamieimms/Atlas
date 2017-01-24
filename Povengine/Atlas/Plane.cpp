#include "Plane.h"
#include "glew.h"

using namespace Atlas;

///
Plane::Plane(float size, float x, float y, float z, unsigned int shaderProgramID)
	:BaseEntity(x, y, z, shaderProgramID)
{
	_dataFormat = DataFormatEnum::DataColourTex;
	_size = size;

	SetUniformScale(size);

	Initialise();
}

void Plane::InitData()
{
	_numIndices = 6;
	_indices = new unsigned short[_numIndices]
	{
			0, 1, 2,
			2, 3, 0,
	};

	_numVertices = 4;
	// An array of 3 vectors which represents 3 vertices
	_data = new float[_numVertices * _dataFormat] {
		-1.0f, 0, -1.0f,	1.0f, 0.0f, 0.0f,		_size * 1.0f, 0.0f,
		1.0f, 0, -1.0f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f,
		1.0f, 0, 1.0f,		0.0f, 0.0f, 1.0f,		0.0f, _size * 1.0f,
		-1.0f, 0, 1.0f,		1.0f, 1.0f, 1.0f,		_size * 1.0f, _size * 1.0f
	};
}