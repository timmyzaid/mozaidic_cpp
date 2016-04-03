#include <Image.h>
#include <stdio.h>

Image::Image(cv::String filename):
	_scale(1),
	_used(0) {
	_image = cv::imread(filename);
	_avgColor = cv::mean(_image);
	//printf("filename: %s - avg color: %f - size x: %d y: %d\n",
	//		filename.c_str(), _avgColor.val[0], _image.size().width, _image.size().height);
}

Image::Image(cv::String filename, double scale):
	_scale(scale),
	_used(0) {
	cv::resize(cv::imread(filename), _image, cv::Size(), scale, scale);
	_avgColor = cv::mean(_image);
	printf("filename: %s - avg color: %f - size x: %d y: %d\n",
			filename.c_str(), _avgColor.val[0], _image.size().width, _image.size().height);
}

Image Image::generateMosaicFromImages(Image ** images) {
	cv::Size size = _image.size();
	cv::Size tileSize = images[0]->size();
	cv::Mat mosaic(cv::Size(size.width * 10, size.height * 10), _image.type());

	for (int i = 0; i < size.width; i += 100) {
		for (int j = 0; j < size.height; j += 100) {
			cv::Mat sub = _image.colRange(i, 100).rowRange(j, 100);
		}
	}


	return Image();
}