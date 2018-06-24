#pragma once
#include <chrono>
#include <thread>
#include "opencv2/opencv.hpp"
#include <QtGui/QImage>
#include <iostream>

#define dbgcout(x) std::cout << (x) << "\n"

#if defined(unix) || defined(__unix) || defined (__unix__) || defined(__APPLE__)
#define _PREDEF_UNIX
#include <signal.h>
#endif

#if defined( _WIN32 )
#define ASSERT(x) if(!(x)) __debugbreak()
#elif defined (_PREDEF_UNIX)
#define ASSERT(x) \
    if (!(x)) \
        raise(SIGTRAP)
#endif



struct Timer {
	std::chrono::time_point<std::chrono::steady_clock> startp, endp;
	std::chrono::duration<float> duration;

	void start() {
		startp = std::chrono::high_resolution_clock::now();
	}

	void end() {
		endp = std::chrono::high_resolution_clock::now();
		duration = endp - startp;
		float ms = duration.count() * 1000.0f;
		std::cout << "duration " << ms << "\n";
	}
};


namespace Utils {
	//cv::Mat qimage_to_mat_ref(QImage &img, QImage::Format format);
	inline cv::Mat qimage_to_mat_ref(QImage &img, QImage::Format format)
	{
		return cv::Mat(img.height(), img.width(),
			format, img.bits(), img.bytesPerLine());
	}
	inline QImage mat_to_qimage(cv::Mat img) {
		return QImage((const unsigned char*)img.data, img.cols, img.rows, QImage::Format_Indexed8);
	}
}




