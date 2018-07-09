#include "utils.h"
#include "Worker.h"
#include "opencv2/opencv.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
Worker::Worker(QObject *parent) :
	QObject(parent),
	hulls(2) {}
Worker::~Worker(){}

#define getmat getMat(cv::ACCESS_READ)
#define getmatr getMat(cv::ACCESS_READ)
#define getmatw getMat(cv::ACCESS_WRITE)
#define getmatrw getMat(cv::ACCESS_RW)




#define IMSHOWS
#define DRAWHIST

#ifdef IMSHOWS
#define imshowdef(x) cv::namedWindow((#x), CV_WINDOW_KEEPRATIO); cv::imshow(#x, (x))
#define imshownamed(x, s) cv::namedWindow((s), CV_WINDOW_KEEPRATIO); cv::imshow((s), (x))
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
	if (histPeaksCount > 1)
		std::sort(histPeaks, histPeaks + histPeaksCount, [](const HistPeak& a, const HistPeak& b) {
			return a.pos.y < b.pos.y;
		});
}

void Worker::process() {
	getHistPeaks(frames[1]);
	drawHulls(frames[1], (histPeaks[1].pos.y + histPeaks[0].pos.y) / 2, histPeaks[1].pos.y + 5, 700, 0, true);
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

void Worker::drawHulls(cv::UMat& src, double threshold, double threshold2, int minContourSize, int iteration, bool eraseDrawing) {
	std::pair<int, int> pair_tmp;
	int maxCountourIdx;
	cv::RNG rng(12345);
	imshowdef(frames[1]);
	
	cv::UMat srcClone = src.clone();
	//cv::bilateralFilter(src, src, 10, 30, 10);
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::UMat threshold_output1(frames[0].size(), CV_8UC1, cv::Scalar::all(0)), threshold_output2;
	
	cv::threshold(srcClone, threshold_output1, threshold, 255, cv::THRESH_BINARY);

	
	cv::UMat adaptive;
	//cv::adaptiveThreshold(frames[1], adaptive, 255, )



	contours.clear();
	hierarchy.clear();
	cv::findContours(threshold_output1, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	int maxContourIdx = Utils::findMostPointsIdx(contours);

	minEllipse[0] = cv::fitEllipse(cv::Mat(contours[maxContourIdx]));
	cv::UMat draw = cv::UMat::zeros(frames[0].size(), CV_8UC1);
	cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
	minEllipse[0].size.height *= 1.07;
	minEllipse[0].size.width *= 1.07;

	cv:ellipse(draw, minEllipse[0], cv::Scalar(255,255,255), -1, 8);
	
	frames[1].copyTo(draw, draw);
	imshowdef(draw);

	cv::threshold(draw, threshold_output1, threshold, 255, cv::THRESH_BINARY);
	imshowdef(threshold_output1);
	

	//for (int i = 0; i < contours.size(); i++)
	//{
	//	if (contours[i].size() < 10)
	//		continue;
	//	color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
	//	cv::drawContours(draw, contours, maxCountourIdx, cv::Scalar::all(100), 3, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
	//}
	
	//imshowdef(draw);
	getMask(minEllipse[0], threshold_output1);
	
	
	
	
	
	
	
	
	
	
	
	int roiSize = 200;
	cv::Point p1(std::max(0, (int)minEllipse[0].center.x - roiSize), 
				 std::max(0, (int)minEllipse[0].center.y - roiSize));
	cv::Point p2(std::min(src.rows - 1, (int)minEllipse[0].center.x + roiSize), 
				 std::min(src.cols - 1, (int)minEllipse[0].center.y + roiSize));
	cv::UMat roi(src, cv::Rect(p1, p2));
	getHistPeaks(roi);
	imshowdef(roi);
	cv::UMat roiThresh;
	cv::threshold(roi, roiThresh, (float)(histPeaks[0].pos.y + histPeaks[1].pos.y) / 2, 255, cv::THRESH_BINARY);
	imshowdef(roiThresh);

	contours.clear();
	hierarchy.clear();
	cv::findContours(roiThresh, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	
	int idx = Utils::findMostPointsIdx(contours);
	
	
	cv::convexHull(contours[idx], hulls[1]);
	minEllipse[1] = cv::fitEllipse(cv::Mat(hulls[1]));
	minEllipse[1].center.x += p1.x;
	minEllipse[1].center.y += p1.y;
	{
		cv::Scalar color(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		//cv::drawContours(frames[0], hulls, 1, color, 2, 8, std::vector<cv::Vec4i>(), 0, p1);
		cv::ellipse(frames[0], minEllipse[1], color, 2);
	}

	
}


void Worker::hough(cv::UMat& src, cv::UMat& dst) {
	std::vector<cv::Vec3f> circles;
	cv::HoughCircles(src, circles, CV_HOUGH_GRADIENT, 1, src.rows / 8, 200, 30, 10, 0);
	for (size_t i = 0; i < circles.size(); i++)
	{
		cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// circle center
		circle(src, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);
		// circle outline
		circle(src, center, radius, cv::Scalar(0, 0, 255), 3, 8, 0);
	}
	imshowdef(src);
}

void Worker::getMask(cv::RotatedRect& ellipse, cv::UMat& src) {
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(9, 9));	
	cv::UMat openMask, closeMask, tmpMask;
	int rsz = 8;
	cv::resize(src, openMask, cv::Size(src.cols / rsz, src.rows / rsz));
	cv::resize(src, closeMask, cv::Size(src.cols / rsz, src.rows / rsz));
	cv::resize(src, tmpMask, cv::Size(src.cols / rsz, src.rows / rsz));

	int br = tmpMask.rows * .2, bc = tmpMask.cols * .2;
	cv::copyMakeBorder(closeMask, closeMask, br, br, br, br, cv::BORDER_CONSTANT, cv::Scalar(0));
	cv::copyMakeBorder(openMask, openMask, br, br, br, br, cv::BORDER_CONSTANT, cv::Scalar(0));
	cv::copyMakeBorder(tmpMask, tmpMask, br, br, br, br, cv::BORDER_CONSTANT, cv::Scalar(0));


	//imshowdef(closeMask);

	//cv::multiply(tmpMask, histPeaks[1].pos.y / 255.0f, tmpMask);
	//cv::erode(tmpMask, tmpMask, kernel, cv::Point(-1, -1), 4, cv::BORDER_DEFAULT);
	//cv::dilate(tmpMask, tmpMask, kernel, cv::Point(-1, -1), 4, cv::BORDER_DEFAULT);
    cv::morphologyEx(openMask, openMask, cv::MORPH_OPEN, kernel, cv::Point(-1,-1), 3);//.getUMat(cv::ACCESS_READ));
	cv::morphologyEx(closeMask, closeMask, cv::MORPH_CLOSE, kernel, cv::Point(-1,-1), 3);// .getUMat(cv::ACCESS_READ));
	//cv::add(src, tmpMask, src);
	

	cv::threshold(openMask, openMask, 50, 255, CV_8UC1);

	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(openMask, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	//cv::RotatedRect minr = cv::minAreaRect(contours);

	int idx = Utils::findMostPointsIdx(contours);


	float r;
	cv::Point2f center;
	cv::minEnclosingCircle(contours[idx], center, r);
	
	cv::UMat circleMask = cv::UMat::zeros(closeMask.size(), CV_8UC1);
	cv::UMat lcirc = circleMask.clone();

	cv::circle(circleMask, center, r , cv::Scalar(255), -1, 8, 0);
	//cv::circle(circleMask, center, r , cv::Scalar(255, 255, 255), -1, 8, 0);

	cv::circle(tmpMask, center, r * .99 , cv::Scalar(255), -1);
	tmpMask.copyTo(tmpMask, circleMask);
	contours.clear();
	hierarchy.clear();


	cv::findContours(tmpMask, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	idx = Utils::findMostPointsIdx(contours);
	

	emit sendVariance(Utils::countVariance(contours[idx], center) * rsz * rsz);

	imshowdef(circleMask);

	center.x -= br;
	center.y -= br;
	center.x *= rsz;
	center.y *= rsz;
	r *= rsz;
	cv::circle(frames[0], center, r, cv::Scalar(200), 4, 8, 0);


	emit sendCenter(center.x, center.y, 0);

	imshowdef(openMask);
	imshowdef(closeMask);
	imshowdef(tmpMask);

}

void Worker::calculate(std::vector<cv::Point>& contour) {	
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
