#pragma once

#include <QObject>
#include <QPushButton>
#include "DataVars.h"

class PushButtonVar : public QPushButton
{
    //Q_OBJECT
    VarI *var;

public:
    PushButtonVar(VarI *v): QPushButton()
    {
        var = v;
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        setText(var->m_descr);

        setAutoFillBackground(true);
        QPalette palette = this->palette();
        if (var->m_value==0)
            palette.setColor(QPalette::Window, QColor(Qt::darkGray));
        else if (var->m_value==1)
            palette.setColor(QPalette::Window, QColor(Qt::green));
        setPalette(palette);

        connect( SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    }
    virtual ~PushButtonVar(){}

private slots:
    void onButtonClicked()
    {
        //    QPushButton *button = (QPushButton *)sender();
        var->m_value = !var->m_value;

        QPalette palette = this->palette();
        if (var->m_value==0)
            palette.setColor(QPalette::Window, QColor(Qt::darkGray));
        else if (var->m_value==1)
            palette.setColor(QPalette::Window, QColor(Qt::green));
        setPalette(palette);
    }

};
