#include "APIException.h"
#include <string>
#include <sstream>

using namespace AtlasAPI;

APIException::APIException(char *file, int line, char* message)
{
	if (file != nullptr) {
		_file = file;
	}

	_line = line;

	if (message != nullptr) {
		_message = message;
	}
}

std::string APIException::ToString()
{
	std::stringstream ss;
	ss << _name << " at line " << _line << " in file " << _file << ". " << _message;

	return ss.str();
}