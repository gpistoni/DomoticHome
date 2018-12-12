#include "InfoBarVar.h"

InfoBarVar::InfoBarVar(VarF3 *v): QWidget()
{
    var = v;

    //button = new QPushButton();
    text = new QLabel();    //use a label to host the icon
    value = new QLabel();
    value1 = new QLabel();
    value2 = new QLabel();
     pbar = new QProgressBar();

   // connect(button, SIGNAL(clicked()), this, SLOT(onClicked()));

    QHBoxLayout * hl = new QHBoxLayout();
    text->setText(var->m_descr);
    hl->addWidget(text);
    value->setText(QString::number(var->m_value));
    hl->addWidget(value);
    value1->setText(QString::number(var->m_value1));
    hl->addWidget(value1);
    value2->setText(QString::number(var->m_value2));
    hl->addWidget(value2);
    //--------------------------------------------------------
    pbar->setMinimum(0);
    pbar->setMaximum(3000);
    pbar->setValue((int)var->m_value);
    hl->addWidget(pbar);

    setLayout(hl);
    SetColor();
}

void InfoBarVar::onClicked()
{
    //    QPushButton *button = (QPushButton *)sender();
    if(var->m_value)
        var->m_value = 0;
    else
        var->m_value = 1;
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

void InfoBarVar::Update()
{
    value->setText(QString::number(var->m_value));
    value1->setText(QString::number(var->m_value1));
    value2->setText(QString::number(var->m_value2));
}
