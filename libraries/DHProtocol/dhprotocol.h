// versione 20160313

#ifndef dhprotocol_h
#define dhprotocol_h

/*   For Arduino 1.0 and newer, do this:   */
#include "Arduino.h"

#ifndef DISABLE_TRACE
#define OUT(x)   Serial.print(x)
#define OUTLN(x) Serial.println(x)
#else
#define OUT(x)
#define OUTLN(x)
#endif

#define NSENS 24
#define NRELAY 12

class SoftwareSerial;

class DHProtocol
{
  private:
    SoftwareSerial *swSerial;

  public:
    unsigned char m_id;
    unsigned char m_otherid;

    unsigned long lastRequest;
    unsigned long lastRecived;

    //dati
    short sensor[NSENS];
    byte relay[NRELAY];

    DHProtocol() {};
    void setup( int myId, int otherId, SoftwareSerial *myserial );

  private:
    bool _waitData( int msec );
    bool _waitHeader( int msec );
    bool _writeByte(byte value );
    byte _readByte();
    void _writeShort(short value);
    short _readShort();
    void _writeHeader();

  public:
    //********************************************************************************/
    void sendRequest();
    bool waitRequest( int timeout );

    //********************************************************************************/
    void sendData( );
    bool waitData( int timeout );

    bool checkTiming( int interval )
    {
      return ( millis() - lastRequest >= interval );
    };
	
	//********************************************************************************/
    unsigned short CalculateModbusCrc16(byte * Buffer, unsigned short wMessageLength);
};

int freeMemory();
#endif
