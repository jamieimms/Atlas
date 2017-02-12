#include "Cube.h"
#include "glew.h"

using namespace Atlas;

///
Cube::Cube(float size, glm::vec3 pos, unsigned int shaderProgramID)
	:PhysicsEntity(pos, shaderProgramID)
{
	_entityType = EntityTypeEnum::ET_Cube;

	_size = size;

	Initialise(DataFormatEnum::DataColourTexNorm);
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

		16, 17, 18,
		18, 19, 16,

		20, 21 , 22,
		22, 23, 20,
	};

	_numVertices = 24;
	_data = new float[_numVertices * _dataFormat]{

		-_size, -_size, -_size, 1.0f, 0.0f, 0.0f,	0.0f, 0.0f,		0.0f, 0.0f, -1.0f, 	// 0
		_size, -_size, -_size,  1.0f, 0.0f, 0.0f,	1.0f, 0.0f,		0.0f, 0.0f, -1.0f,	// 1
		_size,  _size, -_size,  1.0f, 0.0f, 0.0f,	1.0f, 1.0f,		0.0f, 0.0f, -1.0f,	// 2
		-_size,  _size, -_size, 1.0f, 0.0f, 0.0f,	0.0f, 1.0f,		0.0f, 0.0f, -1.0f,	// 3

		-_size, -_size,  _size,  0.0f, 1.0f, 0.0f,	0.0f, 0.0f,		0.0f, 0.0f, 1.0f,	// 4
		_size, -_size,  _size,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f,		0.0f, 0.0f, 1.0f,	// 5
		_size,  _size,  _size,   0.0f, 1.0f, 0.0f,	1.0f, 1.0f,		0.0f, 0.0f, 1.0f,	// 6
		-_size,  _size,  _size,  0.0f, 1.0f, 0.0f,	0.0f, 1.0f,		0.0f, 0.0f, 1.0f,	// 7

		-_size,  _size,  _size, 0.0f, 1.0f, 0.0f,	0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,	// 7 - 8
		-_size,  _size, -_size, 1.0f, 0.0f, 0.0f,	1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,	// 3 - 9
		-_size, -_size, -_size, 1.0f, 0.0f, 0.0f,	1.0f, 1.0f,		-1.0f, 0.0f, 0.0f,	// 0 - 10
		-_size, -_size, _size, 1.0f, 0.0f, 0.0f,	0.0f, 1.0f,		-1.0f, 0.0f, 0.0f,	// 4 - 11

		_size,  _size,  _size,  0.0f, 1.0f, 0.0f,	0.0f, 0.0f,		1.0f, 0.0f, 0.0f,	// 6 - 12
		_size,  _size, -_size,  1.0f, 0.0f, 0.0f,	1.0f, 0.0f,		1.0f, 0.0f, 0.0f,	// 2 - 13
		_size, -_size, -_size,  1.0f, 0.0f, 0.0f,	1.0f, 1.0f,		1.0f, 0.0f, 0.0f,	// 1 - 14
		_size, -_size,  _size,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f,		1.0f, 0.0f, 0.0f,	// 5 - 15

		-_size, -_size, -_size, 1.0f, 0.0f, 0.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f, 	// 0
		_size, -_size, -_size,  1.0f, 0.0f, 0.0f,	1.0f, 0.0f,		0.0f, -1.0f, 0.0f,	// 1
		_size, -_size,  _size,  0.0f, 1.0f, 0.0f,   1.0f, 1.0f,	    0.0f, -1.0f, 0.0f,	// 5 - 18
		-_size, -_size, _size, 1.0f, 0.0f, 0.0f,	0.0f, 1.0f,		0.0f, -1.0f, 0.0f,	// 4 - 19

		-_size,  _size, -_size,   1.0f, 0.0f, 0.0f,	0.0f, 0.0f,		0.0f, 1.0f, 0.0f,	// 3 - 20
		_size,  _size, -_size,  1.0f, 0.0f, 0.0f,	1.0f, 0.0f,		0.0f, 1.0f, 0.0f,	// 2 - 21
		_size,  _size,  _size,   0.0f, 1.0f, 0.0f,	1.0f, 1.0f,		0.0f, 1.0f, 0.0f,	// 6
		-_size,  _size,  _size,  0.0f, 1.0f, 0.0f,	0.0f, 1.0f,		0.0f, 1.0f, 0.0f,	// 7
	};

	_material.ambientColour = glm::vec3(0.0f, 0.08f, 0.34f);
	_material.diffuseColour = glm::vec3(0.0f, 0.45f, 1.0f);
	_material.specularColour = glm::vec3(0.78, 0.88, 1.0f);
	_material.shininess = 32.0f;

}