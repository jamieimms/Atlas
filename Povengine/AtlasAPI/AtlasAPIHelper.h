#pragma once
#include <string>
#include <vector>

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
		static void SetBasePath(std::string& basePath) {AtlasAPIHelper::basePath = basePath; }
		static std::string GetUserDataPath();
		static std::string GetDataPath();
		static bool EnsureDirectory(std::string& path);
		static char GetPathSeparator();
		static long GetFileSizeBytes(std::string& path);
		static bool LoadTextFile(std::string& path, std::string& out);
		//bool LoadBinaryFile(std::string& path, std::vector<unsigned char>& out);


		//String functions
#ifdef _WIN32
		static std::string ConvertUTF16ToUTF8(const wchar_t* toConvert);
		static std::wstring ConvertUTF8ToUTF16(const char* toConvert);
#endif

	private:
		static std::string basePath;

	};
}
