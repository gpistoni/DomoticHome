#include "LogMessage.h"


void LogMessage::appendMessage(const QString& text)
{
    this->appendPlainText(text); // Adds the message to the widget
    //this->verticalScrollBar()->setValue(this->verticalScrollBar()->maximum()); // Scrolls to the bottom
}
