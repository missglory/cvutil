#include <iostream>
#include "opencv2/opencv.hpp"
#include <vector>
#include "mainwindow.h"
#include <QtWidgets/QApplication>

const int W = 800;
const int H = 500;

int main(int argc, char *argv[]) {
	FILE* dbglog = fopen("log.txt", "w");
	if (!dbglog) {
		std::cout << "ERROR OPENING FILE\n";
		system("PAUSE");
		exit(0);
	}
	QApplication app(argc, argv);
	MainWindow mainWindow;
	mainWindow.show();
	return app.exec();

}
