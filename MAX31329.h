#ifndef DS3232RTC_H_INCLUDED
#define DS3232RTC_H_INCLUDED

#include <Arduino.h>
#include <TimeLib.h> 
#include <Wire.h>

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif

class MAX31329
{
	public:
		enum SQWAVE_FREQ {
			SQW_1_HZ,
			SQW_4096_HZ,
			SQW_8192_HZ,
			SQW_32768_HZ,
			SQWAVE_NONE
		};

		enum CHARGER {
			K3_SCHOTTKY,
			K6_SCHOTTKY,
			K11_SCHOTTKY,
			K3_SCHOTTKY_DO,
			K6_SCHOTTKY_DO,
			K11_SCHOTTKY_DO
		};

		enum ALARM_TYPES {
			A1_ONCE_SECOND,
			A1_SEC_MATCH,
			A1_MIN_SEC_MATCH,
			A1_HOUR_MIN_SEC_MATCH,
			A1_DATE_HOUR_MIN_SEC_MATCH,
			A1_MONTH_DATE_HOUR_MIN_SEC_MATCH,
			A1_YEAR_MONTH_DATE_HOUR_MIN_SEC_MATCH,
			A1_DAY_HOUR_MIN_SEC_MATCH,
			A2_ONCE_MINUTE,
			A2_MIN_MATCH,
			A2_HOUR_MIN_MATCH,
			A2_DATE_HOUR_MIN_MATCH,
			A2_DAY_HOUR_MIN_MATCH
		};

		enum ALARM_NUM {
			ALARM_1 = 1,
			ALARM_2 = 2
		};

		static constexpr uint8_t
			MAX_ADR						{0x68},
			MAX_STATUS				{0x00},
			MAX_INT_EN				{0x01},
			MAX_RTC_RESET			{0x02},
			MAX_CONFIG				{0x03},
			MAX_CONFIG2				{0x04},
			MAX_TIMER_CONFIG	{0x05},
			MAX_SECONDS				{0x06},
			MAX_MINUTES				{0x07},
			MAX_HOURS					{0x08},
			MAX_DAY						{0x09},
			MAX_DATE					{0x0A},
			MAX_MONTH					{0x0B},
			MAX_YEAR					{0x0C},
			MAX_PWR_MANAGE		{0x18},
			MAX_CHARGER				{0x19},
			TM_BYTES					{7},
			CLKO_HZ						{5},
			MAX_CLKO					{7},
			MAX_HR1224		    {6},        // Hours register 12 or 24 hour mode (24 hour mode==0)
      MAX_CENTURY   		{7};

    	MAX31329() {};
    	void begin(int SDA, int SCL);
    	//static time_t get();
    	//uint8_t set(time_t t);
    	static uint8_t read(tmElements_t &tm);
    	uint8_t write(tmElements_t &tm);
    	void squareWave(SQWAVE_FREQ freq);
    	void enableCharger(bool charge);
    	uint8_t readRTC(uint8_t addr, uint8_t* values, uint8_t nBytes);
    	uint8_t readRTC(uint8_t addr);
    	uint8_t writeRTC(uint8_t addr, uint8_t* values, uint8_t nBytes);
    	uint8_t writeRTC(uint8_t addr, uint8_t value);

	private:
    	uint8_t dec2bcd(uint8_t n);
    	static uint8_t bcd2dec(uint8_t n);
};

#endif
