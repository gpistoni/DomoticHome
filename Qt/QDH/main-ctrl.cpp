#include "DataReader.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DataReader DR;

    DR.ReadData();

    qDebug() << "PROVA: " << DR.GetValue("T1", "name").toString();

    getchar();
    return a.exec();
}
