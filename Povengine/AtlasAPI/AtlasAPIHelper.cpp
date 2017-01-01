#include "AtlasAPIHelper.h"
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

#include "APIException.h"

#ifdef _WIN32
#include <windows.h>
#include <shlobj.h>

#endif

#ifdef __APPLE__

#endif

#ifdef __linux__

#endif

using namespace AtlasAPI;
using namespace std;

// Time functions
std::string AtlasAPIHelper::GetCurrentTimeODBC()
{
	time_t now = time(nullptr);
	tm time;
	localtime_s(&time, &now);
	stringstream ss;

	ss << setfill('0') << std::setw(4) << 1900 + time.tm_year << "-" << setw(2) << time.tm_mon + 1 << "-" << setw(2) << time.tm_mday << " "
		<< setw(2) << time.tm_hour << ":" << setw(2) << time.tm_min << ":" << setw(2) << time.tm_sec;
	return ss.str();
}

float AtlasAPIHelper::GetTicks()
{
#ifdef _WIN32
	//auto ticks = GetTickCount64();
	//return ticks / 1000.0f;
	LARGE_INTEGER ticks, freq;
	QueryPerformanceCounter(&ticks);
	QueryPerformanceFrequency(&freq);
	return ticks.QuadPart / freq.QuadPart;
#endif
#ifdef __APPLE__
	throw APIException(__FILE__, __LINE__, "NOT IMPLEMENTED.");
#endif

#ifdef __linux__
	throw APIException(__FILE__, __LINE__, "NOT IMPLEMENTED.");
#endif
}

// IO functions
std::string AtlasAPIHelper::GetUserDataPath()
{
	string path;
#ifdef _WIN32
	wchar_t* widePath;
	HRESULT result = SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &widePath);
	if (result != S_OK) {
		throw APIException(__FILE__, __LINE__, "GetUserDataPath failed.");
	}
	path = ConvertUTF16ToUTF8(widePath);
	CoTaskMemFree(widePath);
#endif

#ifdef __APPLE__
	throw APIException(__FILE__, __LINE__, "NOT IMPLEMENTED.");
#endif

#ifdef __linux__
	throw APIException(__FILE__, __LINE__, "NOT IMPLEMENTED.");
#endif

	return path;
}

//
bool AtlasAPIHelper::EnsureDirectory(std::string& path)
{
#ifdef _WIN32
	std::wstring widePath = ConvertUTF8ToUTF16(path.c_str());
	
	auto result = CreateDirectory(widePath.c_str(), NULL);
	return result != 0;
#endif
}

char AtlasAPIHelper::GetPathSeparator()
{
#ifdef _WIN32
	return '\\';
#else
	return '/';
#endif
}



// String functions
#ifdef _WIN32
std::string AtlasAPIHelper::ConvertUTF16ToUTF8(const wchar_t* toConvert)
{
	std::string out;
	int bufLen = WideCharToMultiByte(CP_UTF8, 0, toConvert, -1, NULL, 0, NULL, NULL);	// Call to retrieve the required buffer size

	char * buf = new char[bufLen];
	WideCharToMultiByte(CP_UTF8, 0, toConvert, -1, buf, bufLen, NULL, NULL);	// Now actually convert the string
	out = buf;
	delete[] buf;

	return out;
}

std::wstring AtlasAPIHelper::ConvertUTF8ToUTF16(const char* toConvert)
{
	std::wstring out;
	int bufLen = MultiByteToWideChar(CP_UTF8, 0, toConvert, -1, NULL, 0);
	
	wchar_t* buf = new wchar_t[bufLen];
	MultiByteToWideChar(CP_UTF8, 0, toConvert, -1, buf, bufLen);
	out = buf;
	delete[] buf;

	return out;
}
#endif

