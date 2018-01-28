#include "Mesh.h"
#include "glew.h"
#include <random>
#include "..\AtlasAPI\AtlasAPIHelper.h"

using namespace Atlas;

///
Mesh::Mesh(std::string& meshName, std::vector<glm::vec3>* vertices, std::vector<glm::vec3>* normals, std::vector<unsigned short>* vertexIndices, std::vector<unsigned short>* normalIndices, glm::vec3 colour, Shader* shader)
	:BaseEntity(0, 3, 0, shader)
	//:PhysicsEntity(pos, shader)
{
	_entityType = EntityTypeEnum::ET_Mesh;

	_id = meshName;

	_size = 1;

	_numIndices = vertexIndices->size();

	_numVertices = _numIndices;
	
	_dataFormat = DataFormatEnum::DataTexNorm;

	_data = new float[_numIndices * _dataFormat];

	//_indices = new unsigned short[_numIndices];
	int index = 0;
	for (int i = 0; i < _numIndices; i++) {
		unsigned short vIndex = (*vertexIndices)[i];

		_data[index++] = (*vertices)[vIndex].x;
		_data[index++] = (*vertices)[vIndex].y;
		_data[index++] = (*vertices)[vIndex].z;

		// Tex
		_data[index++] = 0.0f;
		_data[index++] = 0.0f;

		unsigned short nIndex = (*normalIndices)[i];
		// Normals
		_data[index++] = (*normals)[nIndex].x;
		_data[index++] = (*normals)[nIndex].y;
		_data[index++] = (*normals)[nIndex].z;
	}

	_material.diffuseColour = colour;

	Initialise(DataFormatEnum::DataTexNorm);
}

Mesh::~Mesh() 
{

}

void Mesh::InitData()
{
	_material.specularColour = glm::vec3(0.8f, 0.8f, 0.8f);
	_material.ambientColour = glm::vec3(_material.diffuseColour.r * 0.25f, _material.diffuseColour.g * 0.25f, _material.diffuseColour.b * 0.25f);
	_material.shininess = 24.0f;

}