#include <stdio.h>
#include <inttypes.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <errno.h>

#include "tsl2561.h"

void main(){
    int fd = 0;
    fd = wiringPiI2CSetup(TSL2561_ADDR_LOW);
    int lux;

    lux = getLux(fd);
      // system ("tput clear");
    printf("Lux: %d\n", lux);
}
