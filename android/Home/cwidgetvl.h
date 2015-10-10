#ifndef WIDGETVL_H
#define WIDGETVL_H

#include <QWidget>

namespace Ui {
class widgetVL;
}

class CwidgetVL : public QWidget
{
    Q_OBJECT

public:
    explicit CwidgetVL(QWidget *parent = 0);
    ~CwidgetVL();

public:
    Ui::widgetVL *ui;
};

#endif // WIDGETVL_H
