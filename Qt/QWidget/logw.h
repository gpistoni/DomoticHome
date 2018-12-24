#pragma once
#include <qplaintextedit.h>

class LogW : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit LogW(QWidget *parent = nullptr) {}

    /* snip */
    void appendMessage(const QString& text);
};


void LogW::appendMessage(const QString& text)
{
    this->appendPlainText(text); // Adds the message to the widget
    //this->verticalScrollBar()->setValue(this->verticalScrollBar()->maximum()); // Scrolls to the bottom
}
