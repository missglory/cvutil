#pragma once
#include <chrono>
#include <thread>
#include "opencv2/opencv.hpp"
#include <QtGui/QImage>
#include <iostream>
#include <sstream>

inline void LogCall(const char* func, const char* file, int line, FILE* fd = NULL) {
	std::stringstream ss;
	ss << "[FILE]" << file << ":(line) " << line << "\n";
	if (fd) fprintf(fd, ss.str().c_str());
	else fprintf(stdout, ss.str().c_str());
}

#define dbgcout(x) std::cout << (x); \
	LogCall(#x, __FILE__, __LINE__)


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

	float elapsed() {
		duration = std::chrono::high_resolution_clock::now() - startp;
		float ms = duration.count() * 1000.0f;
		return ms;
	}
};


namespace Utils {
	//cv::Mat qimage_to_mat_ref(QImage &img, QImage::Format format);
	inline cv::Mat qimage_to_mat_ref(QImage &img, QImage::Format format)
	{
		return cv::Mat(img.height(), img.width(),
			format, img.bits(), img.bytesPerLine());
	}
	inline QImage mat_to_qimage(cv::Mat img, QImage::Format format) {
		return QImage((const unsigned char*)img.data, img.cols, img.rows, format);
	}
}




