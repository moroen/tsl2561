#include <stdio.h>
#include <inttypes.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <errno.h>
#include <math.h>

#include "tsl2561.h"

int tslGain = TSL2561_GAIN_1X;
int tslTiming = TSL2561_INTEGRATIONTIME_402MS;

uint16_t channel0 = 0;
uint16_t channel1 = 0;

int setGain(int gain) {
    tslGain = gain;
    return gain;
}

int setTiming(int timing) {
    tslTiming = timing;
    return timing;
}

int getRawData(int fd) {

    // enable device
    wiringPiI2CWriteReg8(fd, TSL2561_COMMAND_BIT, TSL2561_CONTROL_POWERON);

    // Check current gain

    // test = wiringPiI2CReadReg8(fd, 0x81);
    // printf("Timing: %d\n", test);

    // Set gain and timing
    wiringPiI2CWriteReg8(fd, TSL2561_REGISTER_TIMING, tslGain | tslTiming);


    //Wait for the conversion to complete
    delay(LUXDELAY);
    //Reads visible + IR diode from the I2C device auto
    uint16_t visible_and_ir = wiringPiI2CReadReg16(fd, TSL2561_REGISTER_CHAN0_LOW);

    channel0 = wiringPiI2CReadReg16(fd, TSL2561_REGISTER_CHAN0_LOW);
    channel1 = wiringPiI2CReadReg16(fd, TSL2561_REGISTER_CHAN1_LOW);

    // disable device
    wiringPiI2CWriteReg8(fd, TSL2561_COMMAND_BIT, TSL2561_CONTROL_POWEROFF); //disable the device
    return visible_and_ir*2;
}

int getTimingInMS() {
    switch (tslTiming) {
        case TSL2561_INTEGRATIONTIME_13MS: return 13;
        case TSL2561_INTEGRATIONTIME_101MS: return 101;
        case TSL2561_INTEGRATIONTIME_402MS: return 402;
    }
    return -1;
}

double getLux(int fd) {
    double ratio, d0, d1;
    getRawData(fd);

    d0 = channel0; d1 = channel1; ratio = d1 / d0;

    // printf("channel0: %f channel1: %f ratio: %f\n", d0, d1, ratio);

    // Normalize for integration time
    double ms = getTimingInMS();
    d0 *= (402/ms);
    d1 *= (402/ms);

    // Normalize for gain
    if (!tslGain) {
        d0 *= 16;
        d1 *= 16;
    }

    // printf("Normalized channel0: %f Normalized channel1: %f ratio: %f\n", d0, d1, ratio);

    // Calculate lux

    if (ratio < 0.5)
	{
		return 0.0304 * d0 - 0.062 * d0 * pow(ratio,1.4);
	}

	if (ratio < 0.61)
	{
		return 0.0224 * d0 - 0.031 * d1;
	}

	if (ratio < 0.80)
	{
		return 0.0128 * d0 - 0.0153 * d1;
	}

	if (ratio < 1.30)
	{
		return 0.00146 * d0 - 0.00112 * d1;
	}

    return 0.0;
}
