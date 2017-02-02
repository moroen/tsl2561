#include <stdio.h>
#include <inttypes.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <errno.h>

#include "tsl2561.h"

int tslAdr = TSL2561_ADDR_LOW;

void main() {
    int fd = 0;
    fd = wiringPiI2CSetup(tslAdr);

    printf("Lux: %f\n", getLux(fd));

    setGain(TSL2561_GAIN_16X);
    // setTiming(TSL2561_INTEGRATIONTIME_101MS);

    printf("Lux: %f\n", getLux(fd));

}
