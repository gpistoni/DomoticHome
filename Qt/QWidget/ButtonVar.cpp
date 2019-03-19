#include "ButtonVar.h"
#include <QSpacerItem>

StdButton::StdButton(): QWidget()
{
    m_pON.setColor(QPalette::Button, QColor(Qt::green));
    m_pOFF.setColor(QPalette::Button, QColor(Qt::darkGray));
    m_pDIS.setColor(QPalette::Button, QColor(Qt::lightGray));
}


ButtonVar::ButtonVar(VarB *v)
{
    var = v;

    text = new QLabel();
    buttonON = new QPushButton();
    buttonOFF = new QPushButton();

    connect(buttonON, SIGNAL(clicked()), this, SLOT(onClicked()));
    connect(buttonOFF, SIGNAL(clicked()), this, SLOT(onClicked()));

    text->setMinimumWidth(300);
    text->setText(var->m_descr);

    QHBoxLayout * hl = new QHBoxLayout();
    buttonON->setText("ON");
    buttonON->setLayout(hl);

    buttonOFF->setText("OFF");
    buttonOFF->setLayout(hl);

    QSpacerItem *spacer = new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_gl.addWidget(text);
    m_gl.addSpacerItem(spacer);
    m_gl.addWidget(buttonOFF);
    m_gl.addWidget(buttonON);

    setLayout(&m_gl);
    SetColor();
}

void ButtonVar::onClicked()
{
    QPushButton *button = static_cast<QPushButton*>(sender());
    if (button==buttonON)
        var->ModifyValue(true);
    if (button==buttonOFF)
        var->ModifyValue(false);
    SetColor();
}

void ButtonVar::SetColor( )
{
    if (*var)
    {
        buttonON->setPalette(m_pON);
        buttonOFF->setPalette(m_pDIS);
    }
    else
    {
        buttonON->setPalette(m_pDIS);
        buttonOFF->setPalette(m_pOFF);
    }
    update();
}

void ButtonVar::Update()
{
    SetColor();
}
