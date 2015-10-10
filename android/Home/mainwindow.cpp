#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_num_pages(0)
{
    ui->setupUi(this);

    m_work.start();

    //********** AIR **********************
    m_pagTAir =  new CWidgetTAir( ui->stackedWidget );
    ui->stackedWidget->addWidget( m_pagTAir );
    m_num_pages++;

    //********** Water **********************
    m_pagTWater = new CwidgetVL(ui->stackedWidget);
    ui->stackedWidget->addWidget( m_pagTWater );
    m_num_pages++;

    //********** EV **********************
    m_pagEv = std::make_shared<CwidgetVL>(ui->stackedWidget);
    ui->stackedWidget->addWidget( m_pagEv.get() );
    m_num_pages++;


    ui->pageIndexBar->setMaximum( m_num_pages - 1 );
    ui->pageIndexBar->setValue(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Prev_clicked()
{
    int p = ui->stackedWidget->currentIndex();
    if (p >0)
        ui->stackedWidget->setCurrentIndex( p-1 );
}

void MainWindow::on_pushButton_Next_clicked()
{
    int p = ui->stackedWidget->currentIndex();
    if (p < m_num_pages)
        ui->stackedWidget->setCurrentIndex( p+1 );
}

void MainWindow::on_pageIndexBar_valueChanged(int value)
{
    ui->stackedWidget->setCurrentIndex( value );
    ui->label_title->setText( "Page" + QString::number(value));
}

void MainWindow::on_stackedWidget_currentChanged(int idx)
{
    if (idx>0)
        ui->pageIndexBar->setValue(idx );
}
