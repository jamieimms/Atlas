#pragma once
#include <string>

namespace AtlasUtil
{
	// AtlasString is an alias for the real string type. This is used because we want different types on different platforms (e.g. windows we want wstring, but linux we want string)
	//
#ifdef WIN32
#define TEXT(x)
	using AtlasChar = wchar_t;
	using AtlasString = std::wstring;
#endif
#ifdef __linux__
	using AtlasChar = char;
	using AtlasString = std::string;
#endif
}