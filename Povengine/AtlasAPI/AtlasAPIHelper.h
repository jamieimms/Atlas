#pragma once
#include <string>

// Wraps native API methods and provides the correct native implementation

namespace AtlasAPI
{
	class AtlasAPIHelper
	{
	public:
		//Time functions
		static std::string GetCurrentTimeODBC();
		static float GetTicks();

		// IO functions
		static std::string GetUserDataPath();
		static std::string GetDataPath();
		static bool EnsureDirectory(std::string& path);
		static char GetPathSeparator();
		

		//String functions
#ifdef _WIN32
		static std::string ConvertUTF16ToUTF8(const wchar_t* toConvert);
		static std::wstring ConvertUTF8ToUTF16(const char* toConvert);
#endif

	};
}