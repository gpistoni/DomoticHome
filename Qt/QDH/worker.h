#ifndef CWORKER_H
#define CWORKER_H

#include <QObject>
#include "../QLibrary/DataTable.h"

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
    void updateValues(DataTable *v);
    void updateListView(DataTable *v);
};


#endif // CWORKER
