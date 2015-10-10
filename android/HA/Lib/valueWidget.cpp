#include "valueWidget.h"
#include "../css.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLCDNumber>
#include "data.h"

extern CData gData;

//class MyWidget : public QWidget //inherit from QWidget
//{
//    Q_OBJECT
//public:
//    MyWidget(QWidget* parent = 0); //don't forget to pass the parent

//private:
//    QVBoxLayout *mainLayout;
//    QHBoxLayout *anotherLayout;
//    QLabel *firstLabel;
//    QLabel *secondLabel;
//    QPushButton *firstButton;
//    QPushButton *secondButton;
//signals:
//    //MyWidget's signals....
//public slots:
//    //MyWidget's slots example:
//    // void firstButtonClicked();
//    //...
//};


//MyWidget::MyWidget(QWidget* parent) : QWidget(parent)
//{
//    mainLayout = new QVBoxLayout(this);
//    anotherLayout = new QHBoxLayout();

//    firstLabel = new QLabel("first label");
//    secondLabel = new QLabel("second label");
//    firstButton = new QPushButton("Fist button");
//    secondButton = new QPushButton("Second Button");

//    mainLayout->addWidget(firstLabel);
//    mainLayout->addWidget(firstButton);
//    mainLayout->addLayout(anotherLayout);
//    anotherLayout->addWidget(secondLabel);
//    anotherLayout->addWidget(secondButton);
//}

ValueWidget::ValueWidget(QWidget* parent) : QWidget(parent)
{
    m_Layout = new QHBoxLayout(this);
    m_label = new QLabel("Label");
    m_value = new QLCDNumber( 3 );

    m_Layout->addWidget(m_label);
    m_Layout->addWidget(m_value);

    connect( &gData, SIGNAL(sigChanged()), this, SLOT(onValueChanged()) );
}


void ValueWidget::init(int idx, QString style )
{
    m_dataIndex = idx;

    m_label->setText( gData.GetL( idx ) );
    m_value->display( gData.GetV( idx ) );

    m_value->setStyleSheet( CSS_LCDDISPLAY );

    setStyleSheet( style );
}

void ValueWidget::display( float val)
{
    m_value->display( val );
}

void ValueWidget::label( QString label )
{
    m_label->setText( label );
}

 void ValueWidget::onValueChanged()
 {
     m_label->setText( gData.GetL( m_dataIndex ) );
     m_value->display( gData.GetV( m_dataIndex ) );
 }

