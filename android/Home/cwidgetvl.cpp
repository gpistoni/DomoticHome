#include "widgetvl.h"
#include "ui_widgetvl.h"

widgetVL::widgetVL(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widgetVL)
{
    ui->setupUi(this);
}

widgetVL::~widgetVL()
{
    delete ui;
}
