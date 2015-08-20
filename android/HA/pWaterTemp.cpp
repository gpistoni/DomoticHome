#include "css.h"
#include "pWaterTemp.h"
#include "ui_pWaterTemp.h"

pWaterTemp::pWaterTemp(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::WaterTemp)
{
    ui->setupUi(this);

    ui->scrollAreaWidgetContents->setStyleSheet( CSS_PAGE );

    ui->label_header->setText("WATER TEMP");
    ui->label_header->setStyleSheet( CSS_HEADER );
    ui->label_header->setMargin(5);

    ui->label_footer->setText("----");
    ui->label_footer->setStyleSheet( CSS_HEADER );
    ui->label_header->setMargin(5);

    std::shared_ptr<QLabel> lab1( new QLabel(this) );
    lab1->setText( QString("sensor"));
    ui->gridLayout->addWidget(lab1.get(), 0, 0, 1, 1);
    m_Labels.push_back(lab1);

    std::shared_ptr<QLabel> lab2( new QLabel(this) );
    lab2->setText( QString("temp"));
    ui->gridLayout->addWidget(lab2.get(), 0, 1, 1, 1);
    m_Labels.push_back(lab2);


    for (int i=1; i<10; i++)
    {
        std::shared_ptr<QLabel> lab( new QLabel(this) );
        lab->setText( QString("label_%1").arg( QString::number(i)) );
        ui->gridLayout->addWidget(lab.get(), i, 0, 1, 1);
        m_Labels.push_back(lab);

        std::shared_ptr<QLCDNumber> lcd( new QLCDNumber(this) );
        lcd->setDigitCount(4);
        lcd->display( 0.5 + i*i );
        ui->gridLayout->addWidget(lcd.get(), i, 1, 1, 1);
        m_LcdNumber.push_back(lcd);
    }
}

pWaterTemp::~pWaterTemp()
{
    delete ui;
}
