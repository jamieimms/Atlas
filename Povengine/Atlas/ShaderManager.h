#pragma once
#include <string>
#include <vector>

#include "../AtlasUtil/AtlasLog.h"


namespace Atlas
{
	//class Shader
	//{
	//public:
	//	unsigned int _id;
	//	unsigned int _internalID;
	//};

	class ShaderManager
	{
	public:
		ShaderManager(AtlasUtil::AtlasLog* log, std::string basePath);
		~ShaderManager();

		// OpenGL
		unsigned int LoadShader(std::string& vertexShaderFilename, std::string& fragmentShaderFilename);

		unsigned int GetShaderAtIndex(unsigned int index);

	private:

		std::string ReadShaderFile(std::string& filename);
		
		/// OpenGL
		unsigned int CompileShader(unsigned int shaderType, const char* source, int sourceLen, std::string& shaderName);

		std::string _basePath;

		AtlasUtil::AtlasLog* _log;

		std::vector<unsigned int> _loadedShaders;
	};
}