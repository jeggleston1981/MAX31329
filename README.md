# MAX31329
Library for the MAX 31329 Real Time Clock using Wire for I2C
![Max31329 Dev Board](MAX31329_dev.jpg?raw=true "Max 31329")

The MAX31329 is similar to the DS3231 and DS1307 but the time registers start at 0x06 instead of at 0x00, additionally in order to read a byte from a specific register it is required that you write the byte you want to read from first and the restart not stop before you read the byte, which is another slight diference to the DS3231.
This basic library always the 7 bytes of time to be read and written using a tmElements_t structure which makes provision for 7 bytes (secs, min, hr, dow, date, mth, yr), the structure can be passed in as an arguement and the structure will be written to and use to write to the RTC.
The MAX31329 has a trickle charger that is designed to charge a super cap as the backup power source to keep time when the power is lost. This can be activated and deactivated as required, I will add that you can choose to have a diode inline or not and alter the inline curent limiting resistor from 3k, 6k, to 11k. I have found that with the diode in circuit you could use a 2.7v Super Cap safely without the Diode the charge voltage will exceed 3v and you will need to be using a dual cell super cap. Functionallity to change this has not been added yet, it is currently hard coded for the lower voltage with the diode in circuit using:
```
#include <MAX31329.h>

MAX31329 rtc;

rtc.begin(5, 4);

rtc.enableCharger(true);
rtc.enableCharger(false);
```
