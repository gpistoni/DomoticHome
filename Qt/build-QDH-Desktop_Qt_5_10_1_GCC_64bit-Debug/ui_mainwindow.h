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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
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
    QListWidget *listWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tabWidgetPage1;
    QHBoxLayout *horizontalLayout;
    QGridLayout *progsPage;
    QWidget *tabWidgetPage2;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *tempsPage;
    QWidget *tabWidgetPage3;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *ampersPage;
    QWidget *tabWidgetPage4;
    QWidget *tabWidgetPage5;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(721, 622);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(370, 10, 330, 551));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(gridLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 1, 0, 1, 1);

        pushButton_2 = new QPushButton(gridLayoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 1, 2, 1, 1);

        label_P = new QLabel(gridLayoutWidget);
        label_P->setObjectName(QStringLiteral("label_P"));
        label_P->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_P, 2, 0, 1, 1);

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

        gridLayout->addWidget(progressBar_P, 7, 0, 1, 1);

        label_C = new QLabel(gridLayoutWidget);
        label_C->setObjectName(QStringLiteral("label_C"));
        label_C->setLayoutDirection(Qt::LeftToRight);
        label_C->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_C, 2, 2, 1, 1);

        progressBar_C = new QProgressBar(gridLayoutWidget);
        progressBar_C->setObjectName(QStringLiteral("progressBar_C"));
        sizePolicy.setHeightForWidth(progressBar_C->sizePolicy().hasHeightForWidth());
        progressBar_C->setSizePolicy(sizePolicy);
        progressBar_C->setMaximum(3000);
        progressBar_C->setValue(0);
        progressBar_C->setOrientation(Qt::Vertical);

        gridLayout->addWidget(progressBar_C, 7, 2, 1, 1);

        label_S = new QLabel(gridLayoutWidget);
        label_S->setObjectName(QStringLiteral("label_S"));
        label_S->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_S, 2, 1, 1, 1);

        pushButton_3 = new QPushButton(gridLayoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 1, 1, 1, 1);

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

        gridLayout->addWidget(progressBar_S, 7, 1, 1, 1);

        label_L1 = new QLabel(gridLayoutWidget);
        label_L1->setObjectName(QStringLiteral("label_L1"));
        label_L1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_L1, 3, 2, 1, 1);

        label_L2 = new QLabel(gridLayoutWidget);
        label_L2->setObjectName(QStringLiteral("label_L2"));
        label_L2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_L2, 4, 2, 1, 1);

        label_L3 = new QLabel(gridLayoutWidget);
        label_L3->setObjectName(QStringLiteral("label_L3"));
        label_L3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_L3, 5, 2, 1, 1);

        listWidget = new QListWidget(gridLayoutWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        gridLayout->addWidget(listWidget, 7, 3, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

        gridLayout->addLayout(verticalLayout, 3, 0, 1, 1);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 351, 441));
        tabWidgetPage1 = new QWidget();
        tabWidgetPage1->setObjectName(QStringLiteral("tabWidgetPage1"));
        horizontalLayout = new QHBoxLayout(tabWidgetPage1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        progsPage = new QGridLayout();
        progsPage->setSpacing(6);
        progsPage->setObjectName(QStringLiteral("progsPage"));

        horizontalLayout->addLayout(progsPage);

        tabWidget->addTab(tabWidgetPage1, QString());
        tabWidgetPage2 = new QWidget();
        tabWidgetPage2->setObjectName(QStringLiteral("tabWidgetPage2"));
        verticalLayout_2 = new QVBoxLayout(tabWidgetPage2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        tempsPage = new QGridLayout();
        tempsPage->setSpacing(6);
        tempsPage->setObjectName(QStringLiteral("tempsPage"));

        verticalLayout_2->addLayout(tempsPage);

        tabWidget->addTab(tabWidgetPage2, QString());
        tabWidgetPage3 = new QWidget();
        tabWidgetPage3->setObjectName(QStringLiteral("tabWidgetPage3"));
        horizontalLayout_2 = new QHBoxLayout(tabWidgetPage3);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        ampersPage = new QGridLayout();
        ampersPage->setSpacing(6);
        ampersPage->setObjectName(QStringLiteral("ampersPage"));

        horizontalLayout_2->addLayout(ampersPage);

        tabWidget->addTab(tabWidgetPage3, QString());
        tabWidgetPage4 = new QWidget();
        tabWidgetPage4->setObjectName(QStringLiteral("tabWidgetPage4"));
        tabWidget->addTab(tabWidgetPage4, QString());
        tabWidgetPage5 = new QWidget();
        tabWidgetPage5->setObjectName(QStringLiteral("tabWidgetPage5"));
        tabWidget->addTab(tabWidgetPage5, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 721, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Produced", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "Consumed", nullptr));
        label_P->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        label_C->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        label_S->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        pushButton_3->setText(QApplication::translate("MainWindow", "Surplus", nullptr));
        label_L1->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        label_L2->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        label_L3->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPage1), QString());
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPage2), QString());
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPage3), QString());
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPage4), QString());
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPage5), QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
