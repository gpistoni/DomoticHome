#pragma once
#include <QObject>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>

#include "ButtonVar.h"
#include "../QLibrary/DataVars.h"

class ButtonVarForced : public StdButton
{
    Q_OBJECT
    VarBf *var;

private:
    QLabel * text;

    QPushButton *buttonStatus;
    QPushButton *buttonForceON;
    QPushButton *buttonForceOFF;

public:
    explicit ButtonVarForced(VarBf *v);
    virtual ~ButtonVarForced(){}

    void SetColor(  );

public slots:
    void onClicked();
    void Update();
};
