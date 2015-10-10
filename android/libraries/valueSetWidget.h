#pragma once

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QLCDNumber>
#include "valueWidget.h"
#include "data.h"



class ValueSetWidget : public ValueWidget //inherit from QWidget
{
    Q_OBJECT

public:
    ValueSetWidget(QWidget* parent = 0); //don't forget to pass the parent

    void init(int idx, QString style, float increment )
    {
        m_dataIndex = idx;
        m_increment = increment;

        setStyleSheet( style );
        m_label->setText( gData->GetL( idx ) );
        m_value->display( gData->GetV( idx ) );

        m_value->setPalette(Qt::yellow);
    }

private:
    QPushButton *m_plus;
    QPushButton *m_minus;

    float m_increment;
    QTimer m_timer;

signals:
    //MyWidget's signals....

public slots:
    void onPlusClicked();
    void onMinusClicked();
    void onTimerTimeout();

    //MyWidget's slots example:
    // void firstButtonClicked();
    //...
};
