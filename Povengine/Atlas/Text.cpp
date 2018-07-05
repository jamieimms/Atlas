#include "Text.h"

#include "glew.h"

namespace Atlas
{
	Text::Text(std::string text, float x, float y, Font* font, Shader* shader, glm::vec3 colour, TextAlignmentEnum horizontalAlignment, TextAlignmentEnum verticalAlignment)
		: Sprite(0, 0, 1, 1, shader, colour), _font(font), _x(x), _y(y), _horizontalAlignment(horizontalAlignment), _verticalAlignment(verticalAlignment)
	{
		SetText(text);
	}

	Text::~Text()
	{

	}

	/// <summary>
	// Update the underlying sprite size to ensure correct display of the next character
	/// </summary>
	void Text::UpdateGlyphSize(float width, float height)
	{
		if (width == 0) {
			width = 1;
		} 
		if (height == 0) {
			height = 1;
		}

		_data[0] = width;
		_data[1] = height;
		_data[6] = height;
		_data[15] = width;

		ReloadData();
	}

	/// <summary>
	// Render the text string
	/// </summary>
	void Text::Render(glm::mat4& view, glm::mat4& proj, glm::vec3& cameraPos, std::vector<Light*>& lights)
	{
		// Enable blending so we only render the glyph
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		float scaleFactorX = GetScaleX();
		float scaleFactorY = GetScaleY();
		int stepX = _x;

		for (int i = 0; i < _glyphIndices.size(); i++) {

			auto glyph = _font->GetGlyph(_glyphIndices[i]);

			if (glyph->Width == 0 && glyph->Height == 0) {
				stepX += (glyph->Advance >> 6) * scaleFactorX;
				continue;
			}

			float width = glyph->Width * scaleFactorX;
			float height = glyph->Height * scaleFactorY;
			float yOffset = _yAlignOffset + (glyph->Top * scaleFactorY);
			float xOffset = _xAlignOffset + (glyph->Left * scaleFactorX);

			UpdateGlyphSize(width, height);
			SetTexture(_font->GetTexture(_glyphIndices[i]));
			
			SetPosition(stepX + xOffset, _y - height + (height - yOffset), 0);

			BaseEntity::Render(view, proj, cameraPos, lights);

			stepX += (glyph->Advance >> 6) / scaleFactorX;
		}

		glDisable(GL_BLEND);
	}

	/// <summary>
	// Sets the text string of this text object; this is done by converting the string characters into
	// glyph indices.
	/// </summary>
	void Text::SetText(const std::string& text)
	{
		_totalWidth = 0;
		_totalHeight = 0;
		Fonts::StringToGlyph(text, _glyphIndices, _font, _totalWidth, _totalHeight);
	}

	/// <summary>
	// Adjust the alignment of text. This needs to be called whenever the container dimensions change
	/// </summary>
	void Text::AdjustAlignment(const unsigned int containerWidth, const unsigned int containerHeight)
	{
		_xAlignOffset = 0;
		_yAlignOffset = 0;

		if (_horizontalAlignment == TextAlignmentEnum::Centre) {
			_xAlignOffset = containerWidth / 2.0f - _totalWidth / 2.0f;
		}
		else if (_horizontalAlignment == TextAlignmentEnum::Right) {
			_xAlignOffset = containerWidth - _totalWidth;
		}

		//if (_verticalAlignment == TextAlignmentEnum::Centre) {
		//	_yAlignOffset = containerHeight / 2.0f - _totalHeight / 2.0f;
		//}
		//else if (_verticalAlignment == TextAlignmentEnum::Bottom) {
		//	_yAlignOffset = containerHeight - _totalHeight;
		//}

	}

}