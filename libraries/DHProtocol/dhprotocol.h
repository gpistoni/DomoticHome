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

class SoftwareSerial;

class DHProtocol
{
  private:
    SoftwareSerial *swSerial;

 public:
    unsigned char id;
    unsigned char otherid;
 
    unsigned long lastsend;

    //dati
    short sensor[28];
    short relay[16];

    DHProtocol(){};
    void setup( int myId, int otherId, SoftwareSerial *myserial);

  private:
    bool _waitData( int msec );
    char _writeChar(char value );
    char _readChar();
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
		return ( millis() - lastsend >= interval );
	};
};

int freeMemory();
#endif
