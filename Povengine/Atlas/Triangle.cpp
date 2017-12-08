#include "Triangle.h"
#include "glew.h"

using namespace Atlas;

///
Triangle::Triangle(float size, float x, float y, float z, Shader* shader)
	:BaseEntity(x, y, z, shader)
{
	_entityType = EntityTypeEnum::ET_Triangle;

	SetUniformScale(size);

	Initialise(DataFormatEnum::Data);
}

void Triangle::InitData()
{
	_numVertices = 3;
	// An array of 3 vectors which represents 3 vertices
	_data = new float[_numVertices * 3]{
		-0.5f, -0.5f, 0,
		0, 0.5f, 0,
		0.5f, -0.5f, 0
	};
}