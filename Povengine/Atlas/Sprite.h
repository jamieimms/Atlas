#pragma once

#include "Fonts.h"
#include "IRenderable.h"
#include "Shader.h"
#include "Plane.h"

namespace Atlas
{
	class Text : public BaseEntity
	{
	public:
		Text(std::string text, float x, float y, Font* fonts, Shader* shader);
		virtual ~Text();

		virtual void InitData();

		virtual void Render(glm::mat4& view, glm::mat4& proj, glm::vec3& cameraPos, std::vector<Light*>& lights);

	private:

		bool _initialised;

		std::vector<unsigned int> _glyphIndices;	// The string is converted into indices into the glyphs array

		float _x;
		float _y;

		glm::mat4 _identity;

		Font* _font;

		void UpdateGlyphSize(float width, float height);

	};
}