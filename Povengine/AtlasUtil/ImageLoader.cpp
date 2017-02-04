#include "ImageLoader.h"
#include "lodepng.h"
#include "..\AtlasAPI\AtlasAPIHelper.h" 
#include "jpeg_decoder.h"
#include <fstream>

using namespace AtlasUtil;

unsigned int ImageLoader::LoadPNGImage(std::string path, std::vector<unsigned char>& imgOut, unsigned int &w, unsigned int &h)
{
	unsigned int error = lodepng::decode(imgOut, w, h, path);

	return error;
}

//unsigned int ImageLoader::LoadBMPImage(std::string path, std::vector<unsigned char>& imgOut, unsigned int &w, unsigned int &h)
//{
//	CImg<unsigned char> img(path.c_str());
//
//	w = img.width();
//	h = img.height();
//
//	imgOut.reserve(img.size() * sizeof(unsigned char));
//	//imgOut.insert(imgOut.begin(), *img.data());
//	imgOut.insert(imgOut.begin(), img.size() * sizeof(unsigned char), *img.data());
//
//	return 0;
//}

unsigned int ImageLoader::LoadJPGImage(std::string path, std::vector<unsigned char>&imgOut, unsigned int &w, unsigned int &h)
{
	long fileSize = AtlasAPI::AtlasAPIHelper::GetFileSizeBytes(path);

	std::ifstream file(path, std::ios::in | std::ios::binary);

	if (!file.good()) {
		return -1;
	}

	char* buf = new char[fileSize];
	file.read(buf, fileSize);

	file.close();

	Jpeg::Decoder decoder((unsigned char*)buf, fileSize);
	if (decoder.GetResult() != Jpeg::Decoder::OK)
	{
		printf("Error decoding the input file\n");
		return -1;
	}

	w = decoder.GetWidth();
	h = decoder.GetHeight();

	auto imgSize = decoder.GetImageSize();
	imgOut.reserve(imgSize);
	imgOut.resize(imgSize);

	auto imgBytes = decoder.GetImage();
	
	memcpy(&imgOut[0], imgBytes, imgSize);
	//memcpy_s(imgOut.data(), imgSize, decoder.GetImage(), imgSize);

	//f = fopen((argc > 2) ? argv[2] : (decoder.IsColor() ? "jpeg_out.ppm" : "jpeg_out.pgm"), "wb");
	//if (!f) {
	//	printf("Error opening the output file.\n");
	//	return 1;
	//}
	//fprintf(f, "P%d\n%d %d\n255\n", decoder.IsColor() ? 6 : 5, decoder.GetWidth(), decoder.GetHeight());
	//fwrite(decoder.GetImage(), 1, decoder.GetImageSize(), f);
	//fclose(f);

	return 0;
}
