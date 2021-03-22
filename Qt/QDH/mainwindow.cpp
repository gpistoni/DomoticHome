#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../QWidget/ButtonVarForced.h"
#include "../QWidget/LogMessage.h"
#include "../QWidget/InfoBarVar.h"
#include "../QWidget/InfoTempSetpoint.h"
#include "QScrollArea"
#include "server.h"

MainWindow::MainWindow(ServerDH *pserver, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_pserver(pserver)
{
    ui->setupUi(this);

    //connect server signals
    {
        connect(m_pserver, SIGNAL(updateValues(DataTable*)), SLOT(updateValues(DataTable*)));
    }
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

        ui->tabWidget-> setTabPosition(QTabWidget::West);
        //*****************************************************************
        {
            QWidget *tab = new QWidget();
            QGridLayout *gridLayout = new QGridLayout(tab);
            gridLayout->setSpacing(6);
            gridLayout->setContentsMargins(11, 11, 11, 11);

            for( VarB *elem : dr->progs )
            {
                ButtonVar *but= new ButtonVar(elem);
                connect(m_pserver, SIGNAL(updateValues(DataTable*)), but, SLOT(Update()));
                gridLayout->addWidget(but);
            }

            QSpacerItem *horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
            gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

            ui->tabWidget->addTab(tab, QString());
            ui->tabWidget->setTabText(ui->tabWidget->indexOf(tab),"Progs");
        }
        //*****************************************************************
        {
            QWidget *tab = new QWidget();
            QGridLayout *gridLayout = new QGridLayout(tab);
            gridLayout->setSpacing(6);
            gridLayout->setContentsMargins(11, 11, 11, 11);

            for( VarF3SP *elem : dr->temps )
            {
                InfoTempSetpoint *t= new InfoTempSetpoint(elem);
                connect(m_pserver, SIGNAL(updateValues(DataTable*)), t, SLOT(Update()));
                gridLayout->addWidget(t);
            }
            QSpacerItem *horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
            gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

            ui->tabWidget->addTab(tab, QString());
            ui->tabWidget->setTabText(ui->tabWidget->indexOf(tab),"Temps");
        }
        //*****************************************************************
        {
            QWidget *tab = new QWidget();
            QGridLayout *gridLayout= new QGridLayout(tab);
            gridLayout->setSpacing(6);
            gridLayout->setContentsMargins(11, 11, 11, 11);

            for( WebVar *elem : dr->lights )
            {
                ButtonWebVar *but= new ButtonWebVar(elem);
                connect(m_pserver, SIGNAL(updateValues(DataTable*)), but, SLOT(Update()));
                gridLayout->addWidget(but);
            }
            QSpacerItem *horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
            gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

            ui->tabWidget->addTab(tab, QString());
            ui->tabWidget->setTabText(ui->tabWidget->indexOf(tab), "Lights");
        }
        //*****************************************************************
        {
            QWidget *tab = new QWidget();
            QGridLayout *gridLayout= new QGridLayout(tab);
            gridLayout->setSpacing(6);
            gridLayout->setContentsMargins(11, 11, 11, 11);

            for( VarF3 *elem : dr->ampers )
            {
                InfoBarVar *t= new InfoBarVar(elem);
                connect(m_pserver, SIGNAL(updateValues(DataTable*)), t, SLOT(Update()));
                gridLayout->addWidget(t);
            }

            //QSpacerItem *horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
            //gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

            ui->tabWidget->addTab(tab, QString());
            ui->tabWidget->setTabText(ui->tabWidget->indexOf(tab), "Ampers");
        }
        //*****************************************************************
        {
            QWidget *tab = new QWidget();
            tab->setObjectName(QStringLiteral("tabRct"));

            QGridLayout *gridLayout= new QGridLayout(tab);
            gridLayout->setSpacing(6);
            gridLayout->setContentsMargins(11, 11, 11, 11);

            for( VarBf *elem : dr->rcaldaia )
            {
                ButtonVarForced *bar= new ButtonVarForced(elem);
                connect(m_pserver, SIGNAL(updateValues(DataTable*)), bar, SLOT(Update()));
                gridLayout->addWidget(bar);
            }

            // QSpacerItem *horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
            // gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

            ui->tabWidget->addTab(tab, QString());
            ui->tabWidget->setTabText(ui->tabWidget->indexOf(tab), "Pumps");
        }
        //*****************************************************************
        {
            QWidget *tab = new QWidget();
            tab->setObjectName(QStringLiteral("tabTct"));

            QGridLayout *gridLayout= new QGridLayout(tab);
            gridLayout->setSpacing(6);
            gridLayout->setContentsMargins(11, 11, 11, 11);

            for( VarF *elem : dr->tcaldaia )
            {
                InfoBarVar *t= new InfoBarVar(elem);
                connect(m_pserver, SIGNAL(updateValues(DataTable*)), t, SLOT(Update()));
                gridLayout->addWidget(t);
            }

            //QSpacerItem *horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
            //gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

            ui->tabWidget->addTab(tab, QString());
            ui->tabWidget->setTabText(ui->tabWidget->indexOf(tab), "TempsCT");
        }
        //*****************************************************************
        {
            QWidget *tab = new QWidget();
            tab->setObjectName(QStringLiteral("tabevStanze"));

            QGridLayout *gridLayout= new QGridLayout(tab);
            gridLayout->setSpacing(6);
            gridLayout->setContentsMargins(11, 11, 11, 11);

            for( VarBf *elem : dr->evStanze )
            {
                ButtonVarForced *bar= new ButtonVarForced(elem);
                connect(m_pserver, SIGNAL(updateValues(DataTable*)), bar, SLOT(Update()));
                gridLayout->addWidget(bar);
            }

            //QSpacerItem *horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
            //gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

            ui->tabWidget->addTab(tab, QString());
            ui->tabWidget->setTabText(ui->tabWidget->indexOf(tab), "Rooms");
        }
        //*****************************************************************
        {
            QWidget *tab = new QWidget();
            tab->setObjectName(QStringLiteral("tabLogs"));

            QGridLayout *gridLayout= new QGridLayout(tab);
            gridLayout->setSpacing(6);
            gridLayout->setContentsMargins(11, 11, 11, 11);

            m_logw = new LogMessage();
            gridLayout->addWidget(m_logw);

            ui->tabWidget->addTab(tab, QString());
            ui->tabWidget->setTabText(ui->tabWidget->indexOf(tab), "Logs");
        }

        //   QScrollArea *scroll = new QScrollArea(this);
        //   scroll->setWidget(ui->tabWidget);
        ui->tabWidget->setTabText(0, "Home");

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

    float WSurplus = 100 * 3600 / dr->wCounter;

    if ( WSurplus > 0 )
        ui->label_G->setText("COUNT: " + dr->wCounter.svalue() + " w:" + QString::number(WSurplus)  );
    else
        ui->label_G->setText("COUNT: " + dr->wCounter.svalue() );

    ui->label_L1->setText("L1: " + dr->wL1.svalue());
    ui->label_L2->setText("L2: " + dr->wL2.svalue());
    ui->label_L3->setText("L3: " + dr->wL3.svalue());

    ui->progressBar_P->setValue(static_cast<int>(dr->wProduced));
    ui->progressBar_C->setValue(static_cast<int>(dr->wConsumed));

    if (dr->wSurplus>0)
    {
        QPalette p = palette();
        p.setColor(QPalette::Highlight, Qt::green);
        ui->progressBar_S->setPalette(p);
        ui->progressBar_S->setValue(static_cast<int>(dr->wSurplus));
    }
    else
    {
        QPalette p = palette();
        p.setColor(QPalette::Highlight, Qt::red);
        ui->progressBar_S->setPalette(p);
        ui->progressBar_S->setValue(static_cast<int>(-dr->wSurplus));
    }
    //***********************************************************
}

void MainWindow::Log(QString s)
{
    m_logw->appendMessage(s);
}
