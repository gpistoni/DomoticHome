#pragma once

#include <QObject>
#include <QPushButton>
#include <QHBoxLayout>

#include <QLabel>
#include "DataVars.h"

class Q_WIDGETS_EXPORT InfoBarVar : public QWidget
{
    Q_OBJECT

    VarI *var;

private:
    QLabel *text;
    QLabel *value;

public:
    explicit InfoBarVar(VarI *v);
    virtual ~InfoBarVar(){}

    void SetColor(  );

public slots:
    void onClicked();

};
