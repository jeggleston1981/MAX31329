# MAX31329
Library for the MAX 31329 Real Time Clock using Wire for I2C
![Max31329 Dev Board](Max31329_DEV.jpeg?raw=true "Max 31329")

The MAX31329 is similar to the DS3231 and DS1307 but the time registers start at 0x06 instead of at 0x00, additionally in order to read a byte from a specific register it is required that you write the byte you want to read from first and the restart not stop before you read the byte, which is another slight diference to the DS3231.
This basic library always the 7 bytes of time to be read and written using a tmElements_t structure which makes provision for 7 bytes (secs, min, hr, dow, date, mth, yr), the structure can be passed in as an arguement and the structure will be written to and use to write to the RTC.
The MAX31329 has a trickle charger that is designed to charge a super cap as the backup power source to keep time when the power is lost. This can be activated and deactivated as required, I will add that you can choose to have a diode inline or not and alter the inline curent limiting resistor from 3k, 6k, to 11k. I have found that with the diode in circuit you could use a 2.7v Super Cap safely without the Diode the charge voltage will exceed 3v and you will need to be using a dual cell super cap. The charger can either be enable in low voltage/low current mode or disabled or a setting specified.

# Setup clock and write and read time
```
#include <MAX31329.h>

MAX31329 rtc;

void setup() {
  rtc.begin(4, 5); //SDA, SCL
}
```

The SDA and SCL pin numbers need to be entered into begin() fucntion, ESP8266 SDA - 4, SCL - 5
For the ESP32 SDA - 21 SCL - 22

```
#include <MAX31329.h>

MAX31329 rtc;
void setup() {
  rtc.begin(4, 5); //SDA, SCL

  rtc.enableCharger(true);
  rtc.enableCharger(false);
}
```
The following ENUMs can be used to set the charge setting
```
K3_SCHOTTKY- 3K inline with Schottky Diode only 
K6_SCHOTTKY- 6K inline with Schottky Diode only 
K11_SCHOTTKY- 11K inline with Schottky Diode only 
K3_SCHOTTKY_DO- 3K inline with Schottky Diode and standard diode for extra voltage drop (About 2.5v charging)
K6_SCHOTTKY_DO - 6K inline with Schottky Diode and standard diode for extra voltage drop
K11_SCHOTTKY_DO - 11K inline with Schottky Diode and standard diode for extra voltage drop
DISABLE

rtc.enableCharger(MAX31329::K6_SCHOTTKY_DO);

```
