#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    num_pages = 0;

    //********** main **********************
    m_pMenu = new pMenu( ui->stackedWidget );
    ui->stackedWidget->addWidget( m_pMenu );
    num_pages++;

    //********** main **********************
    //m_pMain = new pMain( ui->stackedWidget );
    //ui->stackedWidget->addWidget( m_pMain );
    //num_pages++;

    //*****************************************
    ui->pageIndexBar->setMaximum( num_pages - 1 );
    ui->pageIndexBar->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_commandLinkButton_Home_clicked()
{
}

void MainWindow::on_pushButton_Next_clicked()
{
   int p = ui->stackedWidget->currentIndex();
   ui->stackedWidget->setCurrentIndex( (p+1) % num_pages );
}

void MainWindow::on_pushButton_Prev_clicked()
{
    int p = ui->stackedWidget->currentIndex() + num_pages;
    ui->stackedWidget->setCurrentIndex( (p-1) % num_pages );
}

void MainWindow::on_pushButton_Home_clicked()
{
   ui->stackedWidget->setCurrentIndex( 0 );
}


void MainWindow::on_stackedWidget_currentChanged(int idx )
{
    ui->pageIndexBar->setValue(idx );
}

void MainWindow::on_pageIndexBar_valueChanged(int value)
{
     ui->stackedWidget->setCurrentIndex( value );
}
