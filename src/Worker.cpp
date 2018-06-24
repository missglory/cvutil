#include "Worker.h"

Worker::Worker(QObject *parent) :
	QObject(parent),
	status(false),
	binaryThresholdEnabled(false),
	binaryThreshold(127)
{
	ui->setupUi(this);
}

Worker::~Worker()
{
	delete ui;
}

void Worker::signalSendFrame(const QString& fileName) {
	QImage output(fileName);
	emit sendFrame(output);
}

void Worker::receiveGrabFrame(cv::Mat& frame) {
	frameOriginal = frame.clone();
	process();
	QImage output((const unsigned char*)frameProcessed.data, frameProcessed.cols, frameProcessed.rows, QImage::Format_Indexed8);

	emit sendFrame(output);
}

//void Worker::receiveSetup(const int device) {
//	
//}

void Worker::receiveBinaryThreshold(int threshold) {
	binaryThreshold = threshold;
}
