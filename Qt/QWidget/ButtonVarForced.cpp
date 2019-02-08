#include "ButtonVarForced.h"
#include <QSpacerItem>

ButtonVarForced::ButtonVarForced(VarBf *v)
{
    var = v;

    text = new QLabel();
    buttonStatus = new QPushButton();
    buttonForceON = new QPushButton();
    buttonForceOFF = new QPushButton();

    connect(buttonStatus, SIGNAL(clicked()), this, SLOT(onClicked()));
    connect(buttonForceON, SIGNAL(clicked()), this, SLOT(onClicked()));
    connect(buttonForceOFF, SIGNAL(clicked()), this, SLOT(onClicked()));

    text->setText(var->m_descr);

    buttonStatus->setText("AUTO");
    buttonStatus->setMinimumWidth(100);
    buttonForceON->setText("ON");
    buttonForceOFF->setText("OFF");

    QSpacerItem *spacer = new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_gl.addWidget(text);
    m_gl.addSpacerItem(spacer);
    m_gl.addWidget(buttonForceOFF);
    m_gl.addWidget(buttonStatus);
    m_gl.addWidget(buttonForceON);

    setLayout(&m_gl);
    SetColor();
}

void ButtonVarForced::onClicked()
{
    QPushButton *button = static_cast<QPushButton*>(sender());
    if (button==buttonStatus)
    {
        if (*var)
            var->ModifyValue(VarBf::tValue::ON);
        else
            var->ModifyValue(VarBf::tValue::OFF);
    }
    if (button==buttonForceOFF)
        var->ModifyValue(VarBf::tValue::FORCE_OFF);
    if (button==buttonForceON)
        var->ModifyValue(VarBf::tValue::FORCE_ON);
    SetColor();
}

void ButtonVarForced::SetColor( )
{
    buttonStatus->setText("AUTO");
    if (*var)
        buttonStatus->setPalette(m_pON);
    else
        buttonStatus->setPalette(m_pOFF);

    if (var->isForceOn())
       {
        buttonForceON->setPalette(m_pON);
        buttonStatus->setText("");
    }
        else
        buttonForceON->setPalette(m_pDIS);

    if (var->isForceOff())
    {
     buttonForceOFF->setPalette(m_pOFF);
     buttonStatus->setText("");
 }
    else
        buttonForceOFF->setPalette(m_pDIS);
    update();
}

void ButtonVarForced::Update()
{
    SetColor();
}
