#pragma once
#include <qplaintextedit.h>

class LogMessage : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit LogMessage(QWidget *parent = nullptr)
    {
        if(parent){};
        this->setMaximumBlockCount(1000);
    }

    void appendMessage(const QString& text);
};

