#include "utils.h"
#include "Worker.h"
#include "opencv2/opencv.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <algorithm>
Worker::Worker(QObject *parent) :
	QObject(parent),
	hulls(2) {}
Worker::~Worker(){}

#define getmat getMat(cv::ACCESS_READ)
#define getmatr getMat(cv::ACCESS_READ)
#define getmatw getMat(cv::ACCESS_WRITE)
#define getmatrw getMat(cv::ACCESS_RW)



#define IMSHOWS_

#ifdef IMSHOWS
#define imshowdef(x) cv::namedWindow((#x), CV_WINDOW_FREERATIO); cv::imshow(#x, (x))
#define imshownamed(x, s) cv::namedWindow((s), CV_WINDOW_KEEPRATIO); cv::imshow((s), (x))
#else
#define imshowdef(x)
#define imshownamed(x, s)
#endif

void Worker::getHistPeaks(cv::UMat const& src_gray, int bins, bool uchar) {

	int histSize[] = { bins };
	int channels[] = { 0 };
	float rangeGray[2];
	rangeGray[0] = 0.;
	if (uchar)
		rangeGray[1] = 255.;
	else
		rangeGray[1] = 1.;
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
	
	visualizeHist(hist, "hist");

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
	if (histPeaksCount > 1)
		std::sort(histPeaks, histPeaks + histPeaksCount, [](const HistPeak& a, const HistPeak& b) {
			return a.pos.y < b.pos.y;
		});
}

void Worker::process() {
	
	getHistPeaks(frames[1]);
	drawHulls(frames[1], (2 * histPeaks[0].pos.y + histPeaks[1].pos.y) / 3);
	//drawHulls(frames[1], histPeaks[0].pos.y + 10);
	//drawHulls(frames[1], 40);
}


#if defined IMSHOWS
void Worker::visualizeHist(cv::Mat& hist, const std::string& window) {
	//int histSize = 256;
	//int hist_w = 512; int hist_h = 400;
	//int bin_w = cvRound((double)hist_w / histSize);
	//cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));
	//cv::normalize(hist, hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
	//for (int i = 1; i < histSize; i++)
	//{
	//	line(histImage, cv::Point(bin_w*(i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
	//		cv::Point(bin_w*(i), hist_h - cvRound(hist.at<float>(i))),
	//		cv::Scalar(255, 255, 255), 2, 8, 0);
	//}
	//imshownamed(histImage, window);
}
#else
void Worker::visualizeHist(cv::Mat& hist, const std::string& window) {}
#endif

void Worker::drawHulls(cv::UMat& src, double threshold) {
	
	Utils::Timer disttimer, starttimer;
	
	//cv::bilateralFilter(src, src, 10, 30, 10);
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;
	static cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));
	int idx = -1;
	cv::UMat threshold_output1;

	cv::GaussianBlur(src, src, cv::Size(3,3), 1, 1);

	cv::threshold(src, threshold_output1, threshold, 255, cv::THRESH_BINARY);

	cv::UMat threshhull = cv::UMat::zeros(src.size(), CV_8UC1);
	

	//cv::morphologyEx(threshold_output1, threshold_output1, cv::MORPH_OPEN, kernel);


	Utils::findContours(threshold_output1, contours, hierarchy);
	idx = Utils::findMostPointsIdx(contours);
	cv::convexHull(contours[idx], hulls[0]);
	cv::drawContours(threshhull, hulls, 0, cv::Scalar::all(255), -1);

	//cv::morphologyEx(threshold_output1, threshold_output1, cv::MORPH_CLOSE, kernel);


	imshowdef(threshhull);
	imshowdef(threshold_output1);
	cv::UMat dist;

	//Utils::distance(threshold_output1, dist, false);
	Utils::distance(threshhull, dist, false);


	cv::Point centerBig;
	double centerVal;
	
	
	cv::minMaxLoc(dist, 0, &centerVal, 0, &centerBig);
	disttimer.end();
	
	

	Utils::toFloat(threshold_output1);

	static const int numRotations = 3;
	static cv::UMat rotate[numRotations];
	for (size_t i = 0; i < numRotations; i++)
	{
		double angle = 360.0 / (numRotations) / 5;
		angle *= i;
		rotate[i] = cv::getRotationMatrix2D(centerBig, angle, 1).getUMat(cv::ACCESS_RW);
	}


	cv::UMat rotations[numRotations];

	rotations[0] = threshold_output1;
	for (size_t i = 1; i < numRotations; i++)
	{
		cv::warpAffine(threshold_output1, rotations[i], rotate[i], src.size());
		//Utils::toFloat(rotations[i]);
		imshownamed(rotations[i], "rot" + std::to_string(i));
		//double rsummin, rsummax;
		//cv::minMaxLoc(rotations[i], &rsummin, &rsummax, 0, 0);
		//std::cout << rsummin << " " << rsummax << "\n";
	}



	cv::UMat rsum = cv::UMat::zeros(src.size(), CV_32FC1);
	for (size_t i = 0; i < numRotations; i++)
	{
		cv::add(rsum, rotations[i], rsum);
		imshownamed(rsum, "rsum iter " + std::to_string(i));
		//double rsummin, rsummax;
		//cv::minMaxLoc(rsum, &rsummin, &rsummax, 0, 0);
		//std::cout << rsummin << " " << rsummax << "\n";
	}

	//cv::normalize(rsum, rsum, 0., 1., CV_MINMAX);
	cv::multiply(rsum, 1. / numRotations, rsum);
	
	
	
	Utils::toUchar(rsum);
	imshownamed(rsum, "rsumb");
	cv::threshold(rsum, rsum, 150, 255, CV_THRESH_BINARY);

	imshowdef(rsum);

	Utils::findContours(rsum, contours, hierarchy);
	idx = Utils::findMostPointsIdx(contours);
	hulls[0].clear();
	cv::convexHull(contours[idx], hulls[0]);

	float drawr[1];
	cv::Point2f drawc[1];
	
	//cv::minEnclosingCircle(hulls[0], drawc[0], drawr[0]);
	//cv::circle(frames[0], drawc[0], drawr[0], cv::Scalar(255,255,255), 1);
	//cv::drawContours(src, hulls, 0, cv::Scalar(255, 255, 255), 2);
	minEllipse[0] = cv::fitEllipse(hulls[0]);
	cv::ellipse(frames[0], minEllipse[0], cv::Scalar(255, 55, 55), 2);





	emit sendCenter(minEllipse[0].center.x, minEllipse[0].center.y, 0);
	emit sendDiameter(std::max(minEllipse[0].size.height, minEllipse[0].size.width), 0);


	processCore(frames[1], minEllipse[0].center);

	imshowdef(frames[0]);
}





void Worker::processCore(cv::UMat& src, cv::Point center) {
	Utils::Timer coretimer;
	
	int sizeroi = 180;

	cv::Rect roirect(center.x - sizeroi, center.y - sizeroi, 2 * sizeroi, 2 * sizeroi);
	cv::UMat roi = src(roirect);

	cv::GaussianBlur(roi, roi, cv::Size(5, 5), 1, 1);


	//hough(roi, roi, 80, 150);


	imshowdef(roi);
	getHistPeaks(roi);

	cv::UMat thresh;

	float rightthresh = roi.getmatr.at<unsigned char>(roi.rows / 2, roi.cols / 2);
		//std::max(histPeaks[0].pos.y, histPeaks[1].pos.y);

	cv::threshold(roi, thresh, rightthresh - 8, 255, cv::THRESH_BINARY);

	imshownamed(thresh, "core thresh");
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;

	Utils::findContours(thresh, contours, hierarchy);
	int idx = Utils::findMostPointsIdx(contours);

	cv::RotatedRect minel = cv::fitEllipse(contours[idx]);

	emit sendVariance(Utils::countVariance(contours[idx], minel.center));
	
	minel.center.x += center.x - sizeroi;
	minel.center.y += center.y - sizeroi;

	cv::ellipse(frames[0], minel, cv::Scalar(55, 55, 255), 2);
	imshowdef(frames[0]);

	emit sendCenter(minel.center.x, minel.center.y, 1);
	emit sendDiameter(std::max(minel.size.height, minel.size.width), 1);
	emit sendCenterDist(Utils::distance(minel.center, center));
	coretimer.end();
	emit sendEccentricity(Utils::Eccentricity(minel));
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




void Worker::hough(cv::UMat& src, cv::UMat& dst, int rsmall, int rbig) {
	//std::vector<cv::Vec3f> circles;
	//cv::HoughCircles(src, circles, cv::HOUGH_GRADIENT, 1, 5,
	//	90, 60, rsmall, rbig // change the last two parameters
	//				   // (min_radius & max_radius) to detect larger circles
	//);
	//for (size_t i = 0; i < circles.size(); i++)
	//{
	//	cv:: Vec3i c = circles[i];
	//	cv::circle(dst, cv::Point(c[0], c[1]), c[2], cv::Scalar(0, 0, 255), 5, cv::LINE_AA);
	//	cv::circle(dst, cv::Point(c[0], c[1]), 2, cv::Scalar(0, 255, 0), 5, cv::LINE_AA);
	//}
}



void Worker::processMask(cv::RotatedRect& ellipse, cv::UMat& src) {
	//cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(9, 9));	
	//cv::UMat openMask, closeMask, tmpMask;
	//int rsz = 8;
	//cv::resize(src, openMask, cv::Size(src.cols / rsz, src.rows / rsz));
	//cv::resize(src, closeMask, cv::Size(src.cols / rsz, src.rows / rsz));
	//cv::resize(src, tmpMask, cv::Size(src.cols / rsz, src.rows / rsz));
	////tmpMask = src.clone();

	//int br = tmpMask.rows * .2, bc = tmpMask.cols * .2;
	//cv::copyMakeBorder(closeMask, closeMask, br, br, br, br, cv::BORDER_CONSTANT, cv::Scalar(0));
	//cv::copyMakeBorder(openMask, openMask, br, br, br, br, cv::BORDER_CONSTANT, cv::Scalar(0));
	//cv::copyMakeBorder(tmpMask, tmpMask, br, br, br, br, cv::BORDER_CONSTANT, cv::Scalar(0));

	//cv::morphologyEx(openMask, openMask, cv::MORPH_OPEN, kernel, cv::Point(-1,-1), 3);
	//cv::morphologyEx(closeMask, closeMask, cv::MORPH_CLOSE, kernel, cv::Point(-1,-1), 3);
	//cv::threshold(openMask, openMask, 50, 255, CV_8UC1);

	//std::vector<std::vector<cv::Point> > contours;
	//std::vector<cv::Vec4i> hierarchy;
	//cv::findContours(openMask, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	//int idx = Utils::findMostPointsIdx(contours);
	//float r;
	//cv::Point2f center;

	//cv::minEnclosingCircle(contours[idx], center, r);


	//cv::UMat circleMask = cv::UMat::zeros(src.size(), CV_8UC1);
	//cv::circle(circleMask, center, r , cv::Scalar(255), -1, 8, 0);
	//cv::circle(tmpMask, center, r * .99 , cv::Scalar(255), -1);
	//tmpMask.copyTo(tmpMask, circleMask);
	//contours.clear();
	//hierarchy.clear();


	//cv::findContours(tmpMask, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	//idx = Utils::findMostPointsIdx(contours);
	//emit sendVariance(Utils::countVariance(contours[idx], center) * rsz * rsz);
	//emit sendDiameter(r * 2, 0);

	//center.x -= br;
	//center.y -= br;
	//center.x *= rsz;
	//center.y *= rsz;
	//r *= rsz;
	//imshowdef(circleMask);


	//minEllipse[0].center = center;
	//cv::circle(frames[0], center, r, cv::Scalar(200), 4, 8, 0);

	//imshowdef(openMask);
	//imshowdef(closeMask);
	//imshowdef(tmpMask);

}