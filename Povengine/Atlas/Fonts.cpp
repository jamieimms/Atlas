#include "Fonts.h"
#include "glew.h"

using namespace Atlas;


///
///
Fonts::Fonts(AtlasUtil::AtlasLog* log)
	: BaseManager(log)
{
	Initialise();
}

///
///
Fonts::~Fonts()
{
	for (auto it : _loadedFonts) {
		delete it;
	}
	_loadedFonts.clear();

	FT_Done_FreeType(_ftLib);
}

///
///
bool Fonts::Initialise()
{
	FT_Error error;

	error = FT_Init_FreeType(&_ftLib);
	if (error) {
		_log->Error("Failed to intialise FreeType library.");
		return false;
	}

	_initialised = true;

	return true;
}

///
///
bool Fonts::LoadFont(std::string fontPath, FontStyleEnum style)
{
	if (!_initialised) {
		return false;
	}

	FT_Error error;
	FT_Face face;

	error = FT_New_Face(_ftLib, fontPath.c_str(), 0, &face);
	if(error != FT_Err_Ok) {
		_log->Error("Failed to load font: " + fontPath + ". Error code: " + std::to_string(error));
		return false;
	}

	if (face->charmap == nullptr) {
		// If charmap is null, this font doesn't have a unicode charmap so forget about it
		_log->Error("Failed to load font. Only fonts with Unicode charmap are supported.");
		return false;
	}

	// Check if this font is already loaded and if so just return
	for (auto f : _loadedFonts) {
		if (f->IsFamilyAndStyle(std::string(face->family_name), style)) {
			return true;
		}
	}

	unsigned int fontSize = 12;
	switch (style) {
	case FontStyleEnum::XSmall:
		fontSize = 6;
		break;
	case FontStyleEnum::Small:
		fontSize = 8;
		break;
	case FontStyleEnum::Medium:
		fontSize = 14;
		break;
	case FontStyleEnum::Large:
		fontSize = 18;
		break;
	case FontStyleEnum::XLarge:
		fontSize = 32;
		break;
	case FontStyleEnum::Title:
		fontSize = 64;
	}

	FT_Set_Pixel_Sizes(face, 0, fontSize);

	Font* loadedFont = new Font(_loadedFonts.size()+1, face, style);

	_loadedFonts.push_back(loadedFont);

	return true;
}

///
///
void Fonts::StringToGlyph(const std::string& text, std::vector<unsigned int>& glyphIndices, const Font* font, unsigned int& width, unsigned int& height)
{
	glyphIndices.clear();

	for (int i = 0; i < text.length(); i++) {
		unsigned int index = font->GetGlyphIndex(text[i]);
		glyphIndices.push_back(index);

		width += font->GetGlyphWidth(index);
		auto glyphHeight = font->GetGlyphHeight(index);
		if (glyphHeight > height) {
			height = glyphHeight;
		}
	}
}

///
///
Font* Fonts::GetFont(FontStyleEnum style)
{
	// Check if this font is already loaded and if so just return
	for (auto f : _loadedFonts) {
		if (f->IsFamilyAndStyle(std::string("*"), style)) {
			return f;
		}
	}
}