#pragma once

#include <memory>

#include <QScrollArea>
#include <QLabel>
#include <QLCDNumber>
#include <QThread>
#include <QDebug>
#include <QStringList>

#include "Lib/valueWidget.h"

namespace Ui {
class WaterTemp;
class WorkerThread;
}

//*************************************************************************************************************
class pWaterTemp : public QScrollArea
{
    Q_OBJECT

public:
    explicit pWaterTemp(QWidget *parent = 0);
    ~pWaterTemp();

private:
    std::vector< QLabel* >         m_Title;
    std::vector< ValueWidget* >    m_valueNumber;

    Ui::WaterTemp *ui;

};
