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

    void init( int index, QString style );

    void display( float val);
    void label( QString label );

protected:
    //contained widgets:
    QHBoxLayout *m_Layout;

    QLabel *m_label;
    QLCDNumber *m_value;

    int m_dataIndex;

signals:
    //MyWidget's signals....

public slots:
    void onValueChanged();
    //MyWidget's slots example:
    // void firstButtonClicked();
    //...
};
