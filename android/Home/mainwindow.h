#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <memory>

#include <QMainWindow>

#include "cwidgettair.h"
#include "workerhttp.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_Prev_clicked();
    void on_pushButton_Next_clicked();

    void on_pageIndexBar_valueChanged(int value);
    void on_stackedWidget_currentChanged(int arg1);

private:
    Ui::MainWindow *ui;
    int m_num_pages;

   CWidgetTAir *m_pagTAir;
   CwidgetVL  *m_pagTWater;
   std::shared_ptr<CwidgetVL>  m_pagEv;

private:
   // Worker Thread
  WorkerThread m_work;
};

#endif // MAINWINDOW_H
