#include <stdio.h>
#include <inttypes.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <errno.h>

#include "tsl2561.h"

int getLux(int fd){
   wiringPiI2CWriteReg8(fd, TSL2561_COMMAND_BIT, TSL2561_CONTROL_POWERON); //enable the device
   wiringPiI2CWriteReg8(fd, TSL2561_REGISTER_TIMING, TSL2561_GAIN_AUTO); //auto gain and timing = 101 mSec
   //Wait for the conversion to complete
   delay(LUXDELAY);
   //Reads visible + IR diode from the I2C device auto
   uint16_t visible_and_ir = wiringPiI2CReadReg16(fd, TSL2561_REGISTER_CHAN0_LOW);
   wiringPiI2CWriteReg8(fd, TSL2561_COMMAND_BIT, TSL2561_CONTROL_POWEROFF); //disable the device
   return visible_and_ir*2;
}
