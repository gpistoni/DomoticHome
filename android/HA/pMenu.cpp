#include "pMenu.h"
#include "ui_pMenu.h"

pMenu::pMenu(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::pMain)
{
    ui->setupUi(this);

    ui->label_header->setText("MENU");
    ui->label_footer->setText("----");
}

pMenu::~pMenu()
{
    delete ui;
}
