#include "cwidgettair.h"
#include "ui_widgetvl.h"
#include "css.h"

CWidgetTAir::CWidgetTAir(QWidget *parent) :
    CwidgetVL ( parent )
{
    qDebug() << "WATER";

    ui->scrollAreaWidgetContents->setStyleSheet( CSS_PAGE );

    ui->label_header->setText("Temperature Stanze");
    ui->label_header->setStyleSheet( CSS_HEADER );
    ui->label_header->setMargin(5);

    ui->label_footer->setText("----");
    ui->label_footer->setStyleSheet( CSS_HEADER );
    ui->label_header->setMargin(5);

    for (int i=0; i<5; i++)
    {
        ValueSetWidget *val =  new  ValueSetWidget();
        val->init( 10 + i, 10 + i, CSS_TEMPVALUE, 0.5 );
        ui->verticalLayout_3->addWidget( val );
    }

    for (int i=0; i<5; i++)
    {
        ValueWidget *val =  new  ValueWidget();
        val->init( i, CSS_TEMPVALUE );
        ui->verticalLayout_3->addWidget( val );
    }
}
