#include "Text.h"

#include "glew.h"

namespace Atlas
{
	Text::Text(std::string text, float x, float y, Font* font, Shader* shader)
		: BaseEntity(0,0,0, shader), _initialised(false), _font(font), _x(x), _y(y)
	{
		_entityType = EntityTypeEnum::ET_Plane;

		Initialise(DataFormatEnum::DataColourTex);

		SetText(text);
	}

	Text::~Text()
	{

	}

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

		_identity = glm::mat4();
		ComputeMatrix(1024, 768);
	}

	///
	///
	void Text::ComputeMatrix(float windowWidth, float windowHeight)
	{
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glOrtho(0.f, 1024, 768, 0.f, 0.f, 1.f);
		glGetFloatv(GL_PROJECTION_MATRIX, glm::value_ptr(_textProjection));
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

		float scaleFactor = 3.0f;
		int stepX = _x;

		for (int i = 0; i < _glyphIndices.size(); i++) {

			auto glyph = _font->GetGlyph(_glyphIndices[i]);

			if (glyph->Width == 0 && glyph->Height == 0) {
				stepX += (glyph->Advance >> 6) / scaleFactor;
				continue;
			}

			float width = glyph->Width / scaleFactor;
			float height = (glyph->Height / scaleFactor);
			float yOffset = (glyph->Top / scaleFactor);
			float xOffset = (glyph->Left / scaleFactor);

			UpdateGlyphSize(width, height);
			SetTexture(_font->GetTexture(_glyphIndices[i]));
			
			SetPosition(stepX + xOffset, _y - height + (height - yOffset), 0);

			BaseEntity::Render(_identity, _textProjection, glm::vec3(0, 0, 0), lights);

			stepX += (glyph->Advance >> 6) / scaleFactor;
		}

		glDisable(GL_BLEND);
		glPopMatrix();
	}

	///
	///
	void Text::SetText(std::string& text)
	{
		Fonts::StringToGlyph(text, _glyphIndices, _font);
	}
}