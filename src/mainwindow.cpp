#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Worker.h"
#include "utils.h"

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
	connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(onOpenButtonClicked()));
	connect(this, SIGNAL(requestFrame(const QString&)), w, SLOT(receiveGrabFrame(const QString&)));
	connect(w, SIGNAL(sendNumCircles(const int)), this, SLOT(receiveNumCircles(const int)));
	connect(w, SIGNAL(sendProcessTime(const float)), this, SLOT(receiveProcessTime(const float)));
	connect(ui->buttonNext, SIGNAL(clicked(bool)), this, SLOT(onButtonNextClicked()));
	connect(ui->buttonPrev, SIGNAL(clicked(bool)), this, SLOT(onButtonPrevClicked()));
	connect(this, SIGNAL(sendRequestFrame(const int, const int)), w, SLOT(receiveRequestFrame(const int, const int)));

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
	ui->labelView->setPixmap(QPixmap::fromImage(frame).scaled(frame.width()/2, frame.height()/2, Qt::KeepAspectRatio));
	//ui->labelView->setPixmap(QPixmap::fromImage(frame).scaledToHeight(ui->labelView->height(), Qt::SmoothTransformation));	
}

void MainWindow::receiveProcessTime(const float time) {
	//dbgcout("time ");
	dbgcout(time);
	ui->time->setText(QString::number(time));
}


void MainWindow::receiveNumCircles(const int num) {
	const QString text = QString::number(num);
	ui->numberCircles->setText(text);
}


void MainWindow::onOpenButtonClicked() {
	QString fileName = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.jpg *.png)"));
	if (QString::compare(fileName, QString())) {
		//worker->signalSendFrame(fileName);
		emit requestFrame(fileName);
	}
}


void MainWindow::onButtonNextClicked() {
	int id = ui->frameId->text().toInt();
	if (id < 7) {
		id++;
		ui->frameId->setText(QString::number(id));
		int format = QImage::Format_Indexed8;
		switch (id) {
		case 0: break;
		case 1: break;
		case 2: break;
		case 3: format = QImage::Format_RGB888;
		default: break;
		}
		emit sendRequestFrame(id + 1, format);
	}
}

void MainWindow::onButtonPrevClicked() {
	int id = ui->frameId->text().toInt();
	if (id > 0) { 
		ui->frameId->setText(QString::number(id - 1));
		emit sendRequestFrame(id - 1, QImage::Format_Indexed8);
	}
}
