#include "IO.h"

#include <sstream>

using namespace Atlas;

/// <summary>
/// Get the directory where all user data should be stored
/// </summary>
/// <returns>base path for user data (e.g. saves etc.)</returns>
std::string IO::GetUserDataDirectory()
{	
	return AtlasAPI::AtlasAPIHelper::GetUserDataPath() + AtlasAPI::AtlasAPIHelper::GetPathSeparator() + "Atlas";
}

/// <summary>
/// Get the directory where all textures should be stored
/// </summary>
/// <returns>base path for textures</returns>
std::string IO::GetTextureDirectory()
{
	return AtlasAPI::AtlasAPIHelper::GetDataPath() + "Textures" + AtlasAPI::AtlasAPIHelper::GetPathSeparator();
}

/// <summary>
/// Get the directory where all sounds should be stored
/// </summary>
/// <returns>base path for sounds</returns>
std::string IO::GetSoundDirectory()
{
	return AtlasAPI::AtlasAPIHelper::GetDataPath() + "Sound" + AtlasAPI::AtlasAPIHelper::GetPathSeparator();
}

/// <summary>
/// Get the directory where all scenes should be stored
/// </summary>
/// <returns>base path for scenes</returns>
std::string IO::GetSceneDirectory()
{
	return AtlasAPI::AtlasAPIHelper::GetDataPath() + "Scenes" + AtlasAPI::AtlasAPIHelper::GetPathSeparator();
}

/// <summary>
/// Get the directory where all shader files should be stored
/// </summary>
/// <returns>base path for shaders</returns>
std::string IO::GetShaderDirectory()
{
	return AtlasAPI::AtlasAPIHelper::GetDataPath() + "Shaders" + AtlasAPI::AtlasAPIHelper::GetPathSeparator();
}

/// <summary>
/// Get the directory where all model files should be stored
/// </summary>
/// <returns>base path for models</returns>
std::string IO::GetModelDirectory()
{
	return AtlasAPI::AtlasAPIHelper::GetDataPath() + "Models" + AtlasAPI::AtlasAPIHelper::GetPathSeparator();
}

///
///
void ParseFaceElement(char* data, std::vector<unsigned short>* vertexIndices, std::vector<unsigned short>* normalIndices)
{
	const int LINE_LEN = 256;
	char index[16];
	std::stringstream face(data);
	int vi;
	int vni;

	face.getline(index, LINE_LEN, '/');
	vi = atoi(index) - 1;
	vertexIndices->push_back(vi);

	face.getline(index, LINE_LEN, '/');
	// ti = atoi(temp);

	face.getline(index, LINE_LEN, '/');
	vni = atoi(index) -1;
	normalIndices->push_back(vni);
}

///
///
glm::vec3 ParseObjVec3(std::stringstream& s)
{
	const int LINE_LEN = 256;
	char temp[16];
	s.getline(temp, LINE_LEN, ' ');
	float x = atof(temp);
	s.getline(temp, LINE_LEN, ' ');
	float y = atof(temp);
	s.getline(temp, LINE_LEN, ' ');
	float z = atof(temp);
	return glm::vec3(x, y, z);
}

///
///
bool IO::ParseObjFile(std::string& filePath, std::vector<glm::vec3>* outVertices, std::vector<glm::vec3>* outNormals, std::vector<unsigned short>* vertexIndices, std::vector<unsigned short>* normalIndices)
{
	std::string fileContent;
	AtlasAPI::AtlasAPIHelper::LoadTextFile(filePath, fileContent);

	std::stringstream s(fileContent);
	const int LINE_LEN = 256;
	char curLine[LINE_LEN];
	char line[LINE_LEN];

	while (!s.eof()) {
		s.getline(curLine, LINE_LEN);
		if (curLine[0] == '\0') {
			continue;
		}
		std::stringstream ln(curLine);

		ln.getline(line, LINE_LEN, ' ');
		if (line[0] == '#') {
			continue;
		}
		else if (line[0] == 'v') {
			if (line[1] == 'n') {
				// Normals
				outNormals->push_back(ParseObjVec3(ln));
			}
			else if (line[1] == 't') {

			}
			else {
				outVertices->push_back(ParseObjVec3(ln));
			}
		}
		else if (line[0] == 'f')
		{
			char temp[16];
			ln.getline(temp, LINE_LEN, ' ');
			ParseFaceElement(temp, vertexIndices, normalIndices);
			int v1I = vertexIndices->back();
			int n1I = normalIndices->back();

			ln.getline(temp, LINE_LEN, ' ');
			ParseFaceElement(temp, vertexIndices, normalIndices);

			ln.getline(temp, LINE_LEN, ' ');
			ParseFaceElement(temp, vertexIndices, normalIndices);
			int v2I = vertexIndices->back();
			int n2I = normalIndices->back();

			ln.getline(temp, LINE_LEN, ' ');
			if (strlen(temp) > 0) {

				vertexIndices->push_back(v1I);
				vertexIndices->push_back(v2I);
				normalIndices->push_back(n1I);
				normalIndices->push_back(n2I);
				ParseFaceElement(temp, vertexIndices, normalIndices);
			}
		}
		//else {
		//	std::string mat = "mtllib";
		//	std::string umat = "usemtl";
		//	if (line.compare(0, mat.length(), mat)) {
		//		// mtllib
		//	}
		//	else if (line.compare(0, umat.length(), umat)) {
		//		// use material
		//	}
		//}
	}
	return true;
}

