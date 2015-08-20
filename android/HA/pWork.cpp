#include "pWork.h"
#include "ui_pWork.h"

pWork::pWork(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::Work)
{
    ui->setupUi(this);
}

pWork::~pWork()
{
    delete ui;
}
