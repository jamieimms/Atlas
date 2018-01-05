#pragma once

#include "Fonts.h"
#include "IRenderable.h"
#include "Shader.h"
#include "Plane.h"
#include "Sprite.h"

namespace Atlas
{
	class Text : public Sprite
	{
	public:
		Text(std::string text, float x, float y , Font* fonts, Shader* shader, glm::vec3 colour, TextAlignmentEnum horizontalAlignment, TextAlignmentEnum verticalAlignment);
		virtual ~Text();

		virtual void Render(glm::mat4& view, glm::mat4& proj, glm::vec3& cameraPos, std::vector<Light*>& lights);

		void SetText(std::string& text);
		void AdjustAlignment(const unsigned int containerWidth, const unsigned int containerHeight);

	private:

		std::vector<unsigned int> _glyphIndices;	// The string is converted into indices into the glyphs array

		float _x;
		float _y;

		float _xAlignOffset;
		float _yAlignOffset;

		unsigned int _totalWidth;
		unsigned int _totalHeight;

		TextAlignmentEnum _horizontalAlignment;
		TextAlignmentEnum _verticalAlignment;

		Font* _font;

		void UpdateGlyphSize(float width, float height);

	};
}