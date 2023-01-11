#include <MAX31329.h>

MAX31329 myRTC;

tmElements_t tm;

void setup() {
  
  Serial.begin(115200);
  myRTC.begin(4,5);  //SDA, SCL pins
  // Enter in the time and date
  tm.Second = 0;
  tm.Minute = 8;
  tm.Hour = 23;
  tm.Day = 11;
  tm.Month = 1;
  tm.Year = 23;
  tm.Wday = 3;
  myRTC.write(tm); // Write content of tm to RTC
  myRTC.enableCharger(true); // Enable Charger with inline diode enabled
  myRTC.squareWave(MAX31329::SQW_1_HZ); // Enable a 1 pulse per second output on INTB
                                        // It has a CMOS output and needs no pullup, and is active LOW

  

}

void loop() {
  delay(1000);
  byte square_wave = myRTC.readRTC(0x04);  // Read a single register and serial print as binary to serial monitor
  byte charger = myRTC.readRTC(0x19);// Reads 
  Serial.println(square_wave, BIN);
  Serial.println(charger, BIN);
  myRTC.read(tm);
  Serial.print(tm.Hour, DEC);
  Serial.print(":");
  Serial.print(tm.Minute, DEC);
  Serial.print(":");
  Serial.print(tm.Second, DEC);
  Serial.print("  ");
  Serial.print(tm.Day);
  Serial.print("-");
  Serial.print(tm.Month);
  Serial.print("-");
  Serial.println(tm.Year);
}
