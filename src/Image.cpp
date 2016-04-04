#include <Image.h>
#include <stdio.h>
#include <cmath>

int findMatch(cv::Scalar original, Image ** images, size_t numImages) {
	size_t index = 0;
	int distance = INT_MAX;
	for (int i = 0; i < numImages; i++) {
		cv::Scalar test = images[i]->getAverageColor();
		int diff = std::abs(original[0] - test[0]) + std::abs(original[1] - test[1]) + std::abs(original[2] - test[2]);
		if (diff < distance) {
			distance = diff;
			index = i;
		}
	}

	return index;
}

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
	//printf("filename: %s - avg color: %f - size x: %d y: %d\n",
	//		filename.c_str(), _avgColor.val[0], _image.size().width, _image.size().height);
}

Image Image::generateMosaicFromImages(Image ** images, size_t numImages) {
	cv::Size size = _image.size();
	cv::Size tileSize = images[0]->size();
	int tileWidth = tileSize.width / 10;
	int tileHeight = tileSize.height / 10;
	cv::Mat mosaic(_image);

	#pragma omp parallel for
	for (int i = 0; i < size.height - tileHeight; i += tileHeight) {
		cv::Mat test = mosaic.rowRange(i, i + tileHeight);
		for (int j = 0; j + tileWidth < size.width; j += tileWidth) {
			//printf("sub for i: %d - j: %d with tileWidth: %d - tileHeight: %d\n", i, j, tileWidth, tileHeight);
			cv::Mat sub = test.colRange(j, j + tileWidth);
			cv::resize(images[findMatch(cv::mean(sub), images, numImages)]->getImage(), sub, cv::Size(tileWidth, tileHeight));
		}
	}

	cv::imwrite("test.jpg", mosaic);


	return Image();
}