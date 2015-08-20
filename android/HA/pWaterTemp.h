#ifndef PWATERTEMP_H
#define PWATERTEMP_H
#include <memory>

#include <QScrollArea>
#include <QLabel>
#include <QLCDNumber>
#include <QThread>

namespace Ui {
class WaterTemp;
}

class pWaterTemp : public QScrollArea, QThread
{
    Q_OBJECT

public:
    explicit pWaterTemp(QWidget *parent = 0);
    ~pWaterTemp();

private:
    std::vector<std::shared_ptr<QLabel>>        m_Labels;
    std::vector<std::shared_ptr<QLCDNumber>>    m_LcdNumber;

    Ui::WaterTemp *ui;
};

#endif // PWATERTEMP_H
