#pragma once

#include <QObject>
#include <QPushButton>
#include <QHBoxLayout>
#include <QProgressBar>
#include <QLabel>
#include "DataVars.h"

class Q_WIDGETS_EXPORT InfoBarVar : public QWidget
{
    Q_OBJECT

    VarF3 *var;

private:
    QLabel *text;
    QLabel *value;
    QLabel *value1;
    QLabel *value2;

    QProgressBar *pbar;

public:
    explicit InfoBarVar(VarF3 *v);
    virtual ~InfoBarVar(){}

    void SetColor();

public slots:
    void onClicked();
    void Update();

};
