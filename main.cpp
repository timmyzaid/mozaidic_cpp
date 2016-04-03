#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "includes/Image.h"

int main(int argc, char** argv) {
	std::vector<cv::String> filenames;
	cv::glob("/home/zaid/mozaidic/Photobooth/*.jpg", filenames);

	int size = filenames.size();
	Image ** images = new Image*[size];
	#pragma omp parallel for
	for(size_t i = 0; i < size; i++) {
		images[i] = new Image(filenames[i], .1);
	}

	Image mosaic = Image("/home/zaid/mozaidic/IMG-163.jpg").generateMosaicFromImages(images);
}