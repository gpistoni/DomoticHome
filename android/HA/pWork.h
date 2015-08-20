#ifndef PWORK_H
#define PWORK_H

#include <QScrollArea>

namespace Ui {
class Work;
}

class pWork : public QScrollArea
{
    Q_OBJECT

public:
    explicit pWork(QWidget *parent = 0);
    ~pWork();

private:
    Ui::Work *ui;
};

#endif // PWORK_H
