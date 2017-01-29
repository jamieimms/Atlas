#include "Sphere.h"

#include "glew.h"
#include "glm.hpp"


using namespace Atlas;

Sphere::Sphere(int segments, int rings, float size, float x, float y, float z, unsigned int shaderProgramID)
	:BaseEntity(x, y, z, shaderProgramID)
{
	_segs = segments < 4 ? 4 : segments;
	_rings = rings < 4 ? 4 : rings;

	SetUniformScale(size);

	Initialise();
}

void Sphere::InitData()
{

	//int sides = 4 * _quality;

	float segAngleStep = 360.0f / _segs;
	float ringAngleStep = 360.0f / _rings;

	_numVertices = _segs * _rings + 2;
	//_numIndices = (4 * 3 * _quality) * 2;

	_numVertices = 2;

	int dataPos = 0;
	// Allocate memory
	_data = new float[_numVertices * 6];
	SetVertex(dataPos, 0, 1.0f, 0, 1.0f, 1.0f, 1.0f);	// top centre
	SetVertex(dataPos, 0, -1.0f, 0, 1.0f, 1.0f, 1.0f);	// bot centre

	//_indices = new unsigned short[_numIndices];

	float s;
	float c;

	float ringAngle = 0;
	for (int i = 0; i < _rings; i++) {
		s = sin(glm::radians(ringAngle));	// x
		c = cos(glm::radians(ringAngle));	// y
	}

	//float currentAngle = angleStep;
	//// Now calculate the positions of the vertices. We only need to do this for a 90 degree arc, we can just reverse the signs for each quadrant
	//for (int i = 1; i < _quality; i++) {
	//	s = sin(glm::radians(currentAngle));
	//	c = cos(glm::radians(currentAngle));
	//	SetVertex(dataPos, s, 0.0f, c, 1.0f, 0, 0);
	//	SetVertex(dataPos, c, 0.0f, -s, 0, 1.0f, 0);	// Invert angle
	//	SetVertex(dataPos, -s, 0.0f, -c, 0, 0, 1.0f);
	//	SetVertex(dataPos, -c, 0.0f, s, 1.0f, 1.0f, 0);
	//	currentAngle += angleStep;
	//}

	//int indexPos = 0;
	//int vertexPos = 2;	// Start at the first side vertex

	//for (int i = 0; i < _quality; i++) {
	//	if (vertexPos + 4 == _numVertices) {
	//		// Handle the final triangles that needs to connect to the next quadrant
	//		SetIndex(indexPos, 0, vertexPos, 3);
	//		SetIndex(indexPos, 0, vertexPos + 1, 4);
	//		SetIndex(indexPos, 0, vertexPos + 2, 5);
	//		SetIndex(indexPos, 0, vertexPos + 3, 2);
	//		SetIndex(indexPos, 1, vertexPos, 3);
	//		SetIndex(indexPos, 1, vertexPos + 1, 4);
	//		SetIndex(indexPos, 1, vertexPos + 2, 5);
	//		SetIndex(indexPos, 1, vertexPos + 3, 2);
	//	}
	//	else {
	//		for (int j = 0; j < 4; j++) {
	//			SetIndex(indexPos, 0, vertexPos, vertexPos + 4);
	//			SetIndex(indexPos, 1, vertexPos, vertexPos + 4);
	//			vertexPos++;
	//		}
	//	}
	//}
}