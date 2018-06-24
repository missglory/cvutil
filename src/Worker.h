#pragma once
#include <QtWidgets/QApplication>
#include <QtCore/QString>

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
	void sendFrame(QImage& frameProcessed);
public slots:
	void receiveGrabFrame();
	void receiveSetup(const int device);
	void receiveToggleStream();

	void receiveEnableThreshold();
	void receiveBinaryThreshold(int threshold);

};