#include "Cone.h"

#include "glew.h"
#include "glm.hpp"

using namespace Atlas;

Cone::Cone(int quality, float size, float x, float y, float z, unsigned int shaderProgramID)
	:BaseEntity(x, y, z, shaderProgramID)
{
	_quality = quality<1 ? 1 : quality;
	SetUniformScale(size);

	Initialise();
}


void Cone::InitData()
{
	int sides = 4 * _quality;

	float angleStep = 90.0f / _quality;

	_numVertices = sides + 2;
	_numIndices = (4 * 3 * _quality) * 2;

	// Allocate memory
	_data = new float[_numVertices * 6]{
			0, 1.0f, 0,		1.0f, 1.0f, 1.0f,	// top centre
			0, 0, 0,		1.0f, 1.0f, 1.0f	// base centre
	};

	_indices = new unsigned short[_numIndices];

	int dataPos = 12;

	float s;
	float c;

	// corner vertices
	SetVertex(dataPos, 0.0f, 0.0f, 1.0f, 1.0f, 0, 0);
	SetVertex(dataPos, 1.0f, 0.0f, 0.0f, 0, 1.0f, 0);
	SetVertex(dataPos, 0.0f, 0.0f, -1.0f, 0, 0, 1.0f);
	SetVertex(dataPos, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0);

	float currentAngle = angleStep;
	// Now calculate the positions of the vertices. We only need to do this for a 90 degree arc, we can just reverse the signs for each quadrant
	for (int i = 1; i < _quality; i++) {
		s = sin(glm::radians(currentAngle));
		c = cos(glm::radians(currentAngle));
		SetVertex(dataPos, s, 0.0f, c, 1.0f, 0, 0);
		SetVertex(dataPos, c, 0.0f, -s, 0, 1.0f, 0);	// Invert angle
		SetVertex(dataPos, -s, 0.0f, -c, 0, 0, 1.0f);
		SetVertex(dataPos, -c, 0.0f, s, 1.0f, 1.0f, 0);
		currentAngle += angleStep;
	}

	int indexPos = 0;
	int vertexPos = 2;	// Start at the first side vertex

	for (int i = 0; i < _quality; i++) {
		if (vertexPos + 4 == _numVertices) {
			// Handle the final triangles that needs to connect to the next quadrant
			SetIndex(indexPos, 0, vertexPos, 3);
			SetIndex(indexPos, 0, vertexPos + 1, 4);
			SetIndex(indexPos, 0, vertexPos + 2, 5);
			SetIndex(indexPos, 0, vertexPos + 3, 2);
			SetIndex(indexPos, 1, vertexPos, 3);
			SetIndex(indexPos, 1, vertexPos + 1, 4);
			SetIndex(indexPos, 1, vertexPos + 2, 5);
			SetIndex(indexPos, 1, vertexPos + 3, 2);
		}
		else {
			for (int j = 0; j < 4; j++) {
				SetIndex(indexPos, 0, vertexPos, vertexPos + 4);
				SetIndex(indexPos, 1, vertexPos, vertexPos + 4);
				vertexPos++;
			}
		}
	}
}
