#pragma once
#include <qplaintextedit.h>

class LogMessage : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit LogMessage(QWidget *parent = nullptr)
    {
        this->setMaximumBlockCount(1000);
    }

    /* snip */
    void appendMessage(const QString& text);
};

