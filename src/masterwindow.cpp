#include "masterwindow.h"
#include "ui_masterwindow.h"

MasterWindow::MasterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MasterWindow)
{
	addWindow();
	emit sendSetup("../res/6.jpg", current);
}

void MasterWindow::receiveFrame(const QString& fileName) {
	for (int i = 0; i < windows.size(); i++) {
		windows[i]->hide();
	}
	windows[current]->hide();
	addWindow();
	emit sendSetup(fileName, current);
}

void MasterWindow::addWindow() {
	current = windows.size();
	windows.append(new MainWindow);
	windows[current]->id = current;
	connect(this, SIGNAL(sendSetup(const QString&, const int)), windows[current], SLOT(receiveStartFrame(const QString&, const int)));
	connect(windows[current], SIGNAL(sendFrame(const QString&)), this, SLOT(receiveFrame(const QString&)));
	connect(windows[current], SIGNAL(switchFrame(const int)), this, SLOT(receiveSwitchFrame(const int)));
	windows[current]->show();

}

void MasterWindow::receiveSwitchFrame(const int id) {
	if (id >= 0 && id < windows.size())
	{
		windows[current]->hide();
		windows[id]->show();
		current = id;
	}
}

MasterWindow::~MasterWindow()
{
    delete ui;
	std::for_each(windows.begin(), windows.end(), [](MainWindow* mw) {
		delete mw;
	});
}
