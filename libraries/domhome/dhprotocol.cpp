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

void DHProtocol::setup( int myId, int otherId, int nsensors, SoftwareSerial *myserial)
    {
      m_id = myId;
      m_otherid = otherId;

	  m_nsensors = nsensors;
	  sensor = (uint16_t*) calloc( m_nsensors, sizeof(uint16_t) );
	  memset( sensor, 0, sizeof(sensor) );

      relay.val_16 = 0;	  
      pinMode(13, OUTPUT);

	  swSerial = myserial;
      swSerial->begin( 9600 );
      swSerial->listen();
	  m_lastsend = 0;
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
      swSerial->write( m_id);
      swSerial->write('@');
      swSerial->write( m_otherid);
      swSerial->write('#');
    }

    //********************************************************************************/
    void DHProtocol::sendRequest( )
    {
      digitalWrite(13, HIGH);
      _writeHeader();

      Serial.println( "");
      Serial.print( "sendData: " );
      Serial.write('#');
      Serial.write('0' + m_id);
      Serial.write('@');
      Serial.write('0' + m_otherid);
      Serial.write('#');

      //send the data -- relay value
      _writeShort( relay.val_16 );
      Serial.print( relay.val_16  );

      _writeChar('$');
      Serial.write('$');

      digitalWrite(13, LOW);
	   m_lastsend = millis();
    }

    //********************************************************************************/
    bool DHProtocol::waitRequest( int timeout)
    {      
      bool r = false;

      while ( _waitData( timeout ) )
      {
        if ( _readChar() == '#')
        {
          digitalWrite(13, HIGH);          
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
              if ( targetId == m_id )
              {
                uint16_t request;
                request = _readShort();
				Serial.print( request );

                // copio da temp a relay
                if (_readChar() == '$')
                {
                  Serial.write("$");
                  r = true;
				  relay.val_16 = request;
                }
              }
            }
          }
        }
      }
      digitalWrite(13, LOW);
      return r;
    }

    //********************************************************************************/
    void DHProtocol::sendData( )
    {
      digitalWrite(13, HIGH);
      _writeHeader();

      Serial.println( "");
      Serial.print( "sendData: " );
      Serial.write('#');
      Serial.write('0' + m_id);
      Serial.write('@');
      Serial.write('0' + m_otherid);
      Serial.write('#');

      //send the data -- sensor value
      for (int i = 0; i < 24; i++ )
      {
        _writeShort( sensor[i] );
        Serial.print( sensor[i] );
        Serial.write(",");
      }

      _writeChar('$');
      Serial.write('$');

      digitalWrite(13, LOW);
	  m_lastsend = millis();
    }

  //********************************************************************************/
    bool DHProtocol::waitData( int timeout)
    {
      bool r = false;

      while ( _waitData( timeout ) )
      { 
        if (_readChar() == '#')
        {
          digitalWrite(13, HIGH);
		  Serial.write("\nRecived: #");
		  
          unsigned char sendId = _readChar();
          Serial.write('0' + sendId);

          if ( sendId == m_otherid )
          {
            if ( _readChar() == '@')
            {
              Serial.write("@");

              unsigned char targetId = _readChar();
              Serial.write('0' + targetId);

              if ( _readChar() == '#')
              {
                Serial.write("#");

                if ( targetId == m_id )
                {
                  for (int i = 0; i < 24 ; i++)
                  {
                    sensor[i] = _readShort();

                    Serial.print( sensor[i] );
                    Serial.write(",");
                  }

                  // verifico il finale
                  if ( _readChar() == '$')
                  {
                    Serial.write("$");
                    r = true;
                  }
                }
              }
            }
          }
        }
      }

      digitalWrite(13, LOW);
      return r;
    }

