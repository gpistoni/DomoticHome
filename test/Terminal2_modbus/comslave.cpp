#include <RS485.h>
#include <ModbusSlave485.h>
#include <SPI.h>

class CComSlave
{
    // Create new mbs instance
    ModbusSlave485 mbs;

    // Slave registers
    enum {
      MB_0,   // Register 0
      MB_1,   // Register 1
      MB_2,   // Register 2
      MB_3,   // Register 3
      MB_4,   // Register 4
      MB_5,   // Register 0
      MB_6,   // Register 1
      MB_7,   // Register 2
      MB_REGS // Dummy register. using 0 offset to keep size of array
    };

    int regs[MB_REGS];

public:
    void setup( int slaveID, int baudrate = 9600 )
    {
      // Configure msb with config settings
      mbs.configure( slaveID, baudrate );
    }

    void UpdateRegisters( int *values, int len)
    {
      // Pass current register values to mbs
      mbs.update(regs, MB_REGS);

      // Read all the analog Inputs, and store the values in
      // the Modbus registers.
      Serial.print( "Slave UpdateRegisters:");
      for (int i=0; i<len && i<MB_REGS; i++)
      {
        regs[i] = values[i];        // set register
        Serial.print(  regs[i] );
        Serial.print( "," );
      }
      for (int i=len; i<MB_REGS; i++)
      {
        regs[i] = 0;        // set register
      }
    Serial.println( "" );
    }
};

