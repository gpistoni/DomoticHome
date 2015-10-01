#include "ValueSetWidget.h"
#include "../css.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPushButton>
#include <QLCDNumber>
#include "data.h"


ValueSetWidget::ValueSetWidget(QWidget* parent) : ValueWidget(parent)
{
    m_plus = new QPushButton("+");
    m_minus = new QPushButton("-");

    m_plus->setMinimumWidth( 40 );
    m_minus->setMinimumWidth( 40 );

    m_Layout->addWidget(m_plus);
    m_Layout->addWidget(m_value);
    m_Layout->addWidget(m_minus);

    connect( m_plus, SIGNAL( clicked() ), this, SLOT( onPlusClicked() ) );
    connect( m_minus, SIGNAL( clicked() ), this, SLOT( onMinusClicked() ) );

    connect( &m_timer, SIGNAL(timeout()), this, SLOT( onTimerTimeout() ) );
}

void ValueSetWidget::init(int idx, QString style, float increment )
{
    m_dataIndex = idx;
    m_increment = increment;

    m_label->setText( g_data.GetL( idx ) );
    m_value->display( g_data.GetV( idx ) );

    m_value->setStyleSheet( CSS_LCDDISPLAY_VALUE );
    setStyleSheet( style );
}

void ValueSetWidget::onPlusClicked()
{
    disconnect( this, SLOT( onValueChanged() ) );

    m_timer.start(2000);

    m_label->setText( g_data.GetL( m_dataIndex ) );
    m_value->display( g_data.GetV( m_dataIndex ) );
}

void ValueSetWidget::onMinusClicked()
{
    disconnect( this, SLOT( onValueChanged() ) );
    m_timer.start(2000);

    m_label->setText( g_data.GetL( m_dataIndex ) );

    float setpoint = g_data.GetVsetpoint( m_dataIndex ) - m_increment ;
    g_data.SetVsetpoint( m_dataIndex, setpoint );
    m_value->display( setpoint );
    m_value->setStyleSheet( CSS_LCDDISPLAY_SETPOINT );
}

void ValueSetWidget::onTimerTimeout()
{
   connect( &g_data, SIGNAL( sigChanged() ), this, SLOT( onValueChanged() ) );
   m_value->setStyleSheet( CSS_LCDDISPLAY_VALUE );
}
