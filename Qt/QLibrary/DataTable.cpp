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
        QFile f("/var/log/dh.log");
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
