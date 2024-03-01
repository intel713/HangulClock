#include <ThreeWire.h>
#include <RtcDS1302.h>

ThreeWire myWire(3,2,4); // IO, SCLK, CE(DAT, CLK, RST)
RtcDS1302<ThreeWire> Rtc(myWire);

void setup() {
  Serial.begin(57600);
  Rtc.Begin();

  pinMode(12, INPUT_PULLUP);
  
  Rtc.SetIsWriteProtected(false);
  if (!Rtc.GetIsRunning())
    {
        Rtc.SetIsRunning(true);
    }
}

void loop() {
  if(digitalRead(12) == LOW) {
    Rtc.SetDateTime(RtcDateTime("SEP/18/2023", "17:32:00"));
    Serial.println("set");
  }
  RtcDateTime now = Rtc.GetDateTime();
  printDateTime(now);
  Serial.println();
  delay(100);
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    Serial.print(datestring);
}
