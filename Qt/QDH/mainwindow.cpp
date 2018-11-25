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

        connect(m_worker, SIGNAL(updateValues(DataTable*)), SLOT(updateValues(DataTable*)));

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

void MainWindow::updateValues(DataTable* dr)
{
    double fval[6];
    fval[0]= dr->GetValueF("T6", "Produced");
    fval[1]= dr->GetValueF("T6", "Surplus");
    fval[2]= dr->GetValueF("T6", "Consumed");

    fval[3] = dr->GetValueF("T6", "L1");
    fval[4] = dr->GetValueF("T6", "L2");
    fval[5] = dr->GetValueF("T6", "L3");

    ui->label_P->setText(QString::number(fval[0],'f',1));
    ui->label_S->setText(QString::number(fval[1],'f',1));
    ui->label_C->setText(QString::number(fval[2],'f',1));

    ui->label_L1->setText("L1: " + QString::number(fval[3],'f',1));
    ui->label_L2->setText("L2: " + QString::number(fval[4],'f',1));
    ui->label_L3->setText("L3: " + QString::number(fval[5],'f',1));

    ui->progressBar_P->setValue(fval[0]);
    ui->progressBar_C->setValue(fval[2]);

    if (fval[1]>0)
    {
        QPalette p = palette();
        p.setColor(QPalette::Highlight, Qt::green);
        ui->progressBar_S->setPalette(p);
        ui->progressBar_S->setValue(fval[1]);
    }
    else
    {
        QPalette p = palette();
        p.setColor(QPalette::Highlight, Qt::red);
        ui->progressBar_S->setPalette(p);
        ui->progressBar_S->setValue(-fval[1]);
    }
    qDebug("updateValues");
}

