#pragma once

#include <QWidget>
#include <QTimer>
#include "valueWidget.h"

class ValueSetWidget : public ValueWidget //inherit from QWidget
{
    Q_OBJECT

public:
    ValueSetWidget(QWidget* parent = 0); //don't forget to pass the parent
    void init( int index, QString style, float increment );

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
