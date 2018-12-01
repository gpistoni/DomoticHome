#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "worker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateValues(DataTable* dr );
    void updateListView(DataTable* dr );

private:
    Ui::MainWindow *ui;
    QThread* m_workerthread;
    Worker* m_worker;
};



#endif // MAINWINDOW_H
