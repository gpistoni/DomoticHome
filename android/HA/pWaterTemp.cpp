#include "pWaterTemp.h"
#include "ui_pWaterTemp.h"

pWaterTemp::pWaterTemp(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::WaterTemp)
{
    ui->setupUi(this);

    ui->label_header->setText("WATER TEMP");
    ui->label_footer->setText("----");
}

pWaterTemp::~pWaterTemp()
{
    delete ui;
}
