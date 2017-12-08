#pragma once
#include <string>
#include <vector>

#include "BaseManager.h"
#include "../AtlasUtil/AtlasLog.h"

#include "Shader.h"

namespace Atlas
{
	class ShaderManager : protected BaseManager
	{
	public:
		ShaderManager(AtlasUtil::AtlasLog* log, std::string basePath);
		~ShaderManager();

		// OpenGL
		unsigned int LoadShader(const std::string& shaderName);

		Shader* GetShaderAtIndex(unsigned int index);
		Shader* GetShaderByName(const std::string& shaderName);

	private:

		std::string ReadShaderFile(const std::string& filename);
		
		/// OpenGL
		unsigned int CompileShader(unsigned int shaderType, const char* source, int sourceLen, const std::string& shaderName);

		std::string _basePath;

		std::vector<Shader*> _loadedShaders;
	};
}