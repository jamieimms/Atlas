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

		bool LoadFont(std::string fontPath);

		static void StringToGlyph(std::string& text, std::vector<unsigned int>& glyphIndices, const Font* font);

		Font* GetFont(unsigned int index) { return _loadedFonts[index]; }


	private:

		FT_Library _ftLib;

		std::vector<Font*> _loadedFonts;

	};
}