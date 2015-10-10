#include "cwidgetvl.h"
#include "ui_widgetvl.h"

CwidgetVL::CwidgetVL(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widgetVL)
{
    ui->setupUi(this);
}

CwidgetVL::~CwidgetVL()
{
    delete ui;
}
