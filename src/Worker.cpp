#include "utils.h"
#include "Worker.h"
#include "opencv2/opencv.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
Worker::Worker(QObject *parent) :
	QObject(parent),
	hulls(2) {}
Worker::~Worker(){}

#define IMSHOWS

#ifdef IMSHOWS
#define imshowdef(x) cv::imshow(#x, (x))
#define imshownamed(x, s) cv::imshow((s), (x))
#else
#define imshowdef(x)
#define imshownamed(x, s)
#endif

void Worker::getHistPeaks(cv::UMat const& src_gray) {
	int bins = 256;
	int histSize[] = { bins };
	int channels[] = { 0 };
	float rangeGray[] = {0,255};
	const float* ranges[] = { rangeGray };
	cv::calcHist(
		&src_gray.getMat(cv::ACCESS_RW),
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
	
	visualizeHist(hist, "histor");

	double maxVal;
	for (size_t i = 0; i < histPeaksCount; i++)
	{
		cv::minMaxLoc(hist, NULL, &histPeaks[i].value, NULL, &histPeaks[i].pos);
		if (i == histPeaksCount - 1)
			break;
		int range = 10;
		int low_bound = std::max(0, histPeaks[i].pos.y - range);
		int high_bound = std::min(histPeaks[i].pos.y + range, hist.rows);
		cv::Mat nearmax = hist.rowRange(low_bound, high_bound);
		nearmax = cv::Scalar(0, 0, 0);
		visualizeHist(hist, "hist" + std::to_string(i));
	}
	std::sort(histPeaks, histPeaks + histPeaksCount, [](const HistPeak& a, const HistPeak& b) {
		return a.pos.y < b.pos.y;
	});
}

void Worker::process() {
	getHistPeaks(frames[1]);
	drawHulls(frames[1], histPeaks[0].pos.y + 15, histPeaks[1].pos.y + 5, 700, 0, true);
	calculate();
}


#ifdef IMSHOWS
void Worker::visualizeHist(cv::Mat& hist, const std::string& window) {
	int histSize = 256;
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);
	cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));
	cv::normalize(hist, hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, cv::Point(bin_w*(i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
			cv::Point(bin_w*(i), hist_h - cvRound(hist.at<float>(i))),
			cv::Scalar(255, 255, 255), 2, 8, 0);
	}
	imshownamed(histImage, window);
}
#else
void Worker::visualizeHist(cv::Mat& hist, const std::string& window) {}
#endif

void Worker::drawHulls(cv::UMat& src, double threshold, double threshold2, int minContourSize, int iteration, bool eraseDrawing) {
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::UMat threshold_output1, threshold_output2;
	cv::threshold(src, threshold_output1, threshold, 255, cv::THRESH_BINARY);
	cv::threshold(src, threshold_output2, threshold2, 255, cv::THRESH_BINARY);
	
	cv::findContours(threshold_output1, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	
	auto pair_tmp = Utils::findMostPoints(contours);
	int maxContourSize = pair_tmp.first, maxCountourIdx = pair_tmp.second;
	
	cv::convexHull(contours[maxCountourIdx], hulls[0]);
	cv::RNG rng(12345);
	{
		cv::Scalar color(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		cv::drawContours(frames[0], hulls, 0, color, 2, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
	}
	minEllipse[0] = cv::fitEllipse(cv::Mat(hulls[0]));
	int roiSize = 200;
	cv::Point p1(minEllipse[0].center.x - roiSize, minEllipse[0].center.y - roiSize);
	cv::Point p2(minEllipse[0].center.x + roiSize, minEllipse[0].center.y + roiSize);
	cv::UMat roi(frames[1], cv::Rect(p1, p2));
	getHistPeaks(roi);
	imshowdef(roi);
	cv::UMat roiThresh;
	cv::threshold(roi, roiThresh, histPeaks[0].pos.y + 5, 255, cv::THRESH_BINARY);
	imshowdef(roiThresh);
	imshowdef(roi);
	imshowdef(frames[1]);
	contours.clear();
	cv::findContours(roiThresh, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	
	pair_tmp = Utils::findMostPoints(contours);
	maxContourSize = pair_tmp.first;
	maxCountourIdx = pair_tmp.second;
	
	cv::convexHull(contours[maxCountourIdx], hulls[1]);
	minEllipse[1] = cv::fitEllipse(cv::Mat(hulls[1]));
	minEllipse[1].center.x += p1.x;
	minEllipse[1].center.y += p1.y;
	{
		cv::Scalar color(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		cv::drawContours(frames[0], hulls, 1, color, 2, 8, std::vector<cv::Vec4i>(), 0, p1);
	}
	
	getMask(minEllipse[0]);
}

void Worker::getMask(cv::RotatedRect& ellipse) {
	cv::UMat mask(frames[0].rows, frames[0].cols, CV_8UC1, cv::Scalar::all(0));
	cv::ellipse(mask, minEllipse[0], cv::Scalar::all(255), -1, 8);
	cv::UMat mask2 = mask.clone();
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(15, 15));
	cv::dilate(mask, mask2, kernel, cv::Point(-1, -1), 1, cv::BORDER_CONSTANT);
	cv::blur(mask2, mask2, cv::Size(15, 15), cv::Point(-1, -1), cv::BORDER_CONSTANT);
	cv::UMat maskdif;
	cv::subtract(mask2, mask, maskdif);
	imshowdef(maskdif);
	cv::add(mask2, cv::UMat(mask.rows, mask.cols, CV_8UC1, cv::Scalar::all(50)), mask2);
	mask2.convertTo(mask2, CV_32FC1, 1.f / 255);
	cv::UMat masked(mask.rows, mask.cols, CV_32FC1, cv::Scalar::all(0));
	frames[1].convertTo(frames[1], CV_32FC1, 1.f / 255);

	cv::multiply(frames[1], mask2, frames[1]);
	//mask2 = mask2.mul(mask2, 255.f);
	imshowdef(mask2);
	imshowdef(frames[1]);
	imshowdef(masked);
}

void Worker::calculate() {
	Utils::Timer timervar;
	timervar.start();
	
	std::vector<double> r(hulls[0].size());
	double R = 0, V = 0;
	for (size_t i = 0; i < hulls[0].size(); i++)
	{
		r[i] = cv::norm(hulls[0][i] - (cv::Point)minEllipse[0].center);
		R += r[i];
	}
	emit sendVariance(Utils::countVariance(r));
	timervar.end();
	
	for (int i = 0; i < 2; i++) {
		emit sendCenter(minEllipse[i].center.x, minEllipse[i].center.y, i);	
		cv::Size2f s = minEllipse[i].size;
		emit sendDiameter(std::max(s.height, s.width), i);
	}
	emit sendCenterDist(cv::norm(minEllipse[0].center - minEllipse[1].center));
}


void Worker::receiveGrabFrame(const QString& fileName) {
	frames[0] = cv::imread(fileName.toStdString(), CV_LOAD_IMAGE_COLOR).getUMat(cv::ACCESS_RW);
	cv::cvtColor(frames[0], frames[1], CV_BGR2GRAY);
	timer.start();
	process();
	timer.end();
	emit sendProcessTime(timer.elapsed()); 
	emit sendFrame(Utils::mat_to_qimage(frames[0].getMat(cv::ACCESS_RW), QImage::Format_RGB888));
}
