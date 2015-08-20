#include "css.h"
#include "pWaterTemp.h"
#include "ui_pWaterTemp.h"

pWaterTemp::pWaterTemp(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::WaterTemp)
{
    ui->setupUi(this);

    ui->scrollAreaWidgetContents->setStyleSheet( CSS_GRID );

    ui->label_header->setText("WATER TEMP");
    ui->label_footer->setText("----");

    for (int i=0; i<10; i++)
    {
        std::shared_ptr<QLabel> lab( new QLabel(this) );
        lab->setText( QString("label_%1").arg( QString::number(i)) );

        lab->setStyleSheet("background-color:darkgray;color:black;");

        ui->gridLayout->addWidget(lab.get(), i, 0, 1, 1);
        m_Labels.push_back(lab);

        std::shared_ptr<QLCDNumber> lcd( new QLCDNumber(this) );
        lcd->setDigitCount(4);
        lcd->display( 0.5 + i );
        ui->gridLayout->addWidget(lcd.get(), i, 1, 1, 1);
        m_LcdNumber.push_back(lcd);
    }
}

pWaterTemp::~pWaterTemp()
{
    delete ui;
}
