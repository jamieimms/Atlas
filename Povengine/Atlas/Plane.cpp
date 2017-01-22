#include "Plane.h"
#include "glew.h"

using namespace Atlas;

///
Plane::Plane(float size, float x, float y, float z, unsigned int shaderProgramID)
	:BaseEntity(x, y, z, shaderProgramID)
{
	_dataFormat = DataFormatEnum::DataColourTex;

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
		-1.0f, 0, -1.0f,	1.0f, 0.0f, 0.0f,		1.0f, 0.0f,
		1.0f, 0, -1.0f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f,
		1.0f, 0, 1.0f,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f,
		-1.0f, 0, 1.0f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f
	};

	//// Set up vertex data (and buffer(s)) and attribute pointers
	//_data = new float[_numVertices * _dataFormat] {
	//	// Positions          // Colors           // Texture Coords
	//	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
	//	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
	//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
	//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
	//};
	//_indices = new unsigned short[_numIndices] {  // Note that we start from 0!
	//	0, 1, 3, // First Triangle
	//	1, 2, 3  // Second Triangle
	//};
}