#ifndef dhprotocol_h
#define dhprotocol_h

/*   For Arduino 1.0 and newer, do this:   */
#include "Arduino.h"

class SoftwareSerial;

class DHProtocol
{
  private:
    SoftwareSerial *swSerial;

 public:
    unsigned char id;
    unsigned char otherid;
 
    //dati
    short sensor[28];
    short relay[16];

    DHProtocol(){};
    void setup( int myId, int otherId, SoftwareSerial *myserial, int baud);

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

};
#endif
