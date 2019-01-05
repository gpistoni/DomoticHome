/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
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
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab1;
    QHBoxLayout *horizontalLayout;
    QGridLayout *Page1;
    QWidget *tab2;
    QHBoxLayout *horizontalLayout_6;
    QGridLayout *Page2;
    QWidget *tab3;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *Page3;
    QWidget *tab4;
    QHBoxLayout *horizontalLayout_3;
    QGridLayout *Page4;
    QWidget *tab5;
    QHBoxLayout *horizontalLayout_4;
    QGridLayout *Page5;
    QWidget *tab6;
    QHBoxLayout *horizontalLayout_5;
    QGridLayout *Page6;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_7;
    QGridLayout *Page7;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *bottomLayout;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(787, 622);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(370, 10, 411, 261));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(gridLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 1, 0, 1, 1);

        pushButton_2 = new QPushButton(gridLayoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 1, 2, 1, 1);

        label_P = new QLabel(gridLayoutWidget);
        label_P->setObjectName(QString::fromUtf8("label_P"));
        label_P->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_P, 2, 0, 1, 1);

        progressBar_P = new QProgressBar(gridLayoutWidget);
        progressBar_P->setObjectName(QString::fromUtf8("progressBar_P"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(progressBar_P->sizePolicy().hasHeightForWidth());
        progressBar_P->setSizePolicy(sizePolicy);
        progressBar_P->setMaximum(4000);
        progressBar_P->setValue(0);
        progressBar_P->setAlignment(Qt::AlignCenter);
        progressBar_P->setOrientation(Qt::Vertical);

        gridLayout->addWidget(progressBar_P, 7, 0, 1, 1);

        label_C = new QLabel(gridLayoutWidget);
        label_C->setObjectName(QString::fromUtf8("label_C"));
        label_C->setLayoutDirection(Qt::LeftToRight);
        label_C->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_C, 2, 2, 1, 1);

        progressBar_C = new QProgressBar(gridLayoutWidget);
        progressBar_C->setObjectName(QString::fromUtf8("progressBar_C"));
        sizePolicy.setHeightForWidth(progressBar_C->sizePolicy().hasHeightForWidth());
        progressBar_C->setSizePolicy(sizePolicy);
        progressBar_C->setMaximum(4000);
        progressBar_C->setValue(0);
        progressBar_C->setOrientation(Qt::Vertical);

        gridLayout->addWidget(progressBar_C, 7, 2, 1, 1);

        label_S = new QLabel(gridLayoutWidget);
        label_S->setObjectName(QString::fromUtf8("label_S"));
        label_S->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_S, 2, 1, 1, 1);

        pushButton_3 = new QPushButton(gridLayoutWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 1, 1, 1, 1);

        progressBar_S = new QProgressBar(gridLayoutWidget);
        progressBar_S->setObjectName(QString::fromUtf8("progressBar_S"));
        sizePolicy.setHeightForWidth(progressBar_S->sizePolicy().hasHeightForWidth());
        progressBar_S->setSizePolicy(sizePolicy);
        progressBar_S->setStyleSheet(QString::fromUtf8(""));
        progressBar_S->setMinimum(0);
        progressBar_S->setMaximum(4000);
        progressBar_S->setValue(0);
        progressBar_S->setAlignment(Qt::AlignCenter);
        progressBar_S->setOrientation(Qt::Vertical);

        gridLayout->addWidget(progressBar_S, 7, 1, 1, 1);

        label_L1 = new QLabel(gridLayoutWidget);
        label_L1->setObjectName(QString::fromUtf8("label_L1"));
        label_L1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_L1, 3, 2, 1, 1);

        label_L2 = new QLabel(gridLayoutWidget);
        label_L2->setObjectName(QString::fromUtf8("label_L2"));
        label_L2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_L2, 4, 2, 1, 1);

        label_L3 = new QLabel(gridLayoutWidget);
        label_L3->setObjectName(QString::fromUtf8("label_L3"));
        label_L3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_L3, 5, 2, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        gridLayout->addLayout(verticalLayout, 3, 0, 1, 1);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 351, 441));
        tabWidget->setMinimumSize(QSize(0, 441));
        tab1 = new QWidget();
        tab1->setObjectName(QString::fromUtf8("tab1"));
        horizontalLayout = new QHBoxLayout(tab1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        Page1 = new QGridLayout();
        Page1->setSpacing(6);
        Page1->setObjectName(QString::fromUtf8("Page1"));

        horizontalLayout->addLayout(Page1);

        tabWidget->addTab(tab1, QString());
        tab2 = new QWidget();
        tab2->setObjectName(QString::fromUtf8("tab2"));
        horizontalLayout_6 = new QHBoxLayout(tab2);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        Page2 = new QGridLayout();
        Page2->setSpacing(6);
        Page2->setObjectName(QString::fromUtf8("Page2"));

        horizontalLayout_6->addLayout(Page2);

        tabWidget->addTab(tab2, QString());
        tab3 = new QWidget();
        tab3->setObjectName(QString::fromUtf8("tab3"));
        horizontalLayout_2 = new QHBoxLayout(tab3);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        Page3 = new QGridLayout();
        Page3->setSpacing(6);
        Page3->setObjectName(QString::fromUtf8("Page3"));

        horizontalLayout_2->addLayout(Page3);

        tabWidget->addTab(tab3, QString());
        tab4 = new QWidget();
        tab4->setObjectName(QString::fromUtf8("tab4"));
        tab4->setMaximumSize(QSize(347, 16777215));
        horizontalLayout_3 = new QHBoxLayout(tab4);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        Page4 = new QGridLayout();
        Page4->setSpacing(6);
        Page4->setObjectName(QString::fromUtf8("Page4"));

        horizontalLayout_3->addLayout(Page4);

        tabWidget->addTab(tab4, QString());
        tab5 = new QWidget();
        tab5->setObjectName(QString::fromUtf8("tab5"));
        horizontalLayout_4 = new QHBoxLayout(tab5);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        Page5 = new QGridLayout();
        Page5->setSpacing(6);
        Page5->setObjectName(QString::fromUtf8("Page5"));

        horizontalLayout_4->addLayout(Page5);

        tabWidget->addTab(tab5, QString());
        tab6 = new QWidget();
        tab6->setObjectName(QString::fromUtf8("tab6"));
        horizontalLayout_5 = new QHBoxLayout(tab6);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        Page6 = new QGridLayout();
        Page6->setSpacing(6);
        Page6->setObjectName(QString::fromUtf8("Page6"));

        horizontalLayout_5->addLayout(Page6);

        tabWidget->addTab(tab6, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout_7 = new QHBoxLayout(tab);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        Page7 = new QGridLayout();
        Page7->setSpacing(6);
        Page7->setObjectName(QString::fromUtf8("Page7"));

        horizontalLayout_7->addLayout(Page7);

        tabWidget->addTab(tab, QString());
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(370, 280, 411, 281));
        bottomLayout = new QHBoxLayout(horizontalLayoutWidget);
        bottomLayout->setSpacing(6);
        bottomLayout->setContentsMargins(11, 11, 11, 11);
        bottomLayout->setObjectName(QString::fromUtf8("bottomLayout"));
        bottomLayout->setContentsMargins(0, 0, 0, 0);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 787, 19));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(6);


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
        tabWidget->setTabText(tabWidget->indexOf(tab1), QString());
        tabWidget->setTabText(tabWidget->indexOf(tab2), QString());
        tabWidget->setTabText(tabWidget->indexOf(tab3), QString());
        tabWidget->setTabText(tabWidget->indexOf(tab4), QString());
        tabWidget->setTabText(tabWidget->indexOf(tab5), QString());
        tabWidget->setTabText(tabWidget->indexOf(tab6), QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
