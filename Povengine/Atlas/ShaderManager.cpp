#include "ShaderManager.h"
#include "glew.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "IO.h"
#include "..\AtlasAPI\AtlasAPIHelper.h"

using namespace Atlas;
//using namespace AtlasUtil;

ShaderManager::ShaderManager(AtlasUtil::AtlasLog* log, std::string basePath)
	: BaseManager(log), _basePath(basePath)
{

}

ShaderManager::~ShaderManager()
{
	while (_loadedShaders.size() > 0) {
		auto shader = _loadedShaders[_loadedShaders.size() - 1];
		glDeleteProgram(shader->glProgramID);
		_loadedShaders.pop_back();
		delete shader;
	}
}

///
///
unsigned int ShaderManager::LoadShader(const std::string& shaderName)
{
	std::string basePath = IO::GetShaderDirectory();
	std::string vertexShaderName = shaderName + " vertex";
	std::string fragmentShaderName = shaderName + " fragment";
	unsigned int vertexShaderLen = 0;
	unsigned int fragmentShaderLen = 0;

	std::string vertexShaderCode;
	AtlasAPI::AtlasAPIHelper::LoadTextFile(basePath + shaderName + ".vert", vertexShaderCode);

	std::string fragmentShaderCode;
	AtlasAPI::AtlasAPIHelper::LoadTextFile(basePath + shaderName + ".frag", fragmentShaderCode);

	auto vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderCode.c_str(), vertexShaderCode.length(), vertexShaderName);
	auto fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderCode.c_str(), fragmentShaderCode.length(), fragmentShaderName);

	int linkResult = 0;
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkResult);

	if (linkResult == GL_FALSE) {
		// Collapse in heap; cry.
		return 0;
	}

	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	Shader* shader = new Shader();
	shader->name = shaderName;
	shader->atlasID = _loadedShaders.size();
	shader->glProgramID = shaderProgram;

	// Populate the uniforms
	shader->texLoc = glGetUniformLocation(shader->glProgramID, "outTexture1");

	shader->viewLoc = glGetUniformLocation(shader->glProgramID, "view");
	shader->projLoc = glGetUniformLocation(shader->glProgramID, "projection");

	shader->modelLoc = glGetUniformLocation(shader->glProgramID, "model");

	// Lighting variables
	shader->objectColour = glGetUniformLocation(shader->glProgramID, "objectColour");
	shader->positionalLightColour = glGetUniformLocation(shader->glProgramID, "lightColour");
	shader->positionalLightPos = glGetUniformLocation(shader->glProgramID, "lightPos");
	shader->viewerPos = glGetUniformLocation(shader->glProgramID, "viewPos");

	shader->ambientLightColour = glGetUniformLocation(shader->glProgramID, "ambientColour");

	_loadedShaders.push_back(shader);

	return shaderProgram;
}

///
///
std::string ShaderManager::ReadShaderFile(const std::string& filename)
{
	_log->Debug("Loading shader file: " + filename);

	unsigned int fileLen = 0;

	std::ifstream file(filename, std::ios::in);

	if (!file.good()) {
		//throw Exception
		return "";
	}

	std::stringstream ss;
	ss << file.rdbuf();

	file.close();

	return ss.str();
}

///
///
unsigned int ShaderManager::CompileShader(unsigned int shaderType, const char* source, int sourceLen, const std::string& shaderName)
{
	_log->Debug("Compiling shader " + shaderName);

	int compileResult = 0;

	unsigned int shader = glCreateShader(shaderType);

	glShaderSource(shader, 1, &source, &sourceLen);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
	int errorLogLength = 0;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorLogLength);
	if (errorLogLength > 0) {
		char *errorMsg = new char[errorLogLength];
		int outLen = 0;
		glGetShaderInfoLog(shader, errorLogLength, &outLen, errorMsg);
		_log->Error(errorMsg);

		delete[] errorMsg;
	}

	//check for errors
	if (compileResult == GL_FALSE)
	{
		return 0;
	}

	return shader;
}

Shader* ShaderManager::GetShaderAtIndex(unsigned int index)
{
	if (index > _loadedShaders.size()) {
		return nullptr;
	}
	else {
		return _loadedShaders[index];
	}
}

Shader* ShaderManager::GetShaderByName(const std::string& shaderName)
{
	for (auto shader : _loadedShaders) {
		if (shader->name == shaderName) {
			return shader;
		}
	}

	return nullptr;
}