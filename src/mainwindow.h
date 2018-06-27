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
	void sendSetup(const int device);
	void requestFrame(const QString& fileName);
	void sendRequestFrame(const int id, const int format);
private slots:
	void receiveFrame(const QImage& frame);
	void onOpenButtonClicked();
	void receiveNumCircles(const int num);
	void receiveProcessTime(const float time);
	void onButtonPrevClicked();
	void onButtonNextClicked();
};

#endif // MAINWINDOW_H
