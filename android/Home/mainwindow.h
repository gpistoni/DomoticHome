#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <memory>

#include <QMainWindow>

#include "widgetvl.h"
#include "pagina2.h"

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

    std::shared_ptr<widgetVL>  m_pagTAir;
    std::shared_ptr<widgetVL>  m_pagTWater;
    std::shared_ptr<pagina2>  m_pagEv;
};

#endif // MAINWINDOW_H
