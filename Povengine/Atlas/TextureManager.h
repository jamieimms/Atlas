#pragma once
#include "BaseManager.h"

#include <list>

namespace Atlas
{
	enum TextureType {
		Unsupported,
		PNG,
		JPG
	};

	class AtlasTexture
	{
	public:
		std::string Path;
		unsigned int TextureID;
	};

	class TextureManager : protected BaseManager
	{

	public:
		TextureManager(AtlasUtil::AtlasLog* log);
		virtual ~TextureManager();


		unsigned int LoadTexture(std::string& path);

		void FlushTextures();

		bool IsLoaded(std::string& path);
		unsigned int GetTextureID(std::string& path);

	private:
		void UnloadTexture(AtlasTexture* textureID);
		TextureType GetTextureType(std::string& path);


		std::list<AtlasTexture*> _loadedTextures;
	};

}