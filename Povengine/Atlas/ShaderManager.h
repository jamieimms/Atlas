#pragma once
#include <string>
#include <vector>

#include "BaseManager.h"
#include "../AtlasUtil/AtlasLog.h"


namespace Atlas
{
	class Shader
	{
	public:
		unsigned int _atlasID;
		std::string name;

		unsigned int _id;
	};


	class ShaderManager : protected BaseManager
	{
	public:
		ShaderManager(AtlasUtil::AtlasLog* log, std::string basePath);
		~ShaderManager();

		// OpenGL
		unsigned int LoadShader(std::string& shaderName);

		unsigned int GetShaderAtIndex(unsigned int index);
		unsigned int GetShaderByName(std::string& shaderName);

	private:

		std::string ReadShaderFile(std::string& filename);
		
		/// OpenGL
		unsigned int CompileShader(unsigned int shaderType, const char* source, int sourceLen, std::string& shaderName);

		std::string _basePath;

		std::vector<Shader*> _loadedShaders;
	};
}