#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //create worker
    {
        m_thread = new QThread();
        m_worker = new Worker();
        m_worker->moveToThread(m_thread);
        connect(m_worker, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
        connect(m_thread, SIGNAL(started()), m_worker, SLOT(process()));
        connect(m_worker, SIGNAL(finished()), m_thread, SLOT(quit()));
        connect(m_worker, SIGNAL(finished()), m_worker, SLOT(deleteLater()));
        connect(m_thread, SIGNAL(finished()), m_thread, SLOT(deleteLater()));
        m_thread->start();
    };

}

MainWindow::~MainWindow()
{
    delete ui;
}
