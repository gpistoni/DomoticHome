#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../QLibrary/PushButtonVar.h"
#include "../QLibrary/InfoBarVar.h"

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
        connect(m_worker, SIGNAL(updateListView(DataTable*)), SLOT(updateListView(DataTable*)));

        m_workerthread->start();
    };
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateValues(DataTable* dr)
{
    if ( ui->progsPage->count() < 4 )
    {
        //disegno bottoni progs
        for( VarI *elem : dr->progs )
        {
            PushButtonVar *but= new PushButtonVar(elem);
            ui->progsPage->addWidget(but);
        }

        //disegno bottoni ampers
        for( VarI *elem : dr->ampers )
        {
            InfoBarVar *bar= new InfoBarVar(elem);
            ui->ampersPage->addWidget(bar);
        }
    }

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

void MainWindow::updateListView(DataTable* dr)
{
    ui->listWidget->clear();
    for(QVariantMap::const_iterator iter = dr->m_map.begin(); iter != dr->m_map.end(); ++iter)
    {
        ui->listWidget->addItem( QString(iter.key()) + " -----------------" );

        QVariantMap mp = iter.value().toMap();
        for(QVariantMap::const_iterator iter2 = mp.begin(); iter2 != mp.end(); ++iter2)
        {
            ui->listWidget->addItem( QString(iter2.key())  + ":" +  iter2.value().toString());
        }
    }

}

