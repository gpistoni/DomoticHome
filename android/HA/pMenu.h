#ifndef PMAIN_H
#define PMAIN_H

#include <QScrollArea>

namespace Ui {
class pMain;
}

class pMenu : public QScrollArea
{
    Q_OBJECT

public:
    explicit pMenu(QWidget *parent = 0);
    ~pMenu();

private:
    Ui::pMain *ui;
};

#endif // PMAIN_H
