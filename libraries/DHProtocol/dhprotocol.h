#ifndef dhprotocol_h
#define dhprotocol_h

/*   For Arduino 1.0 and newer, do this:   */
#include "Arduino.h"

class SoftwareSerial;

typedef union {
  uint16_t val_16;
  struct {
	uint8_t  b0 : 1; // bit position 0
    uint8_t  b1 : 1; // bit position 1
    uint8_t  b2 : 1; // bit positions 2
    uint8_t  b3 : 1; // bit positions 3
    uint8_t  b4 : 1; // bit positions 4
	uint8_t  b5 : 1;
	uint8_t  b6 : 1;
	uint8_t  b7 : 1;
	uint8_t  b8 : 1;
	uint8_t  b9 : 1;
	uint8_t  b10 : 1;
	uint8_t  b11 : 1;
	uint8_t  b12 : 1;
	uint8_t  b13 : 1;
	uint8_t  b14 : 1;
	uint8_t  b15 : 1;
    // total 16 bits 
  } bits;
} tBit;


class DHProtocol
{
  private:
    SoftwareSerial *swSerial;

 public:
    unsigned char m_id;
    unsigned char m_otherid;
	unsigned long m_lastsend;
 
    //dati
	unsigned char m_nsensors;
    uint16_t *sensor;		// nsensors valori short 
    tBit 	 relay;			// 16 bit

    DHProtocol(){};
    void setup( int myId, int otherId, int nsensors, SoftwareSerial *myserial);

  private:
    bool _waitData( int msec );
	char _writeChar(char value );
    char _readChar();
    void _writeShort(short value);
    short _readShort();
    void _writeHeader();

  public:
    //********************************************************************************/
	bool checkTiming( int interval )
	{
		return ( millis() - m_lastsend >= interval );
	};
    void sendRequest();
    bool waitRequest( int timeout );

    //********************************************************************************/
    void sendData( );
    bool waitData( int timeout );
};

int freeMemory();

#endif
