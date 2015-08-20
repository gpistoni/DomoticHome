#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iostream>
#include <memory>

#include <QPushButton>
#include <QMainWindow>
#include "pMenu.h"
#include "pAirTemp.h"
#include "pWaterTemp.h"
#include "pWork.h"

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
    void on_commandLinkButton_Home_clicked();
    void on_pushButton_Next_clicked();
    void on_pushButton_Home_clicked();
    void on_pushButton_Prev_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    void on_pageIndexBar_valueChanged(int value);

private:
    int num_pages;
    std::shared_ptr<pMenu>       m_pMenu;
    std::shared_ptr<pAirTemp>    m_pAirTemp;
    std::shared_ptr<pWaterTemp>  m_pWaterTemp;
    std::shared_ptr<pWork>       m_pWork;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
