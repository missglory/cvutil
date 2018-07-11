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

private:
	cv::UMat frames[2]; //original & grayscale
	cv::Mat hist;
	cv::Mat mask;
	HistPeak histPeaks[histPeaksCount];
	cv::RotatedRect minEllipse[2];
	std::vector<std::vector<cv::Point> >hulls;
	Utils::Timer timer;
private:
	void process();
	void getHistPeaks(cv::UMat const& src_gray, int bins = 256, bool uchar = true);
	void drawHulls(cv::UMat& src, double threshold);
	void visualizeHist(cv::Mat& hist, const std::string& window);
	void processMask(cv::RotatedRect& ellipse, cv::UMat& src);
	void processCore(cv::UMat& src, cv::Point center);
	void hough(cv::UMat& src, cv::UMat& dst, int rsmall = 0, int rbig = 0);
signals:
	void sendFrame(const QImage& frameProcessed);
	void sendProcessTime(const float time);
	void sendCenter(const float x, const float y, const int order);
	void sendDiameter(const double d, const int order);
	void sendCenterDist(const double dist);
	void sendVariance(const double var);
	void sendEccentricity(const double value);
public slots:
	void receiveGrabFrame(const QString& fileName);
};