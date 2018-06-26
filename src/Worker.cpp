#include "utils.h"
#include "Worker.h"

Worker::Worker(QObject *parent) :
	QObject(parent),
	status(false),
	binaryThresholdEnabled(false),
	binaryThreshold(127)
{
}

Worker::~Worker()
{
}

void Worker::process() {
	
	Timer timer;
	timer.start();
	
	cvtColor(frameOriginal, frameProcessed, CV_BGR2GRAY);
	GaussianBlur(frameProcessed, frameProcessed, cv::Size(15, 15), 2, 2);

	Timer timer2; 
	timer2.start();
	std::vector<cv::Vec3f> circles;
	HoughCircles(frameProcessed, circles, CV_HOUGH_GRADIENT, 1, 1, 200, 99, frameOriginal.rows / 200, frameOriginal.cols);

	cv::Mat sobelx;
	cv::Sobel(frameProcessed, sobelx, CV_32F, 1, 0);

	double minVal, maxVal;
	cv::minMaxLoc(sobelx, &minVal, &maxVal); //find minimum and maximum intensities
	std::cout << "minVal : " << minVal << "\n" << "maxVal : " << maxVal << "\n";

	cv::Mat draw;
	sobelx.convertTo(draw, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));

	emit sendNumCircles(circles.size());

	for (size_t i = 0; i < circles.size(); i++)
	{
		cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// circle center
		cv::circle(frameOriginal, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);
		// circle outline
		cv::circle(frameOriginal, center, radius, cv::Scalar(0, 0, 255), 3, 8, 0);
	}
	timer.end();
	//timer2.end();
	emit sendProcessTime(timer.elapsed());
	//cv::imshow(grayimg);
	//cv::imshow()
}


void Worker::signalSendFrame(const QString& fileName) {
	//emit sendFrame(output);
	//frameOriginal = Utils::qimage_to_mat_ref(output, QImage::Format_Indexed8);
	frameOriginal = cv::imread(fileName.toStdString());
	
	//emit sendFrame(Utils::mat_to_qimage(frameOriginal));
	process();
	emit sendFrame(Utils::mat_to_qimage(frameOriginal, QImage::Format_RGB888));
	emit sendFrame2(Utils::mat_to_qimage(frameProcessed, QImage::Format_Indexed8));
}



void Worker::receiveGrabFrame(const QString& fileName) {
	//dbgcout("receive Grab frame ");
	dbgcout(fileName.toStdString());
	frameOriginal = cv::imread(fileName.toStdString());
	//emit sendFrame(QImage((const unsigned char*)frameOriginal.data, fo.cols, img.rows, QImage::Format_Indexed8));
	process();
	emit sendFrame(Utils::mat_to_qimage(frameOriginal, QImage::Format_RGB888));
	emit sendFrame2(Utils::mat_to_qimage(frameProcessed, QImage::Format_Indexed8));
}

void Worker::receiveSetup(const int device) {
	
}




void Worker::receiveBinaryThreshold(int threshold) {
	binaryThreshold = threshold;
}
