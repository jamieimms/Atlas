#pragma once
#include "PhysicsEntity.h"
#include "LightTypeEnum.h"

namespace Atlas
{
	class Light
	{
	public:

		Light(LightTypeEnum type);
		Light(LightTypeEnum type, float r, float g, float b);
		Light(LightTypeEnum type, float r, float g, float b, float x, float y, float z);

		virtual ~Light();

		glm::vec3 GetColour() { return _lightColour; }
		glm::vec3 GetPosition() { return _position; }
		LightTypeEnum GetType() { return _type; }

		void SetPosition(glm::vec3& pos) { _position = pos; }

	private:

		LightTypeEnum _type;

		glm::vec3 _lightColour;
		glm::vec3 _position;

	};
}