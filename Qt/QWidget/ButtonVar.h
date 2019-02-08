#pragma once
#include <QObject>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include "../QLibrary/DataVars.h"

class StdButton : public QWidget
{
protected:
    QPalette m_pON;
    QPalette m_pOFF;
    QPalette m_pDIS;

    QHBoxLayout m_gl;

    StdButton();
};


class Q_WIDGETS_EXPORT ButtonVar : public StdButton
{
    Q_OBJECT

protected:
    VarB *var;

    QLabel * text;

    QPushButton *buttonON;
    QPushButton *buttonOFF;

public:
    explicit ButtonVar(VarB *v);
    virtual ~ButtonVar(){}

    void SetColor();

public slots:
    void onClicked();
    void Update();
};
