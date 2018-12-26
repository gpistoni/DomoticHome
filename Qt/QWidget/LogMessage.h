#pragma once
#include <qplaintextedit.h>

class LogW : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit LogW(QWidget *parent = nullptr)
    {
        this->setMaximumBlockCount(1000);
    }

    /* snip */
    void appendMessage(const QString& text);
};

