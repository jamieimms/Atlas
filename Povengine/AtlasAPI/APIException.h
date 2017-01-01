#pragma once
#include <string>

namespace AtlasAPI
{
	class APIException
	{
	public:
		APIException(char *file, int line, char* message);

		std::string ToString();
	private:
		std::string _file;
		int _line;
		std::string _message;

		char* _name = "AtlasAPIException";
	};
}