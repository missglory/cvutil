#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Worker.h"


MainWindow::MainWindow(QWidget *parent):
	QWidget(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setup();
}

MainWindow::~MainWindow() {
	thread->quit();
	while (thread->isFinished());
	delete thread;
}

void MainWindow::setup() {
	thread = new QThread();
	Worker* worker = new Worker();
	worker->moveToThread(thread);
	connect(this, SIGNAL(sendSetup(int)), worker, SLOT(receiveSetup(int)));
	connect(worker, SIGNAL(sendFrame(QImage&)), this, SLOT(receiveFrame(QImage&)));

	thread->start();
	worker->signalSendFrame("../res/1.jpg");
	emit sendSetup(0);
	//thread.run();
}

void MainWindow::receiveFrame(QImage& frame)
{
	ui->labelView->setPixmap(QPixmap::fromImage(frame));

}




