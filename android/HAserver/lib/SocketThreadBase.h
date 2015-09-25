#include "windows.h"
#include "QMutex"
#include "QThread"
#include "QTcpServer"
#include "QTcpSocket"
#include "QVector"
#include "QString"

class SocketThreadBase
{
public:
    SocketThreadBase(const QString &ipAddr, const ushort port ) : mIP( ipAddr ), mPort( port )
    {
        mRunThread = false;
    }
    enum Identity {
        BAD_IDENTITY,
        SERVER,
        CLIENT
    };
    virtual void startThread() = 0;
    virtual void stopThread() = 0;
    virtual Identity getIdentity() = 0;
protected:
    QMutex mMutex;
    const QString mIP;
    const ushort mPort;

    void setRunThread( bool newVal );
    bool getRunThread();
    void run();
    QString readLine(QTcpSocket *socket );
    int waitForInput( QTcpSocket *socket );
    bool writeLine( QTcpSocket *client, const QString &line );
private:
    bool mRunThread;
};


class GenericServer : public SocketThreadBase, QThread
{
public:
    GenericServer(const QString &ipAddr, const ushort port ) : SocketThreadBase( ipAddr, port ) {}
    void startThread();
    void stopThread();
    Identity getIdentity() { return SERVER; }
protected:
    void run();
    virtual void Reply( QTcpSocket *client ) = 0;
};


class GenericClient : public SocketThreadBase, QThread
{
public:
    GenericClient(const QString &ipAddr, const ushort port ) : SocketThreadBase( ipAddr, port ) { mDone = false; }
    void startThread();
    void stopThread();
    bool isDone();
    Identity getIdentity() { return CLIENT; }
protected:
    void run();
    void setDone( const bool newVal );

private:
    static const unsigned int CONNECT_TIME_OUT = 5 * 1000; // 5 seconds
    static const char *mStrings[];
    static const uint mNumStrings;
    bool mDone;
};

