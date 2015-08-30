#include "dhprotocol.h"
#include "SoftwareSerial.h"

extern unsigned int __bss_end;
extern unsigned int __heap_start;
extern void *__brkval;

int freeMemory()
{
  int free_memory;

  if ((int)__brkval == 0)
    free_memory = ((int)&free_memory) - ((int)&__bss_end);
  else
    free_memory = ((int)&free_memory) - ((int)__brkval);

  return free_memory;
}

void DHProtocol::setup( int myId, int otherId, SoftwareSerial *myserial)
{
  swSerial = myserial;
  swSerial->begin(9600);

  m_id = myId;
  m_otherid = otherId;

  for (int i = 0; i < 28; i++)
  {
    sensor[i] = 0;
  }
  for (int i = 0; i < 16; i++)
  {
    relay[i] = 0;
  }
  pinMode(13, OUTPUT);

  lastRecived=0;
  lastRequest=0;
  swSerial->listen();
}

bool DHProtocol::_waitData( int msec )
{
  unsigned long start = millis();
  while ( swSerial->available() == 0  && ( millis() - start) < msec ) delay(1);
  return swSerial->available();
}

bool DHProtocol::_writeByte(byte value )
{
  return swSerial->write( value );
}

byte DHProtocol::_readByte()
{
  if ( _waitData (20) )   // 20 msec
  {
    byte r = swSerial->read();
    OUT("r");
    return r;
  }
  return 0;
}

void DHProtocol::_writeShort( short value)
{
  byte b0 = (byte )(value & 0xff);
  byte b1 = (byte )((value >> 8) & 0xff);
  swSerial->write(b0);
  swSerial->write(b1);
}

short DHProtocol::_readShort()
{
  byte b0 = 0, b1 = 0;
  if ( _waitData (20) )   // 20 msec
  {
    b0 = swSerial->read();
  }
  if ( _waitData (20) )   // 20 msec
  {
    b1 = swSerial->read();
  }
  return b0 | b1 << 8;
}

void DHProtocol::_writeHeader()
{
  swSerial->write('#');
  swSerial->write( m_id);
  swSerial->write('@');
  swSerial->write( m_otherid);
  swSerial->write('#');
}

bool DHProtocol::_waitHeaderAndData( int msec )
{
  while ( _waitData( msec ) )
  {
    if ( _readByte() == '#')
    {
      OUT("recived: #");

      byte sendId = _readByte();
      OUT(sendId);

      if (_readByte() == '@')
      {
        OUT("@");

        byte targetId = _readByte();
        OUT(targetId);

        if (_readByte() == '#')
        {
          OUT("#");
          if ( targetId == m_id )
          {
            return true;
          }
        }
      }
    }
  }
  return false;
}

//********************************************************************************/
void DHProtocol::sendRequest( )
{
  _writeHeader();

  OUT( "sendRequest: " );
  OUT('#');
  OUT(m_id);
  OUT('@');
  OUT(m_otherid);
  OUT('#');

  //send the data -- relay value
  for (int i = 0; i < 12; i++ )
  {
    _writeByte( relay[i] );
    OUT( relay[i] );
  }

  _writeByte('$');
  OUTLN('$');
  lastRequest = millis();
}

//********************************************************************************/
bool DHProtocol::waitRequest( int timeout)
{
  bool r = false;

  if ( _waitHeaderAndData( timeout ))
  {
    byte temp[12];
    for (int i = 0; i < 12 ; i++)
    {
      temp[i] = _readByte();
      OUT(temp[i] );
    }
    // copio da temp a relay
    if (_readByte() == '$')
    {
      OUT("$");
      r = true;
      for (int i = 0; i < 12 ; i++)
      {
        relay[i] = temp[i];
      }
    }
  }

  //clear buffer
  while ( swSerial->available() ) swSerial->read();

  return r;
}

//********************************************************************************/
void DHProtocol::sendData( )
{
  _writeHeader();

  OUTLN( "");
  OUT( "sendData: " );
  OUT( '#' );
  OUT( m_id );
  OUT( '@' );
  OUT( m_otherid );
  OUT( '#' );

  //send the data -- sensor value
  for (int i = 0; i < 24; i++ )
  {
    _writeShort( sensor[i] );
    OUT( sensor[i] );
    OUT(",");
  }

  _writeByte('$');
  OUTLN('$');
}

//********************************************************************************/
bool DHProtocol::waitData( int timeout)
{
  bool r = false;
  byte b;
  if( millis() - lastRecived > 60000)
  {    
     OUTLN("Reset data too old");
     for (int i = 0; i < 24 ; i++)
     {
      sensor[i] = 0;
     }
  }

  if ( _waitHeaderAndData( timeout ))
  {
    for (int i = 0; i < 24 ; i++)
    {
      sensor[i] = _readShort();
      OUT( sensor[i] );
      OUT(",");
    }

    // verifico il finale
    if ( _readByte() == '$')
    {
      OUTLN("$");
      r = true;
      lastRecived = millis();
    }
  }

 //clear buffer
  while ( swSerial->available() ) swSerial->read();

  return r;
}

