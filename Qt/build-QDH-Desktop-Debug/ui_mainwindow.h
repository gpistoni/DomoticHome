/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
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
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_P;
    QProgressBar *progressBar_P;
    QLabel *label_C;
    QProgressBar *progressBar_C;
    QLabel *label_S;
    QPushButton *pushButton_3;
    QProgressBar *progressBar_S;
    QLabel *label_L1;
    QLabel *label_L2;
    QLabel *label_L3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(422, 296);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 401, 220));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
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

        progressBar_P = new QProgressBar(gridLayoutWidget);
        progressBar_P->setObjectName(QStringLiteral("progressBar_P"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(progressBar_P->sizePolicy().hasHeightForWidth());
        progressBar_P->setSizePolicy(sizePolicy);
        progressBar_P->setMaximum(3000);
        progressBar_P->setValue(0);
        progressBar_P->setAlignment(Qt::AlignCenter);
        progressBar_P->setOrientation(Qt::Vertical);

        gridLayout->addWidget(progressBar_P, 5, 0, 1, 1);

        label_C = new QLabel(gridLayoutWidget);
        label_C->setObjectName(QStringLiteral("label_C"));
        label_C->setLayoutDirection(Qt::LeftToRight);
        label_C->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_C, 1, 2, 1, 1);

        progressBar_C = new QProgressBar(gridLayoutWidget);
        progressBar_C->setObjectName(QStringLiteral("progressBar_C"));
        sizePolicy.setHeightForWidth(progressBar_C->sizePolicy().hasHeightForWidth());
        progressBar_C->setSizePolicy(sizePolicy);
        progressBar_C->setMaximum(3000);
        progressBar_C->setValue(0);
        progressBar_C->setOrientation(Qt::Vertical);

        gridLayout->addWidget(progressBar_C, 5, 2, 1, 1);

        label_S = new QLabel(gridLayoutWidget);
        label_S->setObjectName(QStringLiteral("label_S"));
        label_S->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_S, 1, 1, 1, 1);

        pushButton_3 = new QPushButton(gridLayoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 0, 1, 1, 1);

        progressBar_S = new QProgressBar(gridLayoutWidget);
        progressBar_S->setObjectName(QStringLiteral("progressBar_S"));
        sizePolicy.setHeightForWidth(progressBar_S->sizePolicy().hasHeightForWidth());
        progressBar_S->setSizePolicy(sizePolicy);
        progressBar_S->setStyleSheet(QStringLiteral(""));
        progressBar_S->setMinimum(0);
        progressBar_S->setMaximum(3000);
        progressBar_S->setValue(0);
        progressBar_S->setAlignment(Qt::AlignCenter);
        progressBar_S->setOrientation(Qt::Vertical);

        gridLayout->addWidget(progressBar_S, 5, 1, 1, 1);

        label_L1 = new QLabel(gridLayoutWidget);
        label_L1->setObjectName(QStringLiteral("label_L1"));
        label_L1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_L1, 2, 2, 1, 1);

        label_L2 = new QLabel(gridLayoutWidget);
        label_L2->setObjectName(QStringLiteral("label_L2"));
        label_L2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_L2, 3, 2, 1, 1);

        label_L3 = new QLabel(gridLayoutWidget);
        label_L3->setObjectName(QStringLiteral("label_L3"));
        label_L3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_L3, 4, 2, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 422, 22));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Produced", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "Consumed", Q_NULLPTR));
        label_P->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        label_C->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        label_S->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "Surplus", Q_NULLPTR));
        label_L1->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        label_L2->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        label_L3->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
