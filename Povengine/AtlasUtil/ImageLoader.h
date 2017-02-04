#pragma once
#include <string>
#include <vector>

namespace AtlasUtil
{

	class ImageLoader
	{
	public:

		static unsigned int LoadPNGImage(std::string path, std::vector<unsigned char>& imgOut, unsigned int &w, unsigned int &h);
		static unsigned int LoadBMPImage(std::string path, std::vector<unsigned char>& imgOut, unsigned int &w, unsigned int &h);

		static unsigned int LoadJPGImage(std::string path, std::vector<unsigned char>&imgOut, unsigned int &w, unsigned int &h);


	};
}