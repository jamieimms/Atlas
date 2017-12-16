#include "Text.h"

#include "glew.h"

namespace Atlas
{
	Text::Text(Shader* shader)
		:_initialised(false)
	{
		_shader = shader;
	}


	void Text::init(std::string& text, float x, float y)
	{
		auto error = FT_Init_FreeType(&_ftLib);
		if (error) {
			return;
		}

		std::string fontPath = AtlasAPI::AtlasAPIHelper::GetDataPath() + "Roboto-Regular.ttf";

		FT_New_Face(_ftLib, fontPath.c_str(), 0, &_ftFace);

		if (error == FT_Err_Unknown_File_Format)
		{
			return;
		}
		else if (error)
		{
			return;
		}

		FT_GlyphSlot g = _ftFace->glyph;

		SetFontSize(48);

		// OpenGL Init
		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &_texID);
		glBindTexture(GL_TEXTURE_2D, _texID);
		// Set wrapping mode
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// Set texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		//glUniform1i(_shader->texLoc, 0);

		glGenBuffers(1, &_vbo);

		_text = text;
		_x = 10;
		_y = 10;

		_initialised = true;
	}

	void Text::SetFontSize(const int sz)
	{
		FT_Set_Pixel_Sizes(_ftFace, 0, sz);
	}

	void Text::LoadChar(const char c)
	{
		auto error = FT_Load_Char(_ftFace, c, FT_LOAD_RENDER);
	}

	void Text::Render(glm::mat4& view, glm::mat4& proj, glm::vec3& cameraPos, std::vector<Light*>& lights)
	{
		float sx = 2.0 / 800;
		float sy = 2.0 / 600;
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		float x = _x, y = _y;
		for (auto i = _text.begin(); i != _text.end(); i++) {
			LoadChar(*i);

			//glTexImage2D(GL_TEXTURE_2D,
			//	0, GL_RED,
			//	_ftFace->glyph->bitmap.width,
			//	_ftFace->glyph->bitmap.rows,
			//	0,
			//	GL_RED,
			//	GL_UNSIGNED_BYTE,
			//	_ftFace->glyph->bitmap.buffer);

			float x2 = x + _ftFace->glyph->bitmap_left * sx;
			float y2 = -y - _ftFace->glyph->bitmap_top * sy;
			float w = _ftFace->glyph->bitmap.width * sx;
			float h = _ftFace->glyph->bitmap.rows * sy;

			float box[4][4] = {
				{ x2,     -y2   , 0, 0 },
				{ x2 + w, -y2   , 1, 0 },
				{ x2,     -y2 - h, 0, 1 },
				{ x2 + w, -y2 - h, 1, 1 },
			};

			glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, box + 2);
			glEnableVertexAttribArray(1);

			glDrawArrays(GL_TRIANGLE_STRIP, 0, 2);

			x += (_ftFace->glyph->advance.x / 64) * sx;
			y += (_ftFace->glyph->advance.y / 64) * sy;
		}


		glDisable(GL_BLEND);
	}


	void Text::SetText(std::string& text)
	{
		_text = text;
		
	}
}