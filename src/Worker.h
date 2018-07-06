#pragma once
#include <QtWidgets/QApplication>
#include <QtCore/QString>
#include <QtGui/QImage>
#include <opencv2/opencv.hpp>
#include "utils.h"

const int histPeaksCount = 2;

struct HistPeak {
	cv::Point pos;
	double value;
};

class Worker: public QObject {
	Q_OBJECT
public:
	explicit Worker(QObject *parent = 0);
	~Worker();
	//void signalSendFrame(const QString& fileName);
private:
	cv::UMat frames[2]; //original & grayscale
	cv::Mat hist;
	cv::Mat mask;
	HistPeak histPeaks[histPeaksCount];
	cv::RotatedRect minEllipse[2];
	std::vector<std::vector<cv::Point> >hulls;
	Utils::Timer timer;
	double diameters[2];
private:
	void process();
	void getHistPeaks(cv::UMat const& src_gray);
	void drawHulls(cv::UMat& src, double threshold, double threshold2, int minContourSize = 200, int iteration = 0, bool eraseDrawing = 1);
	void calculate();
	void visualizeHist(cv::Mat& hist, const std::string& window);
	void getMask(cv::RotatedRect& ellipse);
signals:
	void sendFrame(const QImage& frameProcessed);
	void sendProcessTime(const float time);
	void sendVariance(const double value);
	void sendCenter(const float x, const float y, const int order);
	void sendDiameter(const double d, const int order);
	void sendCenterDist(const double dist);
	void sendRadiusVariance(const double var);
public slots:
	void receiveGrabFrame(const QString& fileName);
};