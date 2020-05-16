#pragma once

#include <QMainWindow>
#include <QThread>

class DataTable;
class LogMessage;
class ServerDH;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(ServerDH *pserver, QWidget *parent = nullptr);
    ~MainWindow();

    void Log(QString s);

public slots:
    void updateValues(DataTable* dr );

private:
    Ui::MainWindow *ui;

    bool m_firstRun = true;

    ServerDH* m_pserver= nullptr;
    LogMessage* m_logw = nullptr;
};
