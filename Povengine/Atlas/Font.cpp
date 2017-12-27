#include "glew.h"

#include "Font.h"

using namespace Atlas;

Font::Font(unsigned int id, FT_Face face)
	: _id(id), _ftFace(face)
{
	_glyphCount = face->num_glyphs;
	_textureIDs = new unsigned int[_glyphCount];

	_glyphs.reserve(_glyphCount);

	this->_name = face->family_name;

	AddFontGlyphs(face);
}

///
///
Font::~Font()
{
	delete[] _textureIDs;
}

///
///
bool Font::AddFontGlyphs(FT_Face face)
{
	FT_Error error;

	glGenTextures(_glyphCount, _textureIDs);

	// Load all the character textures
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (int i = 0; i < face->num_glyphs; i++) {
		error = FT_Load_Glyph(face, i, FT_LOAD_RENDER);

		if (error) {
			return false;
		}

		GlyphMetrics* metrics = new GlyphMetrics();
		metrics->Width = face->glyph->bitmap.width;
		metrics->Height = face->glyph->bitmap.rows;
		metrics->Left = face->glyph->bitmap_left;
		metrics->Top = face->glyph->bitmap_top;
		metrics->Advance = face->glyph->advance.x;

		_glyphs.push_back(metrics);

		glBindTexture(GL_TEXTURE_2D, _textureIDs[i]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

///
//
const GlyphMetrics* Font::GetGlyph(const unsigned int index)
{
	if (index < 0 || index > _glyphs.size()) {
		return nullptr;
	}

	return _glyphs[index];
}

///
///
unsigned int Font::GetTexture(const unsigned int index) const
{
	if (index < 0 || index > _glyphs.size()) {
		return -1;
	}

	return _textureIDs[index];
}

///
///
unsigned int Font::GetGlyphIndex(const char character) const
{
	return FT_Get_Char_Index(_ftFace, character);
}