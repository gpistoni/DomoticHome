#include "PushButtonVar.h"

PushButtonVar::PushButtonVar(VarI *v): QWidget()
{
    var = v;

    button = new QPushButton();
    //icon = new QLabel(); //use a label to host the icon
    //text = new QLabel();

    connect(button, SIGNAL(clicked()), this, SLOT(onClicked()));

    /*  QHBoxLayout * hl = new QHBoxLayout();
    hl->addWidget(icon);
    text->setText(var->m_descr);
    hl->addWidget(text);*/

    QHBoxLayout * hl = new QHBoxLayout();
    button->setText(var->m_descr);
    button->setLayout(hl);

    QVBoxLayout * gl = new QVBoxLayout();
    gl->addWidget(button);

    setLayout(gl);
    SetColor();
}

void PushButtonVar::onClicked()
{
    //    QPushButton *button = (QPushButton *)sender();
    if(var->m_value)  var->m_value = 0;
    else              var->m_value = 1;

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
