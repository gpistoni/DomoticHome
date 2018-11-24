#pragma once

#include <QObject>
#include <QRunnable>

class CHTTPParser: public QRunnable
{
public:
    CHTTPParser();

protected:
    void run();

public:
    qintptr socketDescriptor;
};
