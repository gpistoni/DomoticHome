#include "PushButtonVar.h"
#include <QSpacerItem>

PushButtonVar::PushButtonVar(VarB *v): QWidget()
{
    var = v;

    text = new QLabel();
    buttonON = new QPushButton();
    buttonOFF = new QPushButton();

    connect(buttonON, SIGNAL(clicked()), this, SLOT(onClicked()));
    connect(buttonOFF, SIGNAL(clicked()), this, SLOT(onClicked()));

    text->setText(var->m_descr);

    QHBoxLayout * hl = new QHBoxLayout();
    buttonON->setText("ON");
    buttonON->setLayout(hl);

    buttonOFF->setText("OFF");
    buttonOFF->setLayout(hl);

    QSpacerItem *spacer = new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Fixed);

    QHBoxLayout * gl = new QHBoxLayout();
    gl->addWidget(text);
    gl->addSpacerItem(spacer);
    gl->addWidget(buttonOFF);
    gl->addWidget(buttonON);

    setLayout(gl);
    SetColor();
}

void PushButtonVar::onClicked()
{
    //    QPushButton *button = (QPushButton *)sender();
    if(var->m_value)
        var->m_value = 0;
    else
        var->m_value = 1;

    SetColor();
}

void PushButtonVar::SetColor( )
{
    QPalette pal = this->palette();
    pal.setColor(QPalette::Button, QColor(Qt::cyan));
    if (var->m_value )
        pal.setColor(QPalette::Button, QColor(Qt::green));
    //setAutoFillBackground(true);
    setPalette(pal);
    update();
}

void PushButtonVar::Update()
{
  SetColor();
}
