#ifndef WIDGETVL_H
#define WIDGETVL_H

#include <QWidget>

namespace Ui {
class widgetVL;
}

class widgetVL : public QWidget
{
    Q_OBJECT

public:
    explicit widgetVL(QWidget *parent = 0);
    ~widgetVL();

private:
    Ui::widgetVL *ui;
};

#endif // WIDGETVL_H
