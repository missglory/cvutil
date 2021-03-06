#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Worker.h"
#include "utils.h"
#include <QStringBuilder>
#include "masterwindow.h"


MainWindow::MainWindow(QWidget *parent):
	QWidget(parent),
	ui(new Ui::MainWindow),
	next(NULL),
	id(-1)
{
	ui->setupUi(this);
	setup();
	show();
}

void MainWindow::receiveShow() {
	show();
}

void MainWindow::closeEvent(QCloseEvent *bar) {
	thread->quit();
	thread->wait();
	QWidget::closeEvent(bar);
}

MainWindow::~MainWindow() {
	thread->quit();
	thread->wait();
}

void MainWindow::onButtonBackClicked() {
	
	emit switchFrame(id - 1);
}

void MainWindow::onButtonForwardClicked() {
	emit switchFrame(id + 1);
}


void MainWindow::setup() {
	thread = new QThread(this);
	Worker* w = new Worker();
	w->moveToThread(thread);
	connect(this, SIGNAL(sendSetup(int)), w, SLOT(receiveSetup(int)));
	connect(w, SIGNAL(sendFrame(const QImage&)), this, SLOT(receiveFrame(const QImage&)));
	connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(onOpenButtonClicked()));
	connect(this, SIGNAL(requestFrame(const QString&)), w, SLOT(receiveGrabFrame(const QString&)));
	connect(w, SIGNAL(sendProcessTime(const float)), this, SLOT(receiveProcessTime(const float)));
	connect(w, SIGNAL(sendDiameter(const double, const int)), this, SLOT(receiveDiameter(const double, const int)));
	connect(w, SIGNAL(sendCenter(const float, const float, const int)), this, SLOT(receiveCenter(const float, const float, const int)));
	connect(w, SIGNAL(sendCenterDist(const double)), this, SLOT(receiveCenterDist(const double)));
	connect(w, SIGNAL(sendVariance(const double)), this, SLOT(receiveVariance(const double)));
	connect(w, SIGNAL(sendEccentricity(const double)), this, SLOT(receiveEccentricity(const double)));
	connect(ui->buttonBack, SIGNAL(clicked(bool)), this, SLOT(onButtonBackClicked()));
	connect(ui->buttonForward, SIGNAL(clicked(bool)), this, SLOT(onButtonForwardClicked()));
	//connect(parentWidget(), SIGNAL(sendFrame(const QString&)), this, SLOT(receiveStartFrame(const QString&)));
	//connect(this, SIGNAL(sendFrame(const QString&)), parentWidget(), SLOT(receiveFrame(const QString&)));
	//connect(this, SIGNAL(switchFrame(const int)), parentWidget(), SLOT(receiveSwitchFrame(const int)));
	//
	//connect(this, SIGNAL(sendFrame(const QString&)), master, SLOT(receiveFrame(const QString&)));
	//connect(this, SIGNAL(switchFrame(const int)), master, SLOT(receiveSwitchFrame(const int)));
	//
	worker = w;
	thread->start();
	//emit requestFrame("../res/4.jpg");
}

void MainWindow::receiveStartFrame(const QString& filename, const int requestId) {
	if (requestId == id)
		emit requestFrame(filename);
}

void MainWindow::receiveCenterDist(const double d) {
	ui->fiberDist->setText(QString::number(d));
	ui->coreDist->setText(QString::number(d));
}

void MainWindow::receiveVariance(const double d) {
	ui->coreVariance->setText(QString::number(d));
}

void MainWindow::receiveCenter(const float x, const float y, const int order) { 
	QString s = "(" + QString::number(x) + ", " + QString::number(y) + ")";
	if (order == 0) {
		ui->fiberCenter->setText(s);
	}
	if (order == 1) {
		ui->coreCenter->setText(s);
	}
}


void MainWindow::receiveDiameter(const double d, const int order) {
	if (order == 0) {
		ui->fiberDiameter->setText(QString::number(d));
	}
	if (order == 1) {
		ui->coreDiameter->setText(QString::number(d));
	}
}


void MainWindow::receiveFrame(const QImage& frame)
{
	int w = ui->labelView->width();
	int h = ui->labelView->height();
	ui->labelView->setPixmap(QPixmap::fromImage(frame).scaled(frame.width()/2, frame.height()/2, Qt::KeepAspectRatio));
}

void MainWindow::receiveProcessTime(const float time) {
	dbgcout(time);
	ui->time->setText(QString::number(time));
}


void MainWindow::onOpenButtonClicked() {
	QString fileName = QFileDialog::getOpenFileName(this, tr("Choose"), "/res", tr("Images (*.jpg *.png)"));
	if (QString::compare(fileName, QString())) {
		emit sendFrame(fileName);
	}
}

void MainWindow::receiveEccentricity(const double val) {
	ui->coreEccentricity->setText(QString::number(val));
}