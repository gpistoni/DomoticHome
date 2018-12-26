#pragma once

#include <QObject>
#include <QPushButton>
#include <QHBoxLayout>

#include <QLabel>
#include "DataVars.h"

class Q_WIDGETS_EXPORT PushButtonVar : public QWidget
{
    Q_OBJECT

    VarB *var;

private:
    QLabel * text;

    QPushButton *buttonON;
    QPushButton *buttonOFF;

public:
    explicit PushButtonVar(VarB *v);
    virtual ~PushButtonVar(){}

    void SetColor(  );

public slots:
    void onClicked();
    void Update();
};
