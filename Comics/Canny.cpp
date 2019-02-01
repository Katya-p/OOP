#include "pch.h"
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
namespace {
	cv::Mat source;
	cv::Mat destination;
	int lowThreshold = 0;
	const int max_lowThreshold = 100;
	const int ratio = 3;
	const int kernel_size = 3;
}

static void CannyThreshold(int, void*){
	cv::Mat bgr_source[3];
	cv::Mat bgr_destination[3];
	cv::Mat bgr_detected_edges[3];
	cv::Mat bgr_subtracted[3];
	for (size_t i = 0; i < 3; i++) {
		bgr_subtracted[i].create(source.size(), source.type());
	}
	split(source, bgr_source);	
	std::vector<cv::Mat> channels;
	for (size_t i = 0; i < 3; i++) {
		cv::blur(bgr_source[i], bgr_detected_edges[i], cv::Size(3, 3));
		cv::Canny(bgr_detected_edges[i], bgr_detected_edges[i], lowThreshold, lowThreshold * ratio, kernel_size);
		bgr_destination[i] = cv::Scalar::all(0);
		bgr_source[i].copyTo(bgr_destination[i], bgr_detected_edges[i]);
		cv::subtract(bgr_source[i], bgr_detected_edges[i], bgr_subtracted[i]);
		channels.push_back(bgr_subtracted[i]);
	}
	merge(channels, destination);
	cv::imshow("Comics", destination);
}

int main(){
	source = cv::imread("super.jpg", cv::IMREAD_COLOR);
	if (source.empty()){
		std::cout << "Could not open or find the image!\n" << std::endl;
		return -1;
	}
	destination.create(source.size(), source.type());
	cv::namedWindow("Comics", cv::WINDOW_AUTOSIZE);
	cv::createTrackbar("Min Threshold:", "Comics", &lowThreshold, max_lowThreshold, CannyThreshold);
	CannyThreshold(0, 0);
	cv::waitKey(0);
	return 0;
}
