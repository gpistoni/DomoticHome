#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    num_pages = 0;

    //********** main **********************
    m_pMenu = std::make_shared<pMenu>(ui->stackedWidget);
    ui->stackedWidget->addWidget( m_pMenu.get() );
    num_pages++;

    //********** AirTemp **********************
    m_pAirTemp = std::make_shared<pAirTemp>(ui->stackedWidget);
    ui->stackedWidget->addWidget( m_pAirTemp.get() );
    num_pages++;

    //********** WaterTemp **********************
    m_pWaterTemp = std::make_shared<pWaterTemp>(ui->stackedWidget);
    ui->stackedWidget->addWidget( m_pWaterTemp.get() );
    num_pages++;

    //********** Work **********************
    m_pWork = std::make_shared<pWork>(ui->stackedWidget);
    ui->stackedWidget->addWidget( m_pWork.get() );
    num_pages++;

    //*****************************************
    ui->pageIndexBar->setMaximum( num_pages - 1 );
    ui->pageIndexBar->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
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
    if (idx>0)
    ui->pageIndexBar->setValue(idx );
}

void MainWindow::on_pageIndexBar_valueChanged(int value)
{
     ui->stackedWidget->setCurrentIndex( value );
}

void MainWindow::on_MainWindow_destroyed()
{

}
