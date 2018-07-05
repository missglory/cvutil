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
	frames(7, cv::Mat()),
	numCircles(0)
{
}

Worker::~Worker()
{
}

void Worker::getHist(cv::Mat1b const& src_gray) {
	int bins = 256;
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


	int hist_w = 255; int hist_h = 255;
	int bin_w = cvRound((double)hist_w / bins);

	cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));

	cv::normalize(hist, hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());

	double maxVal, minVal;
	cv::Point maxLoc, minLoc;
	cv::minMaxLoc(hist, &minVal, &maxVal, &minLoc, &maxLoc);
	double maxVal2 = 0;
	cv::Point maxLoc2;
	uchar* histdata = (uchar*)hist.data;
	for (int i = 0; i < 8; i++) {
		std::cout << *(histdata + i) << " ";
	}
	std::cout << "\n";
	int range = 10;
	cv::Mat nearmax;
	nearmax = hist.rowRange(maxLoc.y - range, maxLoc.y + range);

	nearmax = cv::Scalar(0, 0, 0);

	cv::minMaxLoc(hist, &minVal, &maxVal, &minLoc, &histPeakLoc);

	for (int i = 1; i < bins; i++)
	{
		line(histImage, cv::Point(bin_w*(i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
			cv::Point(bin_w*(i), hist_h - cvRound(hist.at<float>(i))),
			cv::Scalar(255, 255, 255), 2, 8, 0);
	}

	for (int i = 0; i < 8; i++) {
		std::cout << *(histdata + i) << " ";
	}
	cv::minMaxLoc(hist, &minVal, &maxVal2, &minLoc, &maxLoc2);

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
	
	
	cv::imshow("original", frames[1]);
	
	GaussianBlur(frames[2], frames[2], cv::Size(15, 15), 2, 2);
	frames[3] = frames[2].clone();
	
	getHist(frames[1]);

	
	drawEllipses(frames[1], histPeakLoc.y - 20, 700, true);
	drawEllipses(frames[1], histPeakLoc.y + 30, 100, false);

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
	emit sendNumCircles(numCircles);

	//cv::imshow(grayimg);
	//cv::imshow()

}

void Worker::drawEllipses(cv::Mat& src, double threshold, int minContourSize, bool eraseDrawing) {
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::Mat threshold_output;
	cv::threshold(src, threshold_output, threshold, 255, cv::THRESH_BINARY);
	cv::findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	std::vector<cv::RotatedRect> minRect(contours.size());
	std::vector<cv::RotatedRect> minEllipse(contours.size());
	std::vector<int> contourIndices;
	std::vector<std::vector<cv::Point> >hulls(contours.size());
	
	

	for (int i = 0; i < contours.size(); i++)
	{
		if (contours[i].size() > minContourSize)
		{
			contourIndices.push_back(i);
			minRect[i] = cv::minAreaRect(cv::Mat(contours[i]));
			minEllipse[i] = cv::fitEllipse(cv::Mat(contours[i]));

			cv::convexHull(contours[i], hulls[i]);
		}
	}

	cv::RNG rng(12345);


	if (eraseDrawing)
		//drawing = cv::Mat::zeros(threshold_output.size(), CV_8UC3);
		drawing = frames[0].clone();

	for (size_t i = 0; i < contours.size(); i++)
	{
	}

	for (int ind = 0; ind < contourIndices.size(); ind++)
	{
		int i = contourIndices[ind];
	
		cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		cv::drawContours(drawing, hulls, i, color, 2, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
		//cv::ellipse(drawing, minEllipse[i], color, 2, 8);
		// rotated rectangle
		cv::Point2f rect_points[4]; minRect[i].points(rect_points);
		for (int j = 0; j < 4; j++)
			cv::line(drawing, rect_points[j], rect_points[(j + 1) % 4], color, 1, 8);
	}

	/// Show in a window
	cv::namedWindow("Contours", CV_WINDOW_AUTOSIZE);
	cv::imshow("Contours", drawing);
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
