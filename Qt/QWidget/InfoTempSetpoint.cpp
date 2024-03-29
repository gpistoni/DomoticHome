#include "InfoTempSetpoint.h"

InfoTempSetpoint::InfoTempSetpoint(VarF3SP *v): QWidget()
{
    var = v;

    //button = new QPushButton();
    text = new QLabel();    //use a label to host the icon
    value = new QLabel();
    value1 = new QLabel();
    value2 = new QLabel();

    butp= new QPushButton();
    setpoint= new QLabel();
    butm= new QPushButton();

   // connect(button, SIGNAL(clicked()), this, SLOT(onClicked()));

    QHBoxLayout * hl = new QHBoxLayout();
    text->setText(var->m_descr);
    text->setMinimumWidth(150);
    hl->addWidget(text);
    value->setText(QString::number(var->m_value));
    value->setMinimumWidth(50);
    hl->addWidget(value);
    value1->setText(QString::number(var->m_value1));
    value1->setMinimumWidth(50);
    hl->addWidget(value1);
    butp->setText("+");
    hl->addWidget(butp);
    setpoint->setText(QString::number(var->m_setpoint));
    setpoint->setMinimumWidth(50);
    hl->addWidget(setpoint);
    butm->setText("-");
    hl->addWidget(butm);

    setLayout(hl);
    SetColor();
}

void InfoTempSetpoint::onClicked()
{
    //    QPushButton *button = (QPushButton *)sender();
    if(var->m_value)
        var->m_value = 0;
    else
        var->m_value = 1;
    SetColor();
}

void InfoTempSetpoint::SetColor( )
{
    QPalette pal = this->palette();
    pal.setColor(backgroundRole(), QColor(Qt::cyan));
    if (var->m_value )
        pal.setColor(backgroundRole(), QColor(Qt::lightGray));
    setAutoFillBackground(true);
    setPalette(pal);
    update();
}

void InfoTempSetpoint::Update()
{
    value->setText(QString::number(var->m_value));
    value1->setText(QString::number(var->m_value1));
    value2->setText(QString::number(var->m_value2));
}

