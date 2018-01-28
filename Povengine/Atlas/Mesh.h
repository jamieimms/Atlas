#pragma once
#include "PhysicsEntity.h"

namespace Atlas
{
	class Mesh : public BaseEntity
	{
	public:
		Mesh(std::string& meshName, std::vector<glm::vec3>* vertices, std::vector<glm::vec3>* normals, std::vector<unsigned short>* vertexIndices, std::vector<unsigned short>* normalIndices, glm::vec3 colour, Shader* shader);
		virtual ~Mesh();

		virtual void InitData();

	private:
	};
}