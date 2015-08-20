#ifndef PWATERTEMP_H
#define PWATERTEMP_H

#include <QScrollArea>

namespace Ui {
class WaterTemp;
}

class pWaterTemp : public QScrollArea
{
    Q_OBJECT

public:
    explicit pWaterTemp(QWidget *parent = 0);
    ~pWaterTemp();

private:
    Ui::WaterTemp *ui;
};

#endif // PWATERTEMP_H
