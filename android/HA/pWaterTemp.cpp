#include "css.h"
#include "pWaterTemp.h"
#include "ui_pWaterTemp.h"
#include "Lib/valueWidget.h"

pWaterTemp::pWaterTemp(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::WaterTemp)
{
    qDebug() << "WATER";

    ui->setupUi(this);

    ui->scrollAreaWidgetContents->setStyleSheet( CSS_PAGE );

    ui->label_header->setText("WATER TEMP");
    ui->label_header->setStyleSheet( CSS_HEADER );
    ui->label_header->setMargin(5);

    ui->label_footer->setText("----");
    ui->label_footer->setStyleSheet( CSS_HEADER );
    ui->label_header->setMargin(5);

    QLabel *lab1 = new QLabel(this);
    lab1->setText( QString("sensor"));
    ui->gridLayout->addWidget( lab1, 0, 0, 1, 1);
    m_Title.push_back(lab1);

    QLabel *lab2 = new QLabel(this);
    lab2->setText( QString("temp"));
    ui->gridLayout->addWidget(lab2, 0, 1, 1, 1);
    m_Title.push_back(lab2);

    for (int i=0; i<10; i++)
    {
        ValueWidget *val =  new  ValueWidget();
        val->init( QString("label_%1").arg( QString::number(i)), "@get(2,0)" );
        ui->gridLayout->addWidget( val, i+1, 0, 1, 1);
    }
}

pWaterTemp::~pWaterTemp()
{
    delete ui;
}

void pWaterTemp::onValueCh()
{
    qDebug() << "onValueCh";
}

void pWaterTemp::onValueChagned()
{
/*    qDebug() << "onValueChagned";
    qDebug() << data.values["val0"];

    std::map<QString,double>::iterator iter = data.values.begin();

    for (size_t i=0; i<m_valueNumber.size() && iter!= data.values.end(); i++ )
    {
        m_valueNumber[i]->display( iter->second );
        m_valueNumber[i]->label( iter->first );
        iter++;
    }

    ui->label_footer->setText( QString::number(data.values[0]) );
    */
}

void pWaterTemp::on_pushUpdate_clicked()
{
    //QString res = DHRequets::sendRequest(  QUrl(QString("http://ip.jsontest.com/")) );
    QString res = DHRequets::sendRequest(  QUrl(QString("https://www.google.com")) );
    ui->label_footer->setText( res );
}
