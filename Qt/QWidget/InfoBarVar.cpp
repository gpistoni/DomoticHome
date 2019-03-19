#include "InfoBarVar.h"

InfoBarVar::InfoBarVar(VarF3 *v): QWidget()
{
    var3 = v;

    text = new QLabel();    //use a label to host the icon
    tvalue = new QLabel();
    tvalue1 = new QLabel();
    tvalue2 = new QLabel();
    pbar = new QProgressBar();

    // connect(button, SIGNAL(clicked()), this, SLOT(onClicked()));

    QHBoxLayout * hl = new QHBoxLayout();
    text->setMinimumWidth(150);
    text->setText(var3->m_descr);
    hl->addWidget(text);

    tvalue->setMinimumWidth(50);
    tvalue->setText(QString::number(var3->m_value));
    hl->addWidget(tvalue);

    tvalue1->setMinimumWidth(50);
    tvalue1->setText(QString::number(var3->m_value1));
    hl->addWidget(tvalue1);

    tvalue2->setMinimumWidth(50);
    tvalue2->setText(QString::number(var3->m_value2));
    hl->addWidget(tvalue2);

    //--------------------------------------------------------
    pbar->setMinimum(var3->m_min);
    pbar->setMaximum(var3->m_max);
    pbar->setValue((int)var3->m_value);
    hl->addWidget(pbar);

    setLayout(hl);
    SetColor();
}

InfoBarVar::InfoBarVar(VarF *v): QWidget()
{
    var1 = v;

    //button = new QPushButton();
    text = new QLabel();    //use a label to host the icon
    tvalue = new QLabel();
    pbar = new QProgressBar();

    // connect(button, SIGNAL(clicked()), this, SLOT(onClicked()));

    QHBoxLayout * hl = new QHBoxLayout();
    text->setMinimumWidth(150);
    text->setText(var1->m_descr);
    hl->addWidget(text);

    tvalue->setMinimumWidth(50);
    hl->addWidget(tvalue);

    //--------------------------------------------------------
    pbar->setMinimum(var1->m_min);
    pbar->setMaximum(var1->m_max);
    pbar->setValue((int)var1->m_value);
    hl->addWidget(pbar);

    setLayout(hl);
    SetColor();
}

void InfoBarVar::SetColor( )
{
    QPalette pal = this->palette();

    pal.setColor(backgroundRole(),QColor(240,240,240));
    if (var1 && var1->m_value>0 )
        pal.setColor(backgroundRole(), QColor(240,240,255));
    if (var3 && var3->m_value>0 )
        pal.setColor(backgroundRole(), QColor(240,240,255));

    setAutoFillBackground(true);
    setPalette(pal);
    update();
}

void InfoBarVar::Update()
{
    if (var1)
    {
        pbar->setValue((int)var1->m_value);
        tvalue->setText(QString::number(var1->m_value));
    }
    if (var3)
    {
        pbar->setValue((int)var3->m_value);
        tvalue->setText(QString::number(var3->m_value));
        tvalue1->setText(QString::number(var3->m_value1));
        tvalue2->setText(QString::number(var3->m_value2));
    }
}
