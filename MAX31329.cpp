// Arduino MAX31329 Library
// Copyright (C) 2023 by James Eggleston

#include <MAX31329.h>

void MAX31329::begin(int SDA, int SCL)
{
	Wire.begin(SDA, SCL);
}

//Returns 0 if Successful transaction on I2C bus
uint8_t MAX31329::read(tmElements_t &tm)
{
	Wire.beginTransmission(MAX_ADR);
  Wire.write(MAX_SECONDS);
  Wire.endTransmission(false);
  Wire.requestFrom(MAX_ADR, TM_BYTES); //request 7 bytes (secs, min, hr, dow, date, mth, yr)
  while(Wire.available()){
  	tm.Second = bcd2dec(Wire.read());
  	tm.Minute = bcd2dec(Wire.read());
  	tm.Hour = bcd2dec(Wire.read() & ~_BV(MAX_HR1224));
  	tm.Wday = Wire.read();
  	tm.Day = bcd2dec(Wire.read());
  	tm.Month = bcd2dec(Wire.read() & ~_BV(MAX_CENTURY));
  	tm.Year = tmYearToY2k(bcd2dec(Wire.read()));
	}
  return 0;
}

uint8_t MAX31329::write(tmElements_t &tm)
{
	Wire.beginTransmission(MAX_ADR);
  Wire.write(MAX_SECONDS);
	Wire.write(dec2bcd(tm.Second));
	Wire.write(dec2bcd(tm.Minute));
	Wire.write(dec2bcd(tm.Hour));
	Wire.write(tm.Wday);
	Wire.write(dec2bcd(tm.Day));
	Wire.write(dec2bcd(tm.Month));
	Wire.write(dec2bcd(y2kYearToTm(tm.Year)));
	Wire.endTransmission();
  return 0;
}

uint8_t MAX31329::writeRTC(uint8_t addr, uint8_t* values, uint8_t nBytes)
{
    Wire.beginTransmission(MAX_ADR);
    Wire.write(addr);
    for (uint8_t i=0; i<nBytes; i++) Wire.write(values[i]);
    return Wire.endTransmission();
}

uint8_t MAX31329::writeRTC(uint8_t addr, uint8_t value)
{
    return ( writeRTC(addr, &value, 1) );
}

uint8_t MAX31329::readRTC(uint8_t addr, uint8_t* values, uint8_t nBytes)
{
    Wire.beginTransmission(MAX_ADR);
    Wire.write(addr);
    if ( uint8_t e = Wire.endTransmission(false) ) return e;
    Wire.requestFrom( (uint8_t)MAX_ADR, nBytes );
    for (uint8_t i=0; i<nBytes; i++) values[i] = Wire.read();
    return 0;
}

uint8_t MAX31329::readRTC(uint8_t addr)
{
    uint8_t b {0};

    readRTC(addr, &b, 1);
    return b;
}

// Set Output Clock Frequency on INTB/CLKOUT
void MAX31329::squareWave(SQWAVE_FREQ freq)
{
    uint8_t config2 = readRTC(MAX_CONFIG2);
    if (freq >= SQWAVE_NONE) {
        config2 &= ~_BV(MAX_CLKO); //set bit 7 to 1 to disable Square Wave and enable INT
    }
    else {
        config2 = (config2 & 0x1F) | ((0x04 | freq ) << CLKO_HZ); // Set output frequency
    }
    writeRTC(MAX_CONFIG2, config2);
}

void MAX31329::enableCharger(bool charge)
{
    uint8_t power_reg = readRTC(MAX_CHARGER);
    if(charge){
        power_reg = (power_reg & _BV(MAX_TRICKLE_ENABLE)) | 0x05;
    }else {
        power_reg &= ~_BV(MAX_TRICKLE_ENABLE);
    }
}

void MAX31329::enableCharger(CHARGER charge)
{
	uint8_t power_reg = readRTC(MAX_CHARGER);
	if (power_reg >= DISABLE){
		power_reg |= _BV(MAX_TRICKLE_ENABLE);
	}
	else {
		power_reg = (power_reg & _BV(MAX_TRICKLE_ENABLE)) | charge;
	}
	writeRTC(MAX_CHARGER, power_reg);
}

// Decimal-to-BCD conversion
uint8_t MAX31329::dec2bcd(uint8_t n)
{
    return n + 6 * (n / 10);
}

// BCD-to-Decimal conversion
uint8_t __attribute__ ((noinline)) MAX31329::bcd2dec(uint8_t n)
{
    return n - 6 * (n >> 4);
}
