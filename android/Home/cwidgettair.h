#ifndef CWIDGETTAIR_H
#define CWIDGETTAIR_H

#include <QScrollArea>
#include <QLabel>
#include <QLCDNumber>
#include <QThread>
#include <QDebug>
#include "../libraries/valueSetWidget.h"

#include "cwidgetvl.h"

namespace Ui {
class CWidgetTAir;
}

class CWidgetTAir : public CwidgetVL
{
public:
    CWidgetTAir( QWidget *parent = 0 );

protected:
    std::vector< QLabel* >         m_Title;
    std::vector< ValueSetWidget* >    m_valueNumber;
};

#endif // CWIDGETTAIR_H
