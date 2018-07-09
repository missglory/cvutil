#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QtCore/QThread>
#include <QtWidgets/QWidget>
#include <QtWidgets/QFileDialog>
#include "Worker.h"
#include <QtGui/QCloseEvent>
namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
	QThread* thread;
	Worker* worker;

	void setup();
	void closeEvent(QCloseEvent *bar);
signals:
	void requestFrame(const QString& fileName);
private slots:
	void receiveFrame(const QImage& frame);
	void onOpenButtonClicked();
	void receiveProcessTime(const float time);
	void receiveDiameter(const double d, const int order);
	void receiveCenter(const float x, const float y, const int order);
	void receiveCenterDist(const double d);
	void receiveVariance(const double d);
	void receiveEccentricity(const double val);
};

#endif // MAINWINDOW_H
