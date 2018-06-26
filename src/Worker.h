#pragma once
#include <QtWidgets/QApplication>
#include <QtCore/QString>
#include <QtGui/QImage>
#include "opencv2/opencv.hpp"


class Worker: public QObject {
	Q_OBJECT
public:
	explicit Worker(QObject *parent = 0);
	~Worker();
	void signalSendFrame(const QString& fileName);
private:
	cv::Mat frameOriginal;
	cv::Mat frameProcessed;

	void process();

	bool status;

	bool binaryThresholdEnabled;
	int binaryThreshold;


signals:
	void sendFrame(const QImage& frameProcessed);
	void sendFrame2(const QImage& frameProcessed);
	void sendNumCircles(const int num);
	void sendProcessTime(const float time);
public slots:
	void receiveGrabFrame(const QString& fileName);
	void receiveSetup(const int device);
	//void receiveToggleStream();

	//void receiveEnableThreshold();
	void receiveBinaryThreshold(int threshold);

};