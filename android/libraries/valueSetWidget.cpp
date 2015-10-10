#include "valueSetWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPushButton>
#include <QLCDNumber>
#include "data.h"

ValueSetWidget::ValueSetWidget(QWidget* parent) : ValueWidget(parent)
{    
    m_plus = new QPushButton( "" );
    m_minus = new QPushButton( "" );

    QIcon icon;
    icon.addFile(QStringLiteral(":/icons/icons/up.svg"), QSize(), QIcon::Normal, QIcon::Off);
    m_plus->setIcon(icon);
    m_plus->setFlat(true);

    QIcon icon2;
    icon2.addFile(QStringLiteral(":/icons/icons/down.svg"), QSize(), QIcon::Normal, QIcon::Off);
    m_minus->setIcon(icon2);
    m_minus->setFlat(true);


    m_plus->setMinimumWidth( 40 );
    m_plus->setMaximumWidth( 100 );
    m_minus->setMinimumWidth( 40 );
    m_plus->setMaximumWidth( 100 );

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

    m_label->setText( gData->GetL( idx ) );

    m_value->setStyleSheet( style );
    m_value->display( gData->GetV( idx ) );

   // m_plus->setStyleSheet( CSS_BUTTON );
   // m_minus->setStyleSheet( CSS_BUTTON );

    m_value->setPalette(Qt::yellow);
}

void ValueSetWidget::onPlusClicked()
{
    disconnect( gData, SIGNAL(sigChanged()), this, SLOT(onValueChanged()) );
    m_timer.stop();
    m_timer.start(5000);

    m_value->setPalette(Qt::red);
    QString label =  gData->GetL( m_dataIndex );

    float setpoint = gData->GetVsetpoint(label) + m_increment ;
    gData->SetVsetpoint(  label, setpoint );
    m_value->display( setpoint );
}

void ValueSetWidget::onMinusClicked()
{
    disconnect( gData, SIGNAL(sigChanged()), this, SLOT(onValueChanged()) );
    m_timer.stop();
    m_timer.start(5000);

    m_value->setPalette(Qt::red);
    QString label =  gData->GetL( m_dataIndex );

    float setpoint = gData->GetVsetpoint(label) - m_increment ;
    gData->SetVsetpoint(  label, setpoint );
    m_value->display( setpoint );
}

void ValueSetWidget::onTimerTimeout()
{
   m_timer.stop();
   connect( gData, SIGNAL( sigChanged() ), this, SLOT( onValueChanged() ) );

   m_value->setPalette(Qt::yellow);
   onValueChanged();
}
