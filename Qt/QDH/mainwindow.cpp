#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../QWidget/ButtonVarOnOffAuto.h"
#include "../QLibrary/InfoBarVar.h"
#include "../QLibrary/InfoTempSetpoint.h"
#include "../QWidget/LogMessage.h"

MainWindow::MainWindow(Server *pserver, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_pserver(pserver)
{
    ui->setupUi(this);

    //connect server signals
    {
        connect(m_pserver, SIGNAL(updateValues(DataTable*)), SLOT(updateValues(DataTable*)));
    };
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateValues(DataTable* dr)
{
    //solo la prima volta
    if ( m_firstRun )
    {
        m_firstRun = false;

        //*****************************************************************
        // Log bar inferiore
        m_logw = new LogMessage();
        ui->bottomLayout->addWidget(m_logw);

        ui->tabWidget->setTabText(0,"progs");
        for( VarB *elem : dr->progs )
        {
            ButtonVar *but= new ButtonVar(elem);
            connect(m_pserver, SIGNAL(updateValues(DataTable*)), but, SLOT(Update()));
            ui->Page1->addWidget(but);
        }

        ui->tabWidget->setTabText(1,"temps");
        for( VarF3SP *elem : dr->temps )
        {
            InfoTempSetpoint *t= new InfoTempSetpoint(elem);
            connect(m_pserver, SIGNAL(updateValues(DataTable*)), t, SLOT(Update()));
            ui->Page2->addWidget(t);
        }

        ui->tabWidget->setTabText(2,"lights");
        for( VarB *elem : dr->lights )
        {
            ButtonVar *but= new ButtonVar(elem);
            connect(m_pserver, SIGNAL(updateValues(DataTable*)), but, SLOT(Update()));
            ui->Page3->addWidget(but);
        }

        ui->tabWidget->setTabText(3,"ampers");
        for( VarF3 *elem : dr->ampers )
        {
            InfoBarVar *t= new InfoBarVar(elem);
            connect(m_pserver, SIGNAL(updateValues(DataTable*)), t, SLOT(Update()));
            ui->Page4->addWidget(t);
        }

        ui->tabWidget->setTabText(4,"rcaldaia");
        for( VarB *elem : dr->rcaldaia )
        {
            ButtonVar *bar= new ButtonVar(elem);
            connect(m_pserver, SIGNAL(updateValues(DataTable*)), bar, SLOT(Update()));
            ui->Page5->addWidget(bar);
        }

        ui->tabWidget->setTabText(5,"tcaldaia");
        for( VarF *elem : dr->tcaldaia )
        {
            InfoBarVar *t= new InfoBarVar(elem);
            connect(m_pserver, SIGNAL(updateValues(DataTable*)), t, SLOT(Update()));
            ui->Page6->addWidget(t);
        }

        ui->tabWidget->setTabText(6,"evStanze");
        for( VarB *elem : dr->evStanze )
        {
            ButtonVar *bar= new ButtonVar(elem);
            connect(m_pserver, SIGNAL(updateValues(DataTable*)), bar, SLOT(Update()));
            ui->Page7->addWidget(bar);
        }
    }

    //***********************************************************
    //aggiorno i messaggi
    QString s;
    if ( dr->GetLogMessage(s))
         m_logw->appendMessage( s );

    //***********************************************************
    ui->label_P->setText( dr->wProduced.svalue());
    ui->label_S->setText( dr->wSurplus.svalue());
    ui->label_C->setText( dr->wConsumed.svalue());

    ui->label_L1->setText("L1: " + dr->wL1.svalue());
    ui->label_L2->setText("L2: " + dr->wL2.svalue());
    ui->label_L3->setText("L3: " + dr->wL3.svalue());

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
    //***********************************************************
}

void MainWindow::Log(QString s)
{
    m_logw->appendMessage(s);
}

