#ifndef MASTERWINDOW_H
#define MASTERWINDOW_H

#include <QMainWindow>
#include <QtCore/qlist.h>
#include "mainwindow.h"

namespace Ui {
class MasterWindow;
}

class MasterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MasterWindow(QWidget *parent = 0);
    ~MasterWindow();
	QList<MainWindow*> windows;
	int current;
private:
    Ui::MasterWindow *ui;
	void addWindow();
signals:
	void sendSetup(const QString& fileName, const int id);
private slots:
	void receiveFrame(const QString& fileName);
	void receiveSwitchFrame(const int id);
};


#endif // MASTERWINDOW_H
