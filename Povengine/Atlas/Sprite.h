#pragma once

#include "Fonts.h"
#include "IRenderable.h"
#include "Shader.h"
#include "Plane.h"

namespace Atlas
{
	class Sprite : public BaseEntity
	{
	public:
		Sprite(float x, float y, float width, float height, Shader* shader);
		Sprite(float x, float y, float width, float height, Shader* shader, glm::vec3 colour);
		virtual ~Sprite();

		virtual void InitData();
		virtual void Render(glm::mat4& view, glm::mat4& proj, glm::vec3& cameraPos, std::vector<Light*>& lights);

		virtual void AdjustAlignment(const unsigned int containerWidth, const unsigned int containerHeight);

		void SetColour(glm::vec3 newColour);

	protected:
		float _x;
		float _y;

		float _width;
		float _height;
	};
}