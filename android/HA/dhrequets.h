#ifndef DHREQUETS_H
#define DHREQUETS_H

#include <QUrl>

class DHRequets
{
public:
    DHRequets();
    QString sendRequest( QUrl url );
};

#endif // DHREQUETS_H
