#include "TextureManager.h"
#include "glew.h"
#include "..\AtlasUtil\ImageLoader.h"

using namespace Atlas;


TextureManager::TextureManager(AtlasUtil::AtlasLog* log)
	: BaseManager(log)
{
	_loadedTextures = new std::list<AtlasTexture*>();
}

TextureManager::~TextureManager()
{
	FlushTextures();

	delete _loadedTextures;
}

/// <summary>
/// Load the texture with the given path or returns the texture ID if it is already loaded into memory
/// </summary>
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

	switch (GetTextureType(path)) {
	case Unsupported:
		return -1;
	case PNG:
		AtlasUtil::ImageLoader::LoadPNGImage(path, texData, w, h);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, &texData[0]);
		break;
	case JPG:
		AtlasUtil::ImageLoader::LoadJPGImage(path, texData, w, h);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, &texData[0]);
		break;
	}

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	_loadedTextures->push_back(tex);

	return tex->TextureID;
}

/// <summary>
/// Gets the texture type (PNG,JPG) based on the file name
/// </summary>
TextureType TextureManager::GetTextureType(std::string& path)
{
	auto index = path.find_last_of('.');
	auto extension = path.substr(index + 1);

	if (extension == "png") {
		return TextureType::PNG;
	}
	else if (extension == "jpg" || extension == "jpeg") {
		return TextureType::JPG;
	}

	return TextureType::Unsupported;
}

/// <summary>
/// Unloads a given texture and frees the memory associated with it.
/// </summary>
void TextureManager::UnloadTexture(AtlasTexture* texture)
{
	if (texture != nullptr) {
		glDeleteTextures(1, &texture->TextureID);
	}

	delete texture;
}

/// <summary>
/// Unloads and deallocates all currently loaded textures
/// </summary>
void TextureManager::FlushTextures()
{
	while (_loadedTextures->size() > 0) {
		auto item = _loadedTextures->front();
		if (item != nullptr) {
			UnloadTexture(item);
		}
		_loadedTextures->pop_front();
	}
}

/// <summary>
/// Go through the loaded textures and remove any items that have been deleted.
/// </summary>
void TextureManager::DefragmentTextures()
{
	auto defrag = new std::list<AtlasTexture*>();
	while (_loadedTextures->size() > 0) {
		auto item = _loadedTextures->front();
		if (item != nullptr) {
			defrag->push_front(item);
		}
		_loadedTextures->pop_front();
	}
	
	delete _loadedTextures;

	_loadedTextures = defrag;
}

/// <summary>
/// Check if the given texture is already loaded
/// </summary>
bool TextureManager::IsLoaded(std::string& path)
{
	for (auto it : *_loadedTextures) {
		if (it == nullptr) {
			continue;
		}
		if (it->Path == path) {
			return true;
		}
	}

	return false;
}

/// <summary>
/// Gets the internal id of the given texture file path
/// </summary>
unsigned int TextureManager::GetTextureID(std::string& path)
{
	for (auto it : *_loadedTextures) {
		if (it == nullptr) {
			continue;
		}

		if (it->Path == path) {
			return true;
		}
	}

	return -1;
}