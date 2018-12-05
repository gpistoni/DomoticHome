#pragma once

#include <QObject>
#include <QPushButton>
#include <QHBoxLayout>

#include <QLabel>
#include "DataVars.h"

class Q_WIDGETS_EXPORT InfoBarVar : public QWidget
{
    Q_OBJECT

    VarI3 *var;

private:
    QLabel *text;
    QLabel *value;
    QLabel *value1;
    QLabel *value2;

public:
    explicit InfoBarVar(VarI3 *v);
    virtual ~InfoBarVar(){}

    void SetColor();

public slots:
    void onClicked();

};
