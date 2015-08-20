#ifndef PAIRTEMP_H
#define PAIRTEMP_H

#include <QScrollArea>

namespace Ui {
class pAirTemp;
}

class pAirTemp : public QScrollArea
{
    Q_OBJECT

public:
    explicit pAirTemp(QWidget *parent = 0);
    ~pAirTemp();

private:
    Ui::pAirTemp *ui;
};

#endif // PAIRTEMP_H
