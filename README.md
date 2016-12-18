# BH1750
Light sensor BH1750 library for the small ATTiny85 (ATTinyX5).

Every command documented in the datasheet is supported and tested:
*   wakeup/power down
*   reading mode
*   double precision mode
*   time register manipulation


_The sensor actually communicate with micro via I2C protocol: the implementation supported is only TinyWireM [http://playground.arduino.cc/Code/USIi2c] , to save code space on the ATTiny MCU._    


