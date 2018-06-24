#include <iostream>
#include "opencv2/opencv.hpp"
#include <vector>
#include "utils.h"
#include "mainwindow.h"
#include <QtWidgets/QApplication>
const int W = 800;
const int H = 500;

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	MainWindow mainWindow;
	mainWindow.show();
	return app.exec();
}
