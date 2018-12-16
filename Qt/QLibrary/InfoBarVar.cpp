#include "InfoBarVar.h"

InfoBarVar::InfoBarVar(VarF3 *v): QWidget()
{
    var3 = v;

    //button = new QPushButton();
    text = new QLabel();    //use a label to host the icon
    value = new QLabel();
    value1 = new QLabel();
    value2 = new QLabel();
    pbar = new QProgressBar();

    // connect(button, SIGNAL(clicked()), this, SLOT(onClicked()));

    QHBoxLayout * hl = new QHBoxLayout();
    text->setText(var3->m_descr);
    hl->addWidget(text);
    value->setText(QString::number(var3->m_value));
    hl->addWidget(value);
    value1->setText(QString::number(var3->m_value1));
    hl->addWidget(value1);
    value2->setText(QString::number(var3->m_value2));
    hl->addWidget(value2);
    //--------------------------------------------------------
    pbar->setMinimum(0);
    pbar->setMaximum(3000);
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
    value = new QLabel();
    pbar = new QProgressBar();

    // connect(button, SIGNAL(clicked()), this, SLOT(onClicked()));

    QHBoxLayout * hl = new QHBoxLayout();
    text->setText(var1->m_descr);
    hl->addWidget(text);
    value->setText(QString::number(var1->m_value));
    hl->addWidget(value);
    //--------------------------------------------------------
    pbar->setMinimum(0);
    pbar->setMaximum(3000);
    pbar->setValue((int)var1->m_value);
    hl->addWidget(pbar);

    setLayout(hl);
    SetColor();
}

void InfoBarVar::SetColor( )
{
    QPalette pal = this->palette();
    pal.setColor(backgroundRole(), QColor(Qt::cyan));
    if (var1 && var1->m_value>0 )
        pal.setColor(backgroundRole(), QColor(Qt::green));
    if (var3 && var3->m_value>0 )
        pal.setColor(backgroundRole(), QColor(Qt::green));
    setAutoFillBackground(true);
    setPalette(pal);
    update();
}

void InfoBarVar::Update()
{
    if (var1)
    {
        value->setText(QString::number(var1->m_value));
    }
    if (var3)
    {
        value->setText(QString::number(var3->m_value));
        value1->setText(QString::number(var3->m_value1));
        value2->setText(QString::number(var3->m_value2));
    }
}
