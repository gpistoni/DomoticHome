#include "SocketThreadBase.h"


void SocketThreadBase::setRunThread(bool newVal )
{
    QMutexLocker lock( &mMutex );
    mRunThread = newVal;
}

bool SocketThreadBase::getRunThread()
{
    QMutexLocker lock( &mMutex );
    return mRunThread;
}


int SocketThreadBase::waitForInput( QTcpSocket *socket )
{
    int bytesAvail = -1;
    while (socket->state() == QAbstractSocket::ConnectedState && getRunThread() && bytesAvail < 0) {
        if (socket->waitForReadyRead( 100 )) {
            bytesAvail = socket->bytesAvailable();
        }
        else {
            Sleep( 50 );
        }
    }
    return bytesAvail;
}

QString SocketThreadBase::readLine(QTcpSocket *socket )
{
    QString line = "";
    int bytesAvail = waitForInput( socket );
    if (bytesAvail > 0) {
        int cnt = 0;
        bool endOfLine = false;
        bool endOfStream = false;
        while (cnt < bytesAvail && (!endOfLine) && (!endOfStream)) {
            char ch;
            int bytesRead = socket->read(&ch, sizeof(ch));
            if (bytesRead == sizeof(ch)) {
                cnt++;
                line.append( ch );
                if (ch == '\r') {
                    endOfLine = true;
                }
            }
            else {
                endOfStream = true;
            }
        }
    }
    return line;
}


void SocketThreadBase::writeLine(QTcpSocket *socket, const QString &line)
{
    if (line.length() > 0)
    {
        socket->write( line.toLatin1() );
        if (! socket->waitForBytesWritten())
        {
            if (getIdentity() == SERVER)
            {
                qDebug() << "Server - " ;
            }
            else if (getIdentity() == CLIENT)
            {
                qDebug() << "Client - ";
            }
            else
            {
                qDebug() << "Unknown identity - ";
            }
            qDebug() <<  "writeLine: the write to the socket failed\n";
        }
    }
}


/**
  Note that Qt requires that the QTcpServer be in the same thread it is used in.
  So it cannot be declared as a class variable.  It must be in the run thread.
*/
void GenericServer::run()
{
    QHostAddress serverAddr( mIP );
    QTcpServer server;
    if (server.listen(serverAddr, mPort))
    {
        qDebug() << "EchoServer::run: listen() succeeded\n";
        while (server.isListening() && getRunThread())
        {
            if (server.waitForNewConnection(100))
            {
                qDebug() << "EchoServer::run: got a TCP connection";
                QTcpSocket *client = server.nextPendingConnection();
                Reply( client );
                client->close();
            }
            else {
                Sleep( 100 );
            }
        } // while
    }
    else {
        qDebug() << "EchoServer::run: listen operation failed\n";
    }
}

void GenericServer::startThread()
{
    setRunThread( true );
    start();
}

void GenericServer::stopThread()
{
    setRunThread( false );
}


void  GenericClient::setDone(const bool newVal)
{
    QMutexLocker lock( &mMutex );
    mDone = newVal;
}

bool GenericClient::isDone()
{
    QMutexLocker lock( &mMutex );
    return mDone;
}

/**
    Note that the QTcpSocket object must be in the run thread.  It cannot
    be a class variable.
*/
void GenericClient::run()
{
    QTcpSocket socket;
    QHostAddress hostAddr( mIP );
    socket.connectToHost( hostAddr, mPort );
    if (socket.waitForConnected( CONNECT_TIME_OUT ))
    {
        QHostAddress hostAddr = socket.localAddress();
        QString addr = "";
        if (hostAddr != QHostAddress::Null)
        {
            addr = hostAddr.toString();
        }
        printf("Client connected");
        if (addr.length() > 0)
        {
            qDebug() << QString(" on address %s:%04d").arg( addr.toLatin1().data(), socket.localPort() );
        }
        printf("\n");
        int ix = 0;
        while (socket.state() == QAbstractSocket::ConnectedState && ix < mNumStrings)
        {
            QString line( mStrings[ix] );
            writeLine(&socket, line);
            QString echoedLine = readLine( &socket );
            if (echoedLine.length() > 0) {
                if (line != echoedLine)
                {
                    qDebug() << "line and echoed line doesn't match\n";
                }
                else
                {
                    qDebug() << QString("%s\n").arg( line.toLatin1().data() );
                }
            }
            ix++;
        } // while
    }
    else {
        qDebug() << "Client socket failed to connect\n";
    }
    setDone( true );
}


void GenericClient::startThread()
{
    setRunThread( true );
    start();
}

void GenericClient::stopThread()
{
}

const char *GenericClient::mStrings[] = {
    "    'Twas brillig, and the slithy toves\r",
    "        Did gyre and gimble in the wabe:\r",
    "    All mimsy were the borogoves,\r",
    "        And the mome raths outgrabe.\r",
    " \r",
    "    \"Beware the Jabberwock, my son!\r",
    "        The jaws that bite, the claws that catch!\r",
    "    Beware the Jubjub bird, and shun\r",
    "        The frumious Bandersnatch!\"\r",
    " \r",
    "    He took his vorpal sword in hand: \r",
    "        Long time the manxome foe he sought--\r",
    "    So rested he by the Tumtum tree, \r",
    "        And stood awhile in thought. \r",
    " \r",
    "    And, as in uffish thought he stood,\r",
    "        The Jabberwock, with eyes of flame,\r",
    "    Came whiffling through the tulgey wood,\r",
    "        And burbled as it came!\r",
    " \r",
    "    One, two!  One, two!  And through and through\r",
    "        The vorpal blade went snicker-snack!\r",
    "    He left it dead, and with its head\r",
    "        He went galumphing back. \r",
    " \r",
    "    \"And hast thou slain the Jabberwock?\r",
    "        Come to my arm, my beamish boy!\r",
    "    O frabjous day! Callooh!  Callay!\"\r",
    "        He chortled in his joy.\r",
    " \r",
    "    'Twas brillig, and the slithy toves\r",
    "        Did gyre and gimble in the wabe:\r",
    "    All mimsy were the borogoves, \r",
    "        And the mome raths outgrabe\r"
};

const uint GenericClient::mNumStrings = sizeof GenericClient::mStrings / sizeof( *GenericClient::mStrings );

