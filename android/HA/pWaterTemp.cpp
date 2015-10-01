#include "css.h"
#include "pWaterTemp.h"
#include "ui_pWaterTemp.h"
#include "Lib/valueSetWidget.h"
#include "Lib/data.h"

pWaterTemp::pWaterTemp(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::WaterTemp)
{
    qDebug() << "WATER";

    ui->setupUi(this);

    ui->scrollAreaWidgetContents->setStyleSheet( CSS_PAGE );

    ui->label_header->setText("Values");
    ui->label_header->setStyleSheet( CSS_HEADER );
    ui->label_header->setMargin(5);

    ui->label_footer->setText("----");
    ui->label_footer->setStyleSheet( CSS_HEADER );
    ui->label_header->setMargin(5);
/*
    QLabel *lab1 = new QLabel(this);
    lab1->setText( QString("sensor") );
    ui->verticalLayout_3->addWidget( lab1 );
    m_Title.push_back(lab1);

    QLabel *lab2 = new QLabel(this);
    lab2->setText( QString("temp") );
    ui->verticalLayout_3->addWidget(lab2 );
    m_Title.push_back(lab2);
    */

    for (int i=0; i<14; i++)
    {
        ValueSetWidget *val =  new  ValueSetWidget();
        val->init( 30 + i, CSS_TEMPVALUE, 0.5 );
        ui->verticalLayout_3->addWidget( val);
    }
}

pWaterTemp::~pWaterTemp()
{
    delete ui;
}

