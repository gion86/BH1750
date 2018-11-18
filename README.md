# BH1750
Light sensor BH1750 library for AVR micro. Tested with ATTiny85 and ATMega328P.

Every command documented in the datasheet is supported and tested:
*   wakeup/power down
*   reading mode
*   double precision mode
*   time register manipulation


_The sensor actually communicate with micro via I2C protocol: the implementation supports_:
* _TinyWireM [http://playground.arduino.cc/Code/USIi2c] , to save code space on the ATTiny MCU_.
* _TwoWire, for micro with TWI hardware implementation_   


