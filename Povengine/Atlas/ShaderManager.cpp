#include "ShaderManager.h"
#include "glew.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace Atlas;
//using namespace AtlasUtil;

ShaderManager::ShaderManager(AtlasUtil::AtlasLog* log, std::string basePath)
	:_log(log), _basePath(basePath), _shaderProgramID(-1)
{

}

ShaderManager::~ShaderManager()
{

}

///
///
unsigned int ShaderManager::CreateShaderProgram(std::string& vertexShaderFilename, std::string& fragmentShaderFilename)
{
	std::string vertexShaderName = "vertex shader";
	std::string fragmentShaderName = "fragment shader";
	unsigned int vertexShaderLen = 0;
	unsigned int fragmentShaderLen = 0;
	auto vertexShaderCode = ReadShaderFile(vertexShaderFilename);
	auto fragmentShaderCode = ReadShaderFile(fragmentShaderFilename);

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

	_shaderProgramID = shaderProgram;

	return shaderProgram;
}

///
///
std::string ShaderManager::ReadShaderFile(std::string& filename)
{
	_log->Debug("Loading shader file: " + filename);

	unsigned int fileLen = 0;
	char* fileContents;
	std::ifstream file(filename, std::ios::in);

	if (!file.good()) {
		//throw Exception
	}

	std::stringstream ss;
	ss << file.rdbuf();

	file.close();



	return ss.str();
}

///
///
unsigned int ShaderManager::CompileShader(unsigned int shaderType, const char* source, int sourceLen, std::string& shaderName)
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
