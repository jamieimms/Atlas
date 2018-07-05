#pragma once
#include "ft2build.h"
#include FT_FREETYPE_H

#include <vector>

#include "Font.h"
#include "..\AtlasAPI\AtlasAPIHelper.h"
#include "BaseManager.h"

namespace Atlas
{
	class Fonts : public BaseManager
	{
	public:
		Fonts(AtlasUtil::AtlasLog* log);
		virtual ~Fonts();

		bool Initialise();

		bool LoadFont(std::string fontPath, FontStyleEnum style);

		static void StringToGlyph(const std::string& text, std::vector<unsigned int>& glyphIndices, const Font* font, unsigned int& width, unsigned int& height);

		Font* GetFont(FontStyleEnum style);

	private:

		FT_Library _ftLib;

		std::vector<Font*> _loadedFonts;

	};
}