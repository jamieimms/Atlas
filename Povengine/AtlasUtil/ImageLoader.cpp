#include "ImageLoader.h"
#include "lodepng.h"
#include "CImg.h"
#include "..\AtlasAPI\AtlasAPIHelper.h" 

using namespace AtlasUtil;
using namespace cimg_library;

unsigned int ImageLoader::LoadPNGImage(std::string path, std::vector<unsigned char>& imgOut, unsigned int &w, unsigned int &h)
{
	unsigned int error = lodepng::decode(imgOut, w, h, path);

	return error;
}

unsigned int ImageLoader::LoadBMPImage(std::string path, std::vector<unsigned char>& imgOut, unsigned int &w, unsigned int &h)
{
	CImg<unsigned char> img(path.c_str());

	w = img.width();
	h = img.height();

	imgOut.reserve(img.size() * sizeof(unsigned char));
	//imgOut.insert(imgOut.begin(), *img.data());
	imgOut.insert(imgOut.begin(), img.size() * sizeof(unsigned char), *img.data());

	return 0;
}