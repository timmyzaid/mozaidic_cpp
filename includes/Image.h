#pragma once
#include <opencv2/opencv.hpp>

class Image {
public:
	Image():
		_scale(1),
		_used(0) {};
	Image(cv::String filename);
	Image(cv::String filename, double scale);

	Image(Image&& other):
		_image(other._image) {
	}

	~Image() {
	}

	cv::Scalar getAverageColor() {
		return _avgColor;
	}

	Image generateMosaicFromImages(Image ** images);

	cv::Size size() {
		return _image.size();
	}

private:
	cv::Mat _image;
	cv::Scalar _avgColor;
	double _scale;
	int _used;
};