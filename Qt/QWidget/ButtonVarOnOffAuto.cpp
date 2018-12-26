#include "ButtonVarOnOffAuto.h"
#include <QSpacerItem>

ButtonVarOnOffAuto::ButtonVarOnOffAuto(VarB *v): ButtonVar(v)
{
    buttonAUTO = new QPushButton();
    connect(buttonAUTO, SIGNAL(clicked()), this, SLOT(onClicked()));

    QHBoxLayout * hl = new QHBoxLayout();
    buttonAUTO->setText("A");
    buttonAUTO->setLayout(hl);

    m_gl.addWidget(buttonAUTO);

    setLayout(&m_gl);
    SetColor();
}

void ButtonVarOnOffAuto::onClicked()
{
    QPushButton *button = static_cast<QPushButton*>(sender());
    if (button==buttonON)
        var->ModifyValue(true);
    if (button==buttonOFF)
        var->ModifyValue(true);
    if (button==buttonAUTO)
        var->ModifyValue(true);
    SetColor();
}

void ButtonVarOnOffAuto::SetColor( )
{
    ButtonVar::SetColor();
    /*
    if (*var )
        buttonFORCE->setPalette(m_pON);
    else
        buttonFORCE->setPalette(m_pOFF);
*/
    update();
}

void ButtonVarOnOffAuto::Update()
{
    SetColor();
    update();
}
