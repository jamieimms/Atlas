#include "Cube.h"
#include "glew.h"

using namespace Atlas;

///
Cube::Cube(float size, glm::vec3 pos, unsigned int shaderProgramID)
	:PhysicsEntity(pos, shaderProgramID)
{
	_entityType = EntityTypeEnum::ET_Cube;

	_size = size;

	Initialise(DataFormatEnum::DataColourTex);
}

Cube::~Cube() {}

void Cube::InitData()
{
	_numIndices = 36;

	_indices = new unsigned short[_numIndices]
	{
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		0, 1, 16,
		16, 11, 0,

		17, 13, 6,
		6, 7, 17,
	};

	_numVertices = 18;
	_data = new float[_numVertices * _dataFormat]{

		-_size, -_size, -_size, 1.0f, 0.0f, 0.0f,	0.0f, 0.0f,	// 0
		_size, -_size, -_size,  1.0f, 0.0f, 0.0f,	1.0f, 0.0f,	// 1
		_size,  _size, -_size,  1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	// 2
		-_size,  _size, -_size, 1.0f, 0.0f, 0.0f,	0.0f, 1.0f,	// 3

		-_size, -_size,  _size,  0.0f, 1.0f, 0.0f,	0.0f, 0.0f,	// 4
		_size, -_size,  _size,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f,	// 5
		_size,  _size,  _size,   0.0f, 1.0f, 0.0f,	1.0f, 1.0f,	// 6
		-_size,  _size,  _size,  0.0f, 1.0f, 0.0f,	0.0f, 1.0f,	// 7

		-_size,  _size,  _size, 0.0f, 1.0f, 0.0f,	0.0f, 0.0f,	// 7 - 8
		-_size,  _size, -_size, 1.0f, 0.0f, 0.0f,	1.0f, 0.0f,	// 3 - 9
		-_size, -_size, -_size, 1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	// 0 - 10
		-_size, -_size, _size, 1.0f, 0.0f, 0.0f,	0.0f, 1.0f,	// 4 - 11

		_size,  _size,  _size,  0.0f, 1.0f, 0.0f,	0.0f, 0.0f,	// 6 - 12
		_size,  _size, -_size,  1.0f, 0.0f, 0.0f,	1.0f, 0.0f,	// 2 - 13
		_size, -_size, -_size,  1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	// 1 - 14
		_size, -_size,  _size,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f,	// 5 - 15

		_size, -_size,  _size,   0.0f, 1.0f, 0.0f,  1.0f, 1.0f,	// 5 - 16

		-_size,  _size, -_size,   1.0f, 0.0f, 0.0f,	0.0f, 0.0f,	// 3 - 17
	};
}