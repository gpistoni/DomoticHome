#pragma once

#include <QMainWindow>
#include <QThread>
#include "server.h"

class LogMessage;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Server *pserver, QWidget *parent = nullptr);
    ~MainWindow();

    void Log(QString s);

public slots:
    void updateValues(DataTable* dr );

private:
    Ui::MainWindow *ui;

    bool m_firstRun = true;

    Server* m_pserver= nullptr;
    LogMessage* m_logw = nullptr;
};
