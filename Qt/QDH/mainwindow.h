#pragma once

#include <QMainWindow>
#include <QThread>
#include "server.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Server *pserver, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void updateValues(DataTable* dr );
    void updateListView(DataTable* dr );

private:
    Ui::MainWindow *ui;

    Server* m_pserver;
};
