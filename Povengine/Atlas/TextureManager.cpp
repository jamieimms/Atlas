#include "TextureManager.h"
#include "glew.h"
#include "..\AtlasUtil\ImageLoader.h"

using namespace Atlas;


TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
	FlushTextures();
}

unsigned int TextureManager::LoadTexture(std::string& path)
{
	if (IsLoaded(path)) {
		return GetTextureID(path);
	}

	AtlasTexture* tex = new AtlasTexture();

	glGenTextures(1, &tex->TextureID);
	glBindTexture(GL_TEXTURE_2D, tex->TextureID);
	// Set wrapping mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	std::vector<unsigned char> texData;

	unsigned int w, h;
	AtlasUtil::ImageLoader::LoadPNGImage(path, texData, w, h);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, &texData[0]);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	_loadedTextures.push_back(tex);

	return tex->TextureID;
}

void TextureManager::UnloadTexture(AtlasTexture* texture)
{
	// OpenGL texture deinit

	delete texture;
}

void TextureManager::FlushTextures()
{
	while (_loadedTextures.size() > 0) {
		auto item = _loadedTextures.front();
		UnloadTexture(item);
		_loadedTextures.pop_front();
	}
}


bool TextureManager::IsLoaded(std::string& path)
{
	for (auto it : _loadedTextures) {
		if (it->Path == path) {
			return true;
		}
	}

	return false;
}


unsigned int TextureManager::GetTextureID(std::string& path)
{
	for (auto it : _loadedTextures) {
		if (it->Path == path) {
			return true;
		}
	}

	return -1;
}