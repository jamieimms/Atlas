#include "Light.h"

using namespace Atlas;

Light::Light(float r, float g, float b, float brightness, Shader* shader)
	: PhysicsEntity(0,0,0,shader)
{
	_size = 0.2f;

	_lightColour.r = r;
	_lightColour.g = g;
	_lightColour.b = b;

	Initialise(DataFormatEnum::DataColour);
}


Light::~Light()
{

}

void Light::InitData()
{
	// Just represent lights with a cube

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
	_data = new float[_numVertices * _dataFormat]{

		-_size, -_size, -_size, _lightColour.r, _lightColour.g,_lightColour.b,	// 0
		_size, -_size, -_size,  _lightColour.r, _lightColour.g,_lightColour.b,	// 1
		_size,  _size, -_size,  _lightColour.r, _lightColour.g,_lightColour.b,  // 2
		-_size,  _size, -_size, _lightColour.r, _lightColour.g,_lightColour.b,	// 3

		-_size, -_size,  _size,  _lightColour.r, _lightColour.g,_lightColour.b,	// 4
		_size, -_size,  _size,   _lightColour.r, _lightColour.g,_lightColour.b,	// 5
		_size,  _size,  _size,  _lightColour.r, _lightColour.g,_lightColour.b,	// 6
		-_size,  _size,  _size,  _lightColour.r, _lightColour.g,_lightColour.b,	// 7
	};
}