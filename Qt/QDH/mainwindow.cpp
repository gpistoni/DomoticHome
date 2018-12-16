#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../QLibrary/PushButtonVar.h"
#include "../QLibrary/InfoBarVar.h"
#include "../QLibrary/InfoTempSetpoint.h"

MainWindow::MainWindow(Server *pserver, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_pserver(pserver)
{
    ui->setupUi(this);

    //connect server signals
    {
        connect(m_pserver, SIGNAL(updateValues(DataTable*)), SLOT(updateValues(DataTable*)));
        connect(m_pserver, SIGNAL(updateValues(DataTable*)), SLOT(updateListView(DataTable*)));
    };
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateValues(DataTable* dr)
{
    //solo la prima volta
    if ( ui->Page1->count() < 4 )
    {
        //disegno page progs
        for( VarB *elem : dr->progs )
        {
            PushButtonVar *but= new PushButtonVar(elem);
            connect(m_pserver, SIGNAL(updateValues(DataTable*)), but, SLOT(Update()));
            ui->Page1->addWidget(but);
        }

        //disegno page temps
        for( VarF3SP *elem : dr->temps )
        {
            InfoTempSetpoint *ttt= new InfoTempSetpoint(elem);
            connect(m_pserver, SIGNAL(updateValues(DataTable*)), ttt, SLOT(Update()));
            ui->Page2->addWidget(ttt);
        }

        //disegno page lights
        for( VarB *elem : dr->lights )
        {
            PushButtonVar *but= new PushButtonVar(elem);
            connect(m_pserver, SIGNAL(updateValues(DataTable*)), but, SLOT(Update()));
            ui->Page3->addWidget(but);
        }

        //disegno page ampers
        for( VarF3 *elem : dr->ampers )
        {
            InfoBarVar *bar= new InfoBarVar(elem);
            connect(m_pserver, SIGNAL(updateValues(DataTable*)), bar, SLOT(Update()));
            ui->Page4->addWidget(bar);
        }

        //disegno rcaldaia
        for( VarB *elem : dr->rcaldaia )
        {
            PushButtonVar *bar= new PushButtonVar(elem);
            connect(m_pserver, SIGNAL(updateValues(DataTable*)), bar, SLOT(Update()));
            ui->Page5->addWidget(bar);
        }

        //disegno rcaldaia
        for( VarF *elem : dr->tcaldaia )
        {
            InfoBarVar *bar= new InfoBarVar(elem);
            connect(m_pserver, SIGNAL(updateValues(DataTable*)), bar, SLOT(Update()));
            ui->Page6->addWidget(bar);
        }

        //disegno rcaldaia
        for( VarB *elem : dr->evStanze )
        {
            PushButtonVar *bar= new PushButtonVar(elem);
            connect(m_pserver, SIGNAL(updateValues(DataTable*)), bar, SLOT(Update()));
            ui->Page7->addWidget(bar);
        }
    }

    ui->label_P->setText(QString::number(dr->wProduced,'f',1));
    ui->label_S->setText(QString::number(dr->wSurplus,'f',1));
    ui->label_C->setText(QString::number(dr->wConsumed,'f',1));

    ui->label_L1->setText("L1: " + QString::number(dr->wL1,'f',1));
    ui->label_L2->setText("L2: " + QString::number(dr->wL2,'f',1));
    ui->label_L3->setText("L3: " + QString::number(dr->wL3,'f',1));

    ui->progressBar_P->setValue(dr->wProduced);
    ui->progressBar_C->setValue(dr->wConsumed);

    if (dr->wSurplus>0)
    {
        QPalette p = palette();
        p.setColor(QPalette::Highlight, Qt::green);
        ui->progressBar_S->setPalette(p);
        ui->progressBar_S->setValue(dr->wSurplus);
    }
    else
    {
        QPalette p = palette();
        p.setColor(QPalette::Highlight, Qt::red);
        ui->progressBar_S->setPalette(p);
        ui->progressBar_S->setValue(-dr->wSurplus);
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

