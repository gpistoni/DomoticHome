#pragma once

#include <QObject>
#include <QPushButton>
#include <QHBoxLayout>
#include <QProgressBar>
#include <QLabel>
#include "../QLibrary/DataVars.h"

class InfoBarVar : public QWidget
{
    Q_OBJECT

    VarF  *var1 = nullptr;
    VarF3 *var3 = nullptr;

private:
    QLabel *text = nullptr;
    QLabel *value = nullptr;
    QLabel *value1 = nullptr;
    QLabel *value2 = nullptr;

    QProgressBar *pbar = nullptr;

public:
    explicit InfoBarVar(VarF3 *v);
    explicit InfoBarVar(VarF *v);
    virtual ~InfoBarVar(){}

    void SetColor();

public slots:
     void Update();

};
