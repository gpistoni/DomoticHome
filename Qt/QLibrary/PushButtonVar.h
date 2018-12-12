#pragma once

#include <QObject>
#include <QPushButton>
#include <QHBoxLayout>

#include <QLabel>
#include "DataVars.h"

class Q_WIDGETS_EXPORT PushButtonVar : public QWidget
{
    Q_OBJECT

    VarI *var;

private:
    QPushButton *button;
    //QLabel * icon;
    //QLabel * text;

public:
    explicit PushButtonVar(VarI *v);
    virtual ~PushButtonVar(){}

    void SetColor(  );

public slots:
    void onClicked();
    void Update();


};
