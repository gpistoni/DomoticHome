#pragma once

#include <QObject>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>

#include "DataVars.h"

class Q_WIDGETS_EXPORT InfoTempSetpoint : public QWidget
{
    Q_OBJECT

    VarF3SP *var;

private:
    QLabel *text;
    QLabel *value;
    QLabel *value1;
    QLabel *value2;

    QPushButton *butp;
    QLabel *setpoint;
    QPushButton *butm;


public:
    explicit InfoTempSetpoint(VarF3SP *v);
    virtual ~InfoTempSetpoint(){}

    void SetColor();

public slots:
    void onClicked();
    void Update();


};
