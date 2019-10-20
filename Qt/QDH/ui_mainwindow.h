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
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *mainWidget;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *tabWidgetPage1;
    QGridLayout *gridLayout;
    QProgressBar *progressBar_S;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QProgressBar *progressBar_P;
    QLabel *label_L1;
    QLabel *label_L3;
    QLabel *label_P;
    QLabel *label_C;
    QLabel *label_L2;
    QProgressBar *progressBar_C;
    QLabel *label_S;
    QPushButton *pushButton_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(704, 375);
        MainWindow->setMaximumSize(QSize(787, 16777215));
        mainWidget = new QWidget(MainWindow);
        mainWidget->setObjectName(QStringLiteral("mainWidget"));
        gridLayout_2 = new QGridLayout(mainWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tabWidget = new QTabWidget(mainWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMaximumSize(QSize(999999, 16777215));
        QFont font;
        font.setPointSize(15);
        tabWidget->setFont(font);
        tabWidget->setAutoFillBackground(true);
        tabWidgetPage1 = new QWidget();
        tabWidgetPage1->setObjectName(QStringLiteral("tabWidgetPage1"));
        gridLayout = new QGridLayout(tabWidgetPage1);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        progressBar_S = new QProgressBar(tabWidgetPage1);
        progressBar_S->setObjectName(QStringLiteral("progressBar_S"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(progressBar_S->sizePolicy().hasHeightForWidth());
        progressBar_S->setSizePolicy(sizePolicy);
        progressBar_S->setStyleSheet(QStringLiteral(""));
        progressBar_S->setMinimum(0);
        progressBar_S->setMaximum(4000);
        progressBar_S->setValue(0);
        progressBar_S->setAlignment(Qt::AlignCenter);
        progressBar_S->setOrientation(Qt::Vertical);

        gridLayout->addWidget(progressBar_S, 6, 1, 1, 1);

        pushButton = new QPushButton(tabWidgetPage1);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(tabWidgetPage1);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 0, 2, 1, 1);

        progressBar_P = new QProgressBar(tabWidgetPage1);
        progressBar_P->setObjectName(QStringLiteral("progressBar_P"));
        sizePolicy.setHeightForWidth(progressBar_P->sizePolicy().hasHeightForWidth());
        progressBar_P->setSizePolicy(sizePolicy);
        progressBar_P->setMaximum(4000);
        progressBar_P->setValue(0);
        progressBar_P->setAlignment(Qt::AlignCenter);
        progressBar_P->setOrientation(Qt::Vertical);

        gridLayout->addWidget(progressBar_P, 6, 0, 1, 1);

        label_L1 = new QLabel(tabWidgetPage1);
        label_L1->setObjectName(QStringLiteral("label_L1"));
        label_L1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_L1, 3, 2, 1, 1);

        label_L3 = new QLabel(tabWidgetPage1);
        label_L3->setObjectName(QStringLiteral("label_L3"));
        label_L3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_L3, 5, 2, 1, 1);

        label_P = new QLabel(tabWidgetPage1);
        label_P->setObjectName(QStringLiteral("label_P"));
        label_P->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_P, 2, 0, 1, 1);

        label_C = new QLabel(tabWidgetPage1);
        label_C->setObjectName(QStringLiteral("label_C"));
        label_C->setLayoutDirection(Qt::LeftToRight);
        label_C->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_C, 2, 2, 1, 1);

        label_L2 = new QLabel(tabWidgetPage1);
        label_L2->setObjectName(QStringLiteral("label_L2"));
        label_L2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_L2, 4, 2, 1, 1);

        progressBar_C = new QProgressBar(tabWidgetPage1);
        progressBar_C->setObjectName(QStringLiteral("progressBar_C"));
        sizePolicy.setHeightForWidth(progressBar_C->sizePolicy().hasHeightForWidth());
        progressBar_C->setSizePolicy(sizePolicy);
        progressBar_C->setMaximum(4000);
        progressBar_C->setValue(0);
        progressBar_C->setOrientation(Qt::Vertical);

        gridLayout->addWidget(progressBar_C, 6, 2, 1, 1);

        label_S = new QLabel(tabWidgetPage1);
        label_S->setObjectName(QStringLiteral("label_S"));
        label_S->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_S, 2, 1, 1, 1);

        pushButton_3 = new QPushButton(tabWidgetPage1);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 0, 1, 1, 1);

        tabWidget->addTab(tabWidgetPage1, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(mainWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Produced", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "Consumed", Q_NULLPTR));
        label_L1->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        label_L3->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        label_P->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        label_C->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        label_L2->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        label_S->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "Surplus", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPage1), QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
