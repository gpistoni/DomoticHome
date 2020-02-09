#ifndef DBEVENTS_H
#define DBEVENTS_H
#include <QSqlDatabase>


class dbEvents
{
public:
    QSqlDatabase m_db;


public:
    dbEvents();

public:
    void CreateTables();
    void LogEnergy(int prod, int cons, int l1, int l2, int l3);

};

#endif // DBEVENTS_H
