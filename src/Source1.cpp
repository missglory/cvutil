#include <iostream>
#include "opencv2/opencv.hpp"
#include <vector>
#include "utils.h"

const int W = 800;
const int H = 500;

int main(void) {
	Timer timer;
	timer.start();
	cv::Mat testimg = cv::imread("../res/1.jpg", CV_LOAD_IMAGE_UNCHANGED);
	if (testimg.data == NULL) {
		std::cout << "failed to load img\n";
		system("PAUSE");
		exit(0);
	}
	cv::namedWindow("color", CV_WINDOW_FREERATIO);
	cv::namedWindow("gs", CV_WINDOW_FREERATIO);
	cv::resizeWindow("color", W, H);
	cv::resizeWindow("gs", W, H);
	cv::moveWindow("color", 20, 20);
	cv::moveWindow("gs", W + 10, 20);

	cv::Mat grayimg;
	cvtColor(testimg, grayimg, CV_BGR2GRAY);
	GaussianBlur(grayimg, grayimg, cv::Size(9, 9), 2, 2);

	Timer timer2; timer2.start();
	std::vector<cv::Vec3f> circles;
	HoughCircles(grayimg, circles, CV_HOUGH_GRADIENT, 1, grayimg.rows / 10, 200, 20, grayimg.rows / 50, grayimg.rows);
	
	

	cv::Mat sobelx;
	cv::Sobel(grayimg, sobelx, CV_32F, 1, 0);

	double minVal, maxVal;
	cv::minMaxLoc(sobelx, &minVal, &maxVal); //find minimum and maximum intensities
	std::cout << "minVal : " << minVal << "\n" << "maxVal : " << maxVal << "\n";

	cv::Mat draw;
	sobelx.convertTo(draw, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));

	cv::namedWindow("sobel", CV_WINDOW_FREERATIO);
	cv::resizeWindow("sobel", W, H);
	cv::moveWindow("sobel", 0.5f * W + 10, 0.8f * H);
	imshow("sobel", draw);


	for( size_t i = 0; i < circles.size(); i++ )
	{
		cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// circle center
		cv::circle( testimg, center, 3, cv::Scalar(0,255,0), -1, 8, 0 );
		// circle outline
		cv::circle( testimg, center, radius, cv::Scalar(0,0,255), 3, 8, 0 );
	}	
	cv::imshow("color", testimg);
	cv::imshow("gs", grayimg);
	timer.end();
	timer2.end();
	cv::waitKey();
}