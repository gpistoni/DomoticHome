#ifndef CWORKER_H
#define CWORKER_H

#include <QObject>
#include "../QLibrary/DataReader.h"

class Worker : public QObject
{
    Q_OBJECT

public:
    Worker();
    ~Worker();

public slots:
    void process();

signals:
    void finished();
    void error(QString err);
    void update(DataReader* dr);
};


#endif // CWORKER
