#include "SQlabel.h"
#include <QDebug>
#include <QBitmap>
#include <iostream>

using namespace std;

CSQLabel::CSQLabel(QWidget *parent)
	: QLabel(parent)
{
    this->setAutoFillBackground(true);
	QPalette palette;  
    palette.setColor(QPalette::Background, Qt::gray);
	this->setPalette(palette);
}

CSQLabel::~CSQLabel()
{
}

void CSQLabel::resizeEvent(QResizeEvent *event)
{
    if(event)
        qDebug() << "CSQHttpClient";
}

void CSQLabel::Show(QBitmap image)
{
	this->setPixmap( image );
}
