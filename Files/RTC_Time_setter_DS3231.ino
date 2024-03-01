#include <DS3231.h>
#include <Wire.h>
#include <time.h>

DS3231 RTC;

#define YEAR 24 //20"24"
#define MONTH 3
#define DATE 1
#define HOUR 14
#define MINUTE 41
#define SECOND 0
#define DOW 6

bool mode12 = false;

void setup() {
  Serial.begin(57600);

  pinMode(12, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(12) == LOW)
  {
    RTC.setYear(YEAR);
    RTC.setMonth(MONTH);
    RTC.setDate(DATE);
    RTC.setClockMode(mode12);
    RTC.setHour(HOUR);
    RTC.setMinute(MINUTE);
    RTC.setSecond(SECOND);
    RTC.setDoW(DOW);
    Serial.println("set");
    delay(1000);
  }
}
