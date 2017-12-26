#include "Text.h"

#include "glew.h"

namespace Atlas
{
	Texel::Texel(Shader* shader)
		:BaseEntity(0,0,0,shader)
	{
		_entityType = EntityTypeEnum::ET_Plane;

		Initialise(DataFormatEnum::DataColourTex);
	}

	/// <summary>
	///	Initialise the vertex and index data for a plane.
	/// </summary>
	void Texel::InitData()
	{
		_width = 1;
		_height = 1;
		_numIndices = 6;
		_indices = new unsigned short[_numIndices]
		{
			0, 1, 2,
			2, 3, 0,
		};

		_numVertices = 4;
		// An array of 3 vectors which represents 3 vertices
		_data = new float[_numVertices * _dataFormat]{
			_width, _height, 0,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f,
			0, _height, 0,		0.0f, 1.0f, 0.0f,		0.0f, 1.0f,
			0, 0, 0,		0.0f, 0.0f, 1.0f,		0.0f, 0.0f,
			_width, 0, 0,		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,
		};
	}

	void Texel::SetSize(float width, float height)
	{
		if (_data != nullptr) {
			delete[] _data;
		}

		if (width == 0) {
			width = 1;
		} 
		if (height == 0) {
			height = 1;
		}

		_width = width;
		_height = height;

		_data = new float[_numVertices * _dataFormat]{
			_width, _height, 0,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f,
			0, _height, 0,		0.0f, 1.0f, 0.0f,		0.0f, 1.0f,
			0, 0, 0,		0.0f, 0.0f, 1.0f,		0.0f, 0.0f,
			_width, 0, 0,		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,
		};
		ReloadData();
	}

	Text::Text()
		:_initialised(false)
	{
	}

	Text::~Text()
	{

	}

	///
	///
	void Text::init(std::string& text, float x, float y, Shader* shader)
	{
		auto error = FT_Init_FreeType(&_ftLib);
		if (error) {
			return;
		}

		std::string fontPath = AtlasAPI::AtlasAPIHelper::GetDataPath() + "Roboto-Regular.ttf";

		if (FT_New_Face(_ftLib, fontPath.c_str(), 0, &_ftFace)) {
			return;
		}

		if (error == FT_Err_Unknown_File_Format)
		{
			return;
		}
		else if (error)
		{
			return;
		}

		if (_ftFace->charmap == nullptr) {
			// If charmap is null, this font doesn't have a unicode charmap so forget about it
			return;
		}

		SetFontSize(48);

		_x = x;
		_y = y;

		_textureIDs = new unsigned int[_ftFace->num_glyphs];
		glGenTextures(_ftFace->num_glyphs, _textureIDs);

		// Load all the character textures
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			for (int i = 0; i < _ftFace->num_glyphs; i++) {
				error = FT_Load_Glyph(_ftFace, i, FT_LOAD_RENDER);

				if (error) {
					return;
				}

				GlyphMetrics* metrics = new GlyphMetrics();
				metrics->Width = _ftFace->glyph->bitmap.width;
				metrics->Height = _ftFace->glyph->bitmap.rows;
				metrics->Left = _ftFace->glyph->bitmap_left;
				metrics->Top = _ftFace->glyph->bitmap_top;
				metrics->Advance = _ftFace->glyph->advance.x;

				_glyphs.push_back(metrics);

				glBindTexture(GL_TEXTURE_2D, _textureIDs[i]);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, _ftFace->glyph->bitmap.width, _ftFace->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, _ftFace->glyph->bitmap.buffer);

				glBindTexture(GL_TEXTURE_2D, 0);
			}

		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		
		_texel = new Texel(shader);
		_texel->InitData();

		SetText(text);

		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glOrtho(0.f, 1024, 768, 0.f, 0.f, 1.f);
		glGetFloatv(GL_PROJECTION_MATRIX, glm::value_ptr(_textProjection));

		_identity = glm::mat4();

		_initialised = true;
	}

	///
	///
	void Text::SetFontSize(const int sz)
	{
		FT_Set_Pixel_Sizes(_ftFace, 0, sz);
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

			auto glyph = _glyphs[_glyphIndices[i]];

			if (glyph->Width == 0 && glyph->Height == 0) {
				stepX += (glyph->Advance >> 6) / scaleFactor;
				continue;
			}

			float width = glyph->Width / scaleFactor;
			float height = (glyph->Height / scaleFactor);
			float yOffset = (glyph->Top / scaleFactor);
			float xOffset = (glyph->Left / scaleFactor);

			_texel->SetSize(width, height);
			_texel->SetTexture(_textureIDs[_glyphIndices[i]]);
			_texel->SetPosition(stepX + xOffset, _y - height + (height - yOffset), 0);// -(height - yOffset), 0);

			_texel->Render(_identity, _textProjection, glm::vec3(0,0,0), lights);
			stepX += (glyph->Advance >> 6) / scaleFactor;
		}

		glDisable(GL_BLEND);
		glPopMatrix();
	}

	///
	///
	void Text::SetText(std::string& text)
	{
		_glyphIndices.clear();

		for (int i = 0; i < text.length(); i++) {
			_glyphIndices.push_back(FT_Get_Char_Index(_ftFace, text[i]));
		}
	}
}