#include "Text.h"

#include "glew.h"

namespace Atlas
{
	Text::Text(std::string text, float x, float y, Font* font, Shader* shader, glm::vec3 colour, TextAlignmentEnum horizontalAlignment, TextAlignmentEnum verticalAlignment)
		: BaseEntity(0,0,0, shader), _initialised(false), _font(font), _x(x),_y(y), _horizontalAlignment(horizontalAlignment), _verticalAlignment(verticalAlignment)
	{
		_entityType = EntityTypeEnum::ET_Plane;

		Initialise(DataFormatEnum::DataColourTex);

		_material.diffuseColour = glm::vec3(colour.r, colour.g, colour.b);

		SetText(text);
	}

	Text::~Text()
	{

	}

	///
	///
	void Text::InitData()
	{
		_numIndices = 6;
		_indices = new unsigned short[_numIndices]
		{
			0, 1, 2,
			2, 3, 0,
		};

		_numVertices = 4;
		// An array of 3 vectors which represents 3 vertices
		_data = new float[_numVertices * _dataFormat]{
			1, 1, 0,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f,
			0, 1, 0,		0.0f, 1.0f, 0.0f,		0.0f, 1.0f,
			0, 0, 0,		0.0f, 0.0f, 1.0f,		0.0f, 0.0f,
			1, 0, 0,		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,
		};
	}

	///
	///
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
		_data[9] = height;
		_data[24] = width;

		ReloadData();
	}

	///
	///
	void Text::Render(glm::mat4& view, glm::mat4& proj, glm::vec3& cameraPos, std::vector<Light*>& lights)
	{
		// Enable blending so we only render the glyph
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		float scaleFactor = 1.0f;
		int stepX = _x;

		for (int i = 0; i < _glyphIndices.size(); i++) {

			auto glyph = _font->GetGlyph(_glyphIndices[i]);

			if (glyph->Width == 0 && glyph->Height == 0) {
				stepX += (glyph->Advance >> 6) / scaleFactor;
				continue;
			}

			float width = glyph->Width / scaleFactor;
			float height = (glyph->Height / scaleFactor);
			float yOffset = _yAlignOffset + (glyph->Top / scaleFactor);
			float xOffset = _xAlignOffset + (glyph->Left / scaleFactor);

			UpdateGlyphSize(width, height);
			SetTexture(_font->GetTexture(_glyphIndices[i]));
			
			SetPosition(stepX + xOffset, _y - height + (height - yOffset), 0);

			BaseEntity::Render(view, proj, glm::vec3(0, 0, 0), lights);

			stepX += (glyph->Advance >> 6) / scaleFactor;
		}

		glDisable(GL_BLEND);
		glPopMatrix();
	}

	///
	///
	void Text::SetText(std::string& text)
	{
		_totalWidth = 0;
		_totalHeight = 0;
		Fonts::StringToGlyph(text, _glyphIndices, _font, _totalWidth, _totalHeight);
	}

	///
	///
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