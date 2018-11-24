#include "HttpParser.h"
#include <QTcpSocket>

CHTTPParser::CHTTPParser()
{    
}

void CHTTPParser::run()
{
    qDebug( "SocketDescriptor run" );
    if(!socketDescriptor) return;


    QTcpSocket socket;
    socket.setSocketDescriptor(socketDescriptor);

    socket.write("From server: hello world");
    socket.flush();
    socket.waitForBytesWritten();
    socket.close();
}
