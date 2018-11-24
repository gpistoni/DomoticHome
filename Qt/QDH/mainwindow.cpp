#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_workerthread(new QThread()),
    m_worker (new Worker())

{
    ui->setupUi(this);

    //create worker
    {
        m_worker->moveToThread(m_workerthread);
        connect(m_workerthread, SIGNAL(started()), m_worker, SLOT(process()));
        connect(m_worker, SIGNAL(finished()), m_workerthread, SLOT(quit()));
        connect(m_worker, SIGNAL(finished()), m_worker, SLOT(deleteLater()));
        connect(m_workerthread, SIGNAL(finished()), m_workerthread, SLOT(deleteLater()));

        connect(m_worker, SIGNAL(update()), SLOT(updateValues(DataReader* dr)));

        m_workerthread->start();
    };
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
}

void MainWindow::updateValues(DataReader* dr)
{
    float val[3] = {1,2,30};
    ui->label_P->setText(QString::number(val[0]));
    ui->label_S->setText(QString::number(val[1]));
    ui->label_C->setText(QString::number(val[2]));

    ui->progressBar_P->setValue(val[0]);
    ui->progressBar_S->setValue(val[1]);
    ui->progressBar_C->setValue(val[2]);
}
