#pragma once
#include <string>

#include "../AtlasUtil/AtlasLog.h"


namespace Atlas
{
	class ShaderManager
	{
	public:
		ShaderManager(AtlasUtil::AtlasLog* log, std::string basePath);
		~ShaderManager();

		// OpenGL
		unsigned int CreateShaderProgram(std::string& vertexShaderFilename, std::string& fragmentShaderFilename);

		unsigned int GetShaderProgramID() { return _shaderProgramID; }

	private:

		std::string ReadShaderFile(std::string& filename);
		
		/// OpenGL
		unsigned int CompileShader(unsigned int shaderType, const char* source, int sourceLen, std::string& shaderName);

		std::string _basePath;

		AtlasUtil::AtlasLog* _log;

		unsigned int _shaderProgramID;
	};
}