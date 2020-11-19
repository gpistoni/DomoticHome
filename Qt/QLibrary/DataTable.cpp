#include <QDateTime>
#include "DataTable.h"

void DataTable::LogMessage(QString s, bool logtofile)
{
    QString str;
    str += "\n";
    str += QDateTime::currentDateTime().time().toString();
    str += " ";
    str += s;
    m_logMessage += str;
    std::cerr << str.toStdString();

    if (logtofile)
    {
        QString fname = QString("/var/log/dh_");
        fname += QString::number(QDateTime::currentDateTime().date().month());
        fname += "_";
        int d = QDateTime::currentDateTime().date().day();
        if (d<10)
            fname += "0";
        fname += QString::number(d);
        fname += ".log";
        QFile f(fname);
        if (f.open(QIODevice::WriteOnly | QIODevice::Append))
        {
            f.write(str.toLatin1());
        }
    }
}

bool DataTable::GetLogMessage(QString &s)
{
    s = m_logMessage;
    m_logMessage.clear();
    return s.size();
}
