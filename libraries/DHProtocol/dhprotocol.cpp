#include "dhprotocol.h"
#include "SoftwareSerial.h"

extern unsigned int __bss_end;
extern unsigned int __heap_start;
extern void *__brkval;

int freeMemory()
 {
  int free_memory;

  if((int)__brkval == 0)
     free_memory = ((int)&free_memory) - ((int)&__bss_end);
  else
    free_memory = ((int)&free_memory) - ((int)__brkval);

  return free_memory;
}

    void DHProtocol::setup( int myId, int otherId, SoftwareSerial *myserial)
    {
      swSerial = myserial;
      swSerial->begin(9600);

      id = myId;
      otherid = otherId;

      for (int i = 0; i < 28; i++)
      {
        sensor[i] = 0;
      }
      for (int i = 0; i < 16; i++)
      {
        relay[i] = 0;
      }
      pinMode(13, OUTPUT);

      swSerial->listen();
     }


    bool DHProtocol::_waitData( int msec )
    {
      unsigned long start = millis();
      while ( swSerial->available() == 0  && ( millis() - start) < msec ) delay(1);
      return swSerial->available();
    }

    char DHProtocol::_writeChar(char value )
    {
      return swSerial->write( value );
    }

    char DHProtocol::_readChar()
    {
      if ( _waitData (20) )   // 20 msec
      {
        return swSerial->read();
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
      swSerial->write( id);
      swSerial->write('@');
      swSerial->write( otherid);
      swSerial->write('#');
    }

    //********************************************************************************/
    void DHProtocol::sendRequest( )
    {
      _writeHeader();

      Serial.println( "");
      Serial.print( "sendRequest: " );
      Serial.write('#');
      Serial.write('0' + id);
      Serial.write('@');
      Serial.write('0' + otherid);
      Serial.write('#');

      //send the data -- relay value
      for (int i = 0; i < 16; i++ )
      {
        _writeChar(relay[i] );
        Serial.write( '0' + relay[i] );
      }

      _writeChar('$');
      Serial.println('$');
   lastsend=millis();
    }

    //********************************************************************************/
    bool DHProtocol::waitRequest( int timeout)
    {      
      bool r = false;

      while ( _waitData( timeout ) )
      {
        if ( _readChar() == '#')
        {
        
          Serial.write("\nRequest: #");

          char sendId = _readChar();
          Serial.write('0' + sendId);

          if (_readChar() == '@')
          {
            Serial.write("@");

            unsigned char targetId = _readChar();
            Serial.write('0' + targetId);

            if (_readChar() == '#')
            {
              Serial.write("#");
              if ( targetId == id )
              {
                short temp[16];
                for (int i = 0; i < 16 ; i++)
                {
                  temp[i] = _readChar();
                  Serial.write('0' +  temp[i] );
                }

                // copio da temp a relay
                if (_readChar() == '$')
                {
                  Serial.println("$");
                  r = true;
                  for (int i = 0; i < 16 ; i++)
                  {
                    relay[i] = temp[i];
                  }
                }
              }
            }
          }
        }
      }

      return r;
    }

    //********************************************************************************/
    void DHProtocol::sendData( )
    {
      _writeHeader();

      Serial.println( "");
      Serial.print( "sendData: " );
      Serial.write('#');
      Serial.write('0' + id);
      Serial.write('@');
      Serial.write('0' + otherid);
      Serial.write('#');

      //send the data -- sensor value
      for (int i = 0; i < 28; i++ )
      {
        _writeShort( sensor[i] );
        Serial.print( sensor[i] );
        Serial.write(",");
      }

      _writeChar('$');
      Serial.println('$');

	lastsend=millis();

    }

  //********************************************************************************/
    bool DHProtocol::waitData( int timeout)
    {
      bool r = false;

      while ( _waitData( timeout ) )
      { 
        if (_readChar() == '#')
        {
         
	  Serial.write("Recived: #");
          unsigned char sendId = _readChar();
          Serial.write('0' + sendId);

          if ( sendId == otherid )
          {
            if ( _readChar() == '@')
            {
              Serial.write("@");

              unsigned char targetId = _readChar();
              Serial.write('0' + targetId);

              if ( _readChar() == '#')
              {
                Serial.write("#");

                if ( targetId == id )
                {
                  for (int i = 0; i < 28 ; i++)
                  {
                    sensor[i] = _readShort();

                    Serial.print( sensor[i] );
                    Serial.write(",");
                  }

                  // verifico il finale
                  if ( _readChar() == '$')
                  {
                    Serial.println("$");
                    r = true;
                  }
                }
              }
            }
          }
        }
      }

      return r;
    }

