#pragma once
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

namespace AtlasUtil
{
	class AtlasTime
	{
	public:
		static void getCurrentTimeODBC(std::wstring& out)
		{
			std::time_t now = std::time(nullptr);
			auto local = std::localtime(&now);
			std::wstringstream ss;

			ss << std::setfill(L'0') << std::setw(4) << 1900 + local->tm_year << L"-" << std::setw(2) << local->tm_mon + 1 << L"-" << std::setw(2) << local->tm_mday << L" " 
			   << std::setw(2) << local->tm_hour << L":" << std::setw(2) << local->tm_min << L":" << std::setw(2) << local->tm_sec;
			out = ss.str();
		}
	};
}