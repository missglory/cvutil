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


void MainWindow::closeEvent(QCloseEvent *bar) {
	thread->quit();
	while (thread->isFinished());
	delete thread;
	bar->accept();
	QWidget::closeEvent(bar);
}

MainWindow::~MainWindow() {
	thread->quit();
	while (thread->isFinished());
	delete worker;
	delete thread;
	
}

void MainWindow::setup() {
	thread = new QThread();
	Worker* w = new Worker();
	w->moveToThread(thread);
	connect(this, SIGNAL(sendSetup(int)), w, SLOT(receiveSetup(int)));
	connect(w, SIGNAL(sendFrame(const QImage&)), this, SLOT(receiveFrame(const QImage&)));
	connect(w, SIGNAL(sendFrame2(const QImage&)), this, SLOT(receiveFrame2(const QImage&)));
	connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(onOpenButtonClicked()));
	connect(this, SIGNAL(requestFrame(const QString&)), w, SLOT(receiveGrabFrame(const QString&)));
	worker = w;
	thread->start();
	worker->signalSendFrame("../res/1.jpg");
	emit sendSetup(0);
	//thread.run();
}

void MainWindow::receiveFrame(const QImage& frame)
{
	int w = ui->labelView->width();
	int h = ui->labelView->height();
	ui->labelView->setPixmap(QPixmap::fromImage(frame).scaled(frame.width()/4, frame.height()/4, Qt::KeepAspectRatio));
	//ui->labelView->setPixmap(QPixmap::fromImage(frame).scaledToHeight(ui->labelView->height(), Qt::SmoothTransformation));
	
}

void MainWindow::receiveFrame2(const QImage& frame) {
	ui->label->setPixmap(QPixmap::fromImage(frame).scaled(frame.width() / 4, frame.height() / 4, Qt::KeepAspectRatio));
	//ui->label->setPixmap(QPixmap::fromImage(frame).scaledToHeight(ui->label->height(), Qt::SmoothTransformation));
}



void MainWindow::onOpenButtonClicked() {
	QString fileName = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.jpg)"));
	if (QString::compare(fileName, QString())) {
		//worker->signalSendFrame(fileName);
		emit requestFrame(fileName);
	}
}


