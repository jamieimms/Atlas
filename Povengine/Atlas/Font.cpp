#include "glew.h"

#include "Font.h"

using namespace Atlas;

Font::Font(unsigned int id, FT_Face face, FontStyleEnum style)
	: _id(id), _ftFace(face), _style(style)
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

/// <summary>
/// Goes through the entire font face loading all glyphs into memory
/// </summary>
/// <param name="keyID">The freetype font face to load glyphs from</param>
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

/// <summary>
/// Gets the glyph metrics corresponding to the given glyph index
/// </summary>
/// <param name="index">glyph index to retrieve</param>
const GlyphMetrics* Font::GetGlyph(const unsigned int index)
{
	if (index < 0 || index > _glyphs.size()) {
		return nullptr;
	}

	return _glyphs[index];
}

/// <summary>
/// Gets the texture id corresponding to the given glyph index
/// </summary>
/// <param name="index">glyph index to retrieve</param>
unsigned int Font::GetTexture(const unsigned int index) const
{
	if (index < 0 || index > _glyphs.size()) {
		return -1;
	}

	return _textureIDs[index];
}

/// <summary>
/// Gets the glyph index corresponding to the given character code
/// </summary>
/// <param name="character">character to retrieve the glyph index for</param>
unsigned int Font::GetGlyphIndex(const char character) const
{
	return FT_Get_Char_Index(_ftFace, character);
}

/// <summary>
/// Get whether or not this font matches the given family and style.
/// </summary>
/// <param name="fontFamily">The font family to check for. This can be a wildcard "*" to ignore the family</param>
/// <param name="style">the style the caller is looking for</param>
bool Font::IsFamilyAndStyle(std::string& fontFamily, FontStyleEnum style)
{
	if (style != _style) {
		return false;
	}

	return fontFamily == "*" || fontFamily == _name;
}

const unsigned int Font::GetGlyphWidth(const unsigned int index) const
{
	if (index < 0 || index > _glyphs.size()) {
		return 0;
	}

	return _glyphs[index]->Advance >> 6;
}

const unsigned int Font::GetGlyphHeight(const unsigned int index) const
{
	if (index < 0 || index > _glyphs.size()) {
		return 0;
	}

	return _glyphs[index]->Top;
}