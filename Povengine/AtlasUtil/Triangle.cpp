#include "Triangle.h"

using namespace AtlasUtil::Primitives;

Triangle::Triangle(float x, float y, float z)
	:_vertices(nullptr)
{
	_vertices = new Vertex[3];
	
	_vertices[0].x = -1.0f; 	
	_vertices[0].y = -1.0f;
	_vertices[0].z = 0.0f;
	_vertices[1].x = 1.0f;
	_vertices[1].y = -1.0f;
	_vertices[1].z = 0.0f;
	_vertices[2].x = 0.0f; 
	_vertices[2].y = 1.0f; 
	_vertices[2].z = 0.0f;
}

Triangle::~Triangle()
{
	delete[] _vertices;
}