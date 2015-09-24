#pragma once
#include <QWidget>

//forward declarations
class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QPushButton;
class QLCDNumber;

class ValueWidget : public QWidget //inherit from QWidget
{
    Q_OBJECT
public:
    ValueWidget(QWidget* parent = 0); //don't forget to pass the parent

    void init( QString label, QString ReadTcpStr );
    void display( float val);
    void label( QString label );

private:
    //contained widgets:
    // QVBoxLayout *V1Layout;
    QHBoxLayout *m_Layout;

    QLabel *m_label;
    QLCDNumber *m_value;

    QString m_readTcpStr;
    //QPushButton *firstButton;
    //QPushButton *secondButton;

signals:
    //MyWidget's signals....

public slots:
    //MyWidget's slots example:
    // void firstButtonClicked();
    //...
};
