#include "utils.h"
#include "Worker.h"
#include "opencv2/opencv.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
Worker::Worker(QObject *parent) :
	QObject(parent),
	status(false),
	binaryThresholdEnabled(false),
	binaryThreshold(127),
	frames(7, cv::Mat())
{
}

Worker::~Worker()
{
}

void Worker::getHist(cv::Mat1b const& src_gray) {
	int bins = 8;
	int histSize[] = { bins };
	int channels[] = { 0 };
	float rangeGray[] = {0,255};
	const float* ranges[] = { rangeGray };
	cv::calcHist(
		&src_gray,
		1, // number of images channels
		channels, //0,
		cv::Mat(), // no masks, an empty Mat 
		hist,
		1, // dimensionality 
		histSize,
		ranges,
		true, // uniform 
		false // not accumulate
	);


	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / bins);

	cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));

	cv::normalize(hist, hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
	
	for (int i = 1; i < bins; i++)
	{
		line(histImage, cv::Point(bin_w*(i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
			cv::Point(bin_w*(i), hist_h - cvRound(hist.at<float>(i))),
			cv::Scalar(255, 255, 255), 2, 8, 0);
	}
	double maxVal = 0;
	int maxLoc;
	cv::minMaxLoc(&hist, 0, &maxVal, 0, &maxLoc);
	double maxVal2 = 0;
	int maxLoc2;

	cv::minMaxLoc(hist, 0, &maxVal2, 0, &maxLoc2);

	cv::namedWindow("hist", CV_WINDOW_FREERATIO);
	cv::imshow("hist", histImage);
}

void Worker::takeDft(cv::Mat& source, cv::Mat& dest) {
	
	cv::Mat srcFloat;
	source.convertTo(srcFloat, CV_32FC1, 1.0f / 255.0f);
	cv::Mat origComplex[2] = { srcFloat, cv::Mat::zeros(srcFloat.size(), CV_32F) };
	cv::Mat dftReady;
	cv::merge(origComplex, 2, dftReady);
	//cv::Mat dftOriginal;
	cv::dft(dftReady, dest, cv::DftFlags::DFT_COMPLEX_OUTPUT);
}

void Worker::showDft(cv::Mat& source, cv::Mat& magnitude) {
	cv::Mat splitArray[2] = { cv::Mat::zeros(source.size(), CV_32F), cv::Mat::zeros(source.size(), CV_32F) };
	cv::split(source, splitArray);
	cv::magnitude(splitArray[0], splitArray[1], magnitude);
	magnitude += cv::Scalar::all(1);
	cv::log(magnitude, magnitude);
	cv::normalize(magnitude, magnitude, 0, 1, CV_MINMAX);
}

void Worker::invertDft(cv::Mat& source, cv::Mat& dest) {
	cv::Mat invert;
	cv::dft(source, invert, cv::DftFlags::DFT_INVERSE | cv::DftFlags::DFT_REAL_OUTPUT | cv::DftFlags::DFT_SCALE); 
	dest = invert;
}

void Worker::recenterDFT(cv::Mat& source) {
	int centerX = source.cols / 2;
	int centerY = source.rows / 2;
	cv::Mat quadrant1(source, cv::Rect(0, 0, centerX, centerY));
	cv::Mat quadrant2(source, cv::Rect(centerX, 0, centerX, centerY));
	cv::Mat quadrant3(source, cv::Rect(0, centerY, centerX, centerY));
	cv::Mat quadrant4(source, cv::Rect(centerX, centerY, centerX, centerY));

	cv::Mat swapMap;
	quadrant1.copyTo(swapMap);
	quadrant4.copyTo(quadrant1);
	swapMap.copyTo(quadrant4);

	quadrant2.copyTo(swapMap);
	quadrant3.copyTo(quadrant2);
	swapMap.copyTo(quadrant3);
}

void Worker::process() {
	Timer timer;
	timer.start();
	
	//cvtColor(frames[0], frames[1], CV_BGR2GRAY);
	//GaussianBlur(frames[1], frames[1], cv::Size(15, 15), 2, 2);

	Timer timer2; 
	timer2.start();
	std::vector<cv::Vec3f> circles;
	HoughCircles(frames[1], circles, CV_HOUGH_GRADIENT, 1, 1, 200, 99, frames[0].rows / 20, frames[0].cols);

	cv::Mat sobelx;
	cv::Sobel(frames[1], sobelx, CV_32F, 1, 0);

	double minVal, maxVal;
	cv::minMaxLoc(sobelx, &minVal, &maxVal); //find minimum and maximum intensities
	std::cout << "minVal : " << minVal << "\n" << "maxVal : " << maxVal << "\n";

	cv::Mat draw;
	sobelx.convertTo(draw, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));

	emit sendNumCircles(circles.size());

	cv::imshow("original", frames[1]);
	
	GaussianBlur(frames[2], frames[2], cv::Size(15, 15), 2, 2);
	frames[3] = frames[2].clone();
	
	getHist(frames[1]);

	for (size_t i = 0; i < circles.size(); i++)
	{
		cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// circle center
		cv::circle(frames[0], center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);
		// circle outline
		cv::circle(frames[0], center, radius, cv::Scalar(0, 0, 255), 3, 8, 0);
	}
	timer.end();
	//timer2.end();
	emit sendProcessTime(timer.elapsed());
	//cv::imshow(grayimg);
	//cv::imshow()





}


void Worker::signalSendFrame(const QString& fileName) {
	//emit sendFrame(output);
	//frames[0] = Utils::qimage_to_mat_ref(output, QImage::Format_Indexed8);
	frames[0] = cv::imread(fileName.toStdString());
	frames[1] = cv::imread(fileName.toStdString(), CV_LOAD_IMAGE_GRAYSCALE);

	//emit sendFrame(Utils::mat_to_qimage(frames[0]));
	process();
//	emit sendFrame(Utils::mat_to_qimage(frames[0], QImage::Format_RGB888));
}



void Worker::receiveGrabFrame(const QString& fileName) {
	//dbgcout("receive Grab frame ");
	dbgcout(fileName.toStdString());
	frames[0] = cv::imread(fileName.toStdString(), CV_LOAD_IMAGE_COLOR);
	frames[1] = cv::imread(fileName.toStdString(), CV_LOAD_IMAGE_GRAYSCALE);

	//emit sendFrame(QImage((const unsigned char*)frames[0].data, fo.cols, img.rows, QImage::Format_Indexed8));
	process();
	//emit sendFrame(Utils::mat_to_qimage(frames[0], QImage::Format_Grayscale8));
}

void Worker::receiveSetup(const int device) {
	
}

void Worker::receiveRequestFrame(const int id, const int format) {
	if (id > 0 && id < frames.size())
		emit sendFrame(Utils::mat_to_qimage(frames[id], (QImage::Format)format));
}


void Worker::receiveBinaryThreshold(int threshold) {
	binaryThreshold = threshold;
}
