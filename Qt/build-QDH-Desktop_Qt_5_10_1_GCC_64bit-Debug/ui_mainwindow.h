/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDial>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QDial *dial_S;
    QPushButton *pushButton_3;
    QDial *dial_P;
    QDial *dial_C;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_P;
    QLabel *label_S;
    QLabel *label_C;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(424, 300);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 401, 211));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        dial_S = new QDial(gridLayoutWidget);
        dial_S->setObjectName(QStringLiteral("dial_S"));
        dial_S->setMinimum(-16);
        dial_S->setMaximum(16);

        gridLayout->addWidget(dial_S, 2, 1, 1, 1);

        pushButton_3 = new QPushButton(gridLayoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 0, 1, 1, 1);

        dial_P = new QDial(gridLayoutWidget);
        dial_P->setObjectName(QStringLiteral("dial_P"));
        dial_P->setAutoFillBackground(false);
        dial_P->setMinimum(-16);
        dial_P->setMaximum(16);
        dial_P->setValue(0);
        dial_P->setSliderPosition(0);
        dial_P->setOrientation(Qt::Horizontal);
        dial_P->setInvertedAppearance(false);

        gridLayout->addWidget(dial_P, 2, 0, 1, 1);

        dial_C = new QDial(gridLayoutWidget);
        dial_C->setObjectName(QStringLiteral("dial_C"));
        dial_C->setMinimum(-16);
        dial_C->setMaximum(16);

        gridLayout->addWidget(dial_C, 2, 2, 1, 1);

        pushButton = new QPushButton(gridLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(gridLayoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 0, 2, 1, 1);

        label_P = new QLabel(gridLayoutWidget);
        label_P->setObjectName(QStringLiteral("label_P"));
        label_P->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_P, 1, 0, 1, 1);

        label_S = new QLabel(gridLayoutWidget);
        label_S->setObjectName(QStringLiteral("label_S"));
        label_S->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_S, 1, 1, 1, 1);

        label_C = new QLabel(gridLayoutWidget);
        label_C->setObjectName(QStringLiteral("label_C"));
        label_C->setLayoutDirection(Qt::LeftToRight);
        label_C->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_C, 1, 2, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 424, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_3->setText(QApplication::translate("MainWindow", "Surplus", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Produced", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "Consumed", nullptr));
        label_P->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        label_S->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        label_C->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
