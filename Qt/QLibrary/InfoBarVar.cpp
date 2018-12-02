#include "InfoBarVar.h"

InfoBarVar::InfoBarVar(VarI *v): QWidget()
{
    var = v;

    //button = new QPushButton();
    text = new QLabel();    //use a label to host the icon
    value = new QLabel();

   // connect(button, SIGNAL(clicked()), this, SLOT(onClicked()));

    QHBoxLayout * hl = new QHBoxLayout();
    text->setText(var->m_descr);
    hl->addWidget(text);
    value->setText(QString::number(var->m_value));
    hl->addWidget(value);

    setLayout(hl);
    SetColor();
}

void InfoBarVar::onClicked()
{
    //    QPushButton *button = (QPushButton *)sender();
    if(var->m_value)  var->m_value = 0;
    else              var->m_value = 1;

    SetColor();
}

void InfoBarVar::SetColor( )
{
    QPalette pal = this->palette();
    pal.setColor(backgroundRole(), QColor(Qt::cyan));
    if (var->m_value )
        pal.setColor(backgroundRole(), QColor(Qt::green));
    setAutoFillBackground(true);
    setPalette(pal);
    update();
}
