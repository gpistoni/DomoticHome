#ifndef DHREQUETS_H
#define DHREQUETS_H

#include <QString.h>
#include <QUrl>

class DHRequets
{
public:
    DHRequets();
    static QString sendRequest( QUrl url );
};

#endif // DHREQUETS_H
