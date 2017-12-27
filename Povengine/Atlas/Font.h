#pragma once
#include "ft2build.h"
#include FT_FREETYPE_H

#include <string>
#include <vector>

namespace Atlas
{
	///
	///
	struct GlyphMetrics
	{
		unsigned int Index;
		unsigned int Width;
		unsigned int Height;
		unsigned int Top;
		unsigned int Left;
		unsigned int Advance;
	};

	///
	///
	class Font
	{
	public:
		Font(unsigned int id, FT_Face face);
		virtual ~Font();

		const GlyphMetrics* GetGlyph(const unsigned int index);
		unsigned int GetTexture(const unsigned int index) const;
		unsigned int GetGlyphIndex(const char character) const;


	private:
		unsigned int _id;
		std::string _name;
		std::vector<GlyphMetrics*> _glyphs;
		unsigned int* _textureIDs;
		unsigned int _glyphCount;

		FT_Face _ftFace;

		bool AddFontGlyphs(FT_Face face);
	};
}