#ifndef CWIDGETTWATER_H
#define CWIDGETTWATER_H

#include <QScrollArea>
#include <QLabel>
#include <QLCDNumber>
#include <QThread>
#include <QDebug>
#include "../libraries/valueSetWidget.h"

#include "cwidgetvl.h"

namespace Ui {
class CWidgetTWater;
}

class CWidgetTWater : public CwidgetVL
{
public:
    CWidgetTWater( QWidget *parent = 0 );

protected:
    std::vector< QLabel* >            m_Title;
    std::vector< ValueSetWidget* >    m_temp;
    std::vector< ValueWidget* >       m_humi;
};

#endif // CWIDGETTWATER_H
