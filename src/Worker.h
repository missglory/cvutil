#pragma once
#include <QtWidgets/QApplication>
#include <QtCore/QString>
#include <QtGui/QImage>
#include <opencv2/opencv.hpp>


class Worker: public QObject {
	Q_OBJECT
public:
	explicit Worker(QObject *parent = 0);
	~Worker();
	void signalSendFrame(const QString& fileName);
private:
	std::vector<cv::Mat> frames;
	cv::Mat hist;
	cv::Point histPeakLoc;
	int numCircles;

	void process();

	bool status;

	bool binaryThresholdEnabled;
	int binaryThreshold;

	void takeDft(cv::Mat& source, cv::Mat& dest);
	void Worker::showDft(cv::Mat& source, cv::Mat& magnitude);
	void recenterDFT(cv::Mat& source);
	void invertDft(cv::Mat& source, cv::Mat& dest);

	void getHist(cv::Mat1b const& src_gray);

	void drawEllipses(cv::Mat& src, double threshold, int minContourSize = 200);
signals:
	void sendFrame(const QImage& frameProcessed);
	void sendNumCircles(const int num);
	void sendProcessTime(const float time);
public slots:
	void receiveGrabFrame(const QString& fileName);
	void receiveSetup(const int device);
	//void receiveToggleStream();

	//void receiveEnableThreshold();
	void receiveBinaryThreshold(int threshold);
	void receiveRequestFrame(const int id, const int);

};