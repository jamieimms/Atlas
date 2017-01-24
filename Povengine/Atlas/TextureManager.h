#pragma once
#include "BaseManager.h"

#include <list>

namespace Atlas
{
	class AtlasTexture
	{
	public:
		std::string Path;
		unsigned int TextureID;
	};

	class TextureManager : protected BaseManager
	{

	public:
		TextureManager();
		virtual ~TextureManager();


		unsigned int LoadTexture(std::string& path);

		void FlushTextures();

		bool IsLoaded(std::string& path);
		unsigned int GetTextureID(std::string& path);

	private:
		void UnloadTexture(AtlasTexture* textureID);


		std::list<AtlasTexture*> _loadedTextures;
	};

}