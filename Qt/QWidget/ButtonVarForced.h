#pragma once
#include <QObject>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>

#include "ButtonVar.h"
#include "../QLibrary/DataVars.h"

class Q_WIDGETS_EXPORT ButtonVarOnOffAuto : public ButtonVar
{
    Q_OBJECT

private:
    QPushButton *buttonAUTO;

public:
    explicit ButtonVarOnOffAuto(VarB *v);
    virtual ~ButtonVarOnOffAuto(){}

    void SetColor(  );

public slots:
    void onClicked();
    void Update();
};
