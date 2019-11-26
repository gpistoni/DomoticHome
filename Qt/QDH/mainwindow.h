#pragma once

#include <QMainWindow>
#include <QThread>

class DataTable;
class LogMessage;
class Server;

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

private slots:
    void on_label_S1_linkActivated(const QString &link);

private:
    Ui::MainWindow *ui;

    bool m_firstRun = true;

    Server* m_pserver= nullptr;
    LogMessage* m_logw = nullptr;
};
