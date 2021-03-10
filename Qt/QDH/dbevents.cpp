#include "dbevents.h"
#include "../QLibrary/DataTable.h"
#include <QSqlQuery>

dbEvents::dbEvents()
{    
    QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("/root/dh/domotichome.db");
    m_db.open();


//    QSqlQuery query(m_db);
//    query.exec("CREATE table person (id int primary key, firstname varchar(20), lastname varchar(20))");
//    query.exec("INSERT into person values(101, 'Danny', 'Young') ");
//    query.exec("SELECT * FROM person");
//    m_db.close();

}


void dbEvents::CreateTables()
{
    QSqlQuery query(m_db);
    query.exec("CREATE table energy (date DATETIME primary key, produced INT, consumed INT, consumedL1 INT, consumedL2 INT, consumedL3 INT )");
    query.exec("CREATE table temperature (date DATETIME primary key, PufferHi REAL, PufferLow REAL, ReturnFireplace REAL, InletFloor REAL, ReturnFloor REAL, External REAL  )");

    //Per la modifica
    //ALTER TABLE Customers ADD Email varchar(255);
    m_db.close();
}

void dbEvents::LogEnergy(int prod, int cons, int l1, int l2, int l3)
{
    QString str;
    str += "INSERT into energy values ( CURRENT_TIMESTAMP, ";
    str += QString::number(prod);
    str += ",";
    str += QString::number(cons);
    str += ",";
    str += QString::number(l1);
    str += ",";
    str += QString::number(l2);
    str += ",";
    str += QString::number(l3);
    str += " )";

    QSqlQuery query(m_db);
    query.exec( str );
}

void dbEvents::LogTemperature(DataTable &dt)
{
    QString str;
    str += "INSERT into temperature values ( CURRENT_TIMESTAMP, ";
    str += QString::number(dt.tPufferHi);
    str += ",";
    str += QString::number(dt.tPufferLow);
    str += ",";
    str += QString::number(dt.tReturnFireplace);
    str += ",";
    str += QString::number(dt.tReturnFloor);
    str += ",";
    str += QString::number(dt.tInletFloor);
    str += ",";
    str += QString::number(dt.tExternal);
    str += " )";

    QSqlQuery query(m_db);
    query.exec( str );
}
