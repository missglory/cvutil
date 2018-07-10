/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *labelView;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QLabel *coreDist;
    QLabel *coreEccentricity;
    QLabel *coreCenter;
    QLabel *label_17;
    QLabel *label_15;
    QLabel *label_3;
    QLabel *coreDiameter;
    QLabel *centerTitle;
    QLabel *coreVariance;
    QLabel *label_20;
    QLabel *time;
    QFrame *line;
    QLabel *fiberCenter;
    QLabel *fiberDist;
    QLabel *label_6;
    QGridLayout *gridLayout_2;
    QLabel *label_16;
    QFrame *line_2;
    QLabel *fiberDiameter;
    QLabel *label_4;
    QLabel *timeTitle;
    QFrame *line_3;
    QLabel *label_7;
    QLabel *label_8;
    QPushButton *buttonBack;
    QPushButton *buttonForward;
    QPushButton *pushButton;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(872, 599);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(MainWindow);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        labelView = new QLabel(MainWindow);
        labelView->setObjectName(QStringLiteral("labelView"));

        verticalLayout->addWidget(labelView);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        coreDist = new QLabel(MainWindow);
        coreDist->setObjectName(QStringLiteral("coreDist"));

        gridLayout->addWidget(coreDist, 3, 1, 1, 1);

        coreEccentricity = new QLabel(MainWindow);
        coreEccentricity->setObjectName(QStringLiteral("coreEccentricity"));

        gridLayout->addWidget(coreEccentricity, 5, 1, 1, 1);

        coreCenter = new QLabel(MainWindow);
        coreCenter->setObjectName(QStringLiteral("coreCenter"));

        gridLayout->addWidget(coreCenter, 1, 1, 1, 1);

        label_17 = new QLabel(MainWindow);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_17, 9, 0, 1, 1);

        label_15 = new QLabel(MainWindow);
        label_15->setObjectName(QStringLiteral("label_15"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_15->setFont(font);
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_15, 7, 0, 1, 1);

        label_3 = new QLabel(MainWindow);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3->setMargin(1);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        coreDiameter = new QLabel(MainWindow);
        coreDiameter->setObjectName(QStringLiteral("coreDiameter"));

        gridLayout->addWidget(coreDiameter, 2, 1, 1, 1);

        centerTitle = new QLabel(MainWindow);
        centerTitle->setObjectName(QStringLiteral("centerTitle"));
        centerTitle->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(centerTitle, 1, 0, 1, 1);

        coreVariance = new QLabel(MainWindow);
        coreVariance->setObjectName(QStringLiteral("coreVariance"));

        gridLayout->addWidget(coreVariance, 4, 1, 1, 1);

        label_20 = new QLabel(MainWindow);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_20, 10, 0, 1, 1);

        time = new QLabel(MainWindow);
        time->setObjectName(QStringLiteral("time"));

        gridLayout->addWidget(time, 12, 1, 1, 1);

        line = new QFrame(MainWindow);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 11, 0, 1, 1);

        fiberCenter = new QLabel(MainWindow);
        fiberCenter->setObjectName(QStringLiteral("fiberCenter"));

        gridLayout->addWidget(fiberCenter, 8, 1, 1, 1);

        fiberDist = new QLabel(MainWindow);
        fiberDist->setObjectName(QStringLiteral("fiberDist"));

        gridLayout->addWidget(fiberDist, 10, 1, 1, 1);

        label_6 = new QLabel(MainWindow);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_6->setMargin(1);

        gridLayout->addWidget(label_6, 3, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_16 = new QLabel(MainWindow);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_16, 0, 0, 1, 1);


        gridLayout->addLayout(gridLayout_2, 8, 0, 1, 1);

        line_2 = new QFrame(MainWindow);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 6, 0, 1, 1);

        fiberDiameter = new QLabel(MainWindow);
        fiberDiameter->setObjectName(QStringLiteral("fiberDiameter"));

        gridLayout->addWidget(fiberDiameter, 9, 1, 1, 1);

        label_4 = new QLabel(MainWindow);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        timeTitle = new QLabel(MainWindow);
        timeTitle->setObjectName(QStringLiteral("timeTitle"));
        timeTitle->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(timeTitle, 12, 0, 1, 1);

        line_3 = new QFrame(MainWindow);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_3, 15, 0, 1, 1);

        label_7 = new QLabel(MainWindow);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_7->setMargin(1);

        gridLayout->addWidget(label_7, 4, 0, 1, 1);

        label_8 = new QLabel(MainWindow);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_8->setMargin(1);

        gridLayout->addWidget(label_8, 5, 0, 1, 1);

        buttonBack = new QPushButton(MainWindow);
        buttonBack->setObjectName(QStringLiteral("buttonBack"));

        gridLayout->addWidget(buttonBack, 14, 0, 1, 1);

        buttonForward = new QPushButton(MainWindow);
        buttonForward->setObjectName(QStringLiteral("buttonForward"));

        gridLayout->addWidget(buttonForward, 14, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        pushButton = new QPushButton(MainWindow);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(pushButton);


        horizontalLayout->addLayout(verticalLayout_2);


        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Form", nullptr));
        labelView->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        coreDist->setText(QApplication::translate("MainWindow", "0", nullptr));
        coreEccentricity->setText(QApplication::translate("MainWindow", "0", nullptr));
        coreCenter->setText(QApplication::translate("MainWindow", "0", nullptr));
        label_17->setText(QApplication::translate("MainWindow", "Diameter", nullptr));
        label_15->setText(QApplication::translate("MainWindow", "Fiber", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Diameter", nullptr));
        coreDiameter->setText(QApplication::translate("MainWindow", "0", nullptr));
        centerTitle->setText(QApplication::translate("MainWindow", "Center", nullptr));
        coreVariance->setText(QApplication::translate("MainWindow", "0", nullptr));
        label_20->setText(QApplication::translate("MainWindow", "Dist to core", nullptr));
        time->setText(QApplication::translate("MainWindow", "0", nullptr));
        fiberCenter->setText(QApplication::translate("MainWindow", "0", nullptr));
        fiberDist->setText(QApplication::translate("MainWindow", "0", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Dist to fiber", nullptr));
        label_16->setText(QApplication::translate("MainWindow", "Center", nullptr));
        fiberDiameter->setText(QApplication::translate("MainWindow", "0", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Core", nullptr));
        timeTitle->setText(QApplication::translate("MainWindow", "Time", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "Radius variance", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "Eccentricity", nullptr));
        buttonBack->setText(QApplication::translate("MainWindow", "<", nullptr));
        buttonForward->setText(QApplication::translate("MainWindow", ">", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Open file", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
