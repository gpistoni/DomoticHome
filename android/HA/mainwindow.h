#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    pMenu       *m_pMenu;
    pAirTemp    *m_pAirTemp;
    pWaterTemp  *m_pWaterTemp;
    pWork       *m_pWork;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
