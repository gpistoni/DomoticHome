#include "pAirTemp.h"
#include "ui_pairtemp.h"

pAirTemp::pAirTemp(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::pAirTemp)
{
    ui->setupUi(this);

    ui->label_header->setText("AIR TEMP");
    ui->label_footer->setText("----");
}

pAirTemp::~pAirTemp()
{
    delete ui;
}
