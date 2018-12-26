#pragma once

#include <QObject>
#include <QPushButton>
#include <QHBoxLayout>

#include <QLabel>
#include "../QLibrary/DataVars.h"

class Q_WIDGETS_EXPORT ButtonVar : public QWidget
{
    Q_OBJECT

protected:
    QPalette m_pON;
    QPalette m_pOFF;
    QPalette m_pDIS;

    VarB *var;
    QHBoxLayout m_gl;

    QLabel * text;

    QPushButton *buttonON;
    QPushButton *buttonOFF;

public:
    explicit ButtonVar(VarB *v);
    virtual ~ButtonVar(){}

    void SetColor(  );

public slots:
    void onClicked();
    void Update();
};
