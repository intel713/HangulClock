#include <ThreeWire.h>
#include <RtcDS1302.h>
#include <Adafruit_NeoPixel.h>

//RTC 모듈에 연결할 핀 구성
ThreeWire myWire(3,2,4); // IO, SCLK, CE(DAT, CLK, RST)
RtcDS1302<ThreeWire> Rtc(myWire);

#define LED_PIN 5 //네오픽셀 Data 단자와 연결할 핀
#define LED_COUNT 36 //네오픽셀 LED 개수 (6 X 6)

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

/* 위치 구성
오 전 후 한 두 세
네 다 섯 여 섯 일
곱 여 덟 아 홉 열
한 두 시 이 삼 사
오 십 일 이 삼 사
오 육 칠 팔 구 분

00 01 02 03 04 05
06 07 08 09 10 11
12 13 14 15 16 17
18 19 20 21 22 23
24 25 26 27 28 29
30 31 32 33 34 35
*/

//색과 밝기 설정
int r = 255;
int g = 255;
int b = 255;
int brightness = 255;

void setup() {
  Rtc.Begin();
  strip.begin();
  strip.setBrightness(brightness);
  //Serial.begin(57600);
  Rtc.SetIsWriteProtected(true);
}

int h = 0;
int m = 0;
//int s = 0;

void loop() {
  strip.clear();
  strip.setPixelColor(0, r, g, b); //오(전/후)
  strip.setPixelColor(20, r, g, b); //시
  setTime(RtcDateTime(Rtc.GetDateTime()));
  setAmPm();
  setHour();
  setMinute();
  if (m != 0) {
    strip.setPixelColor(35, r, g, b); //분
  }
  strip.show();
  delay(500);
}

//--------------------functions--------------------

#define countof(a) (sizeof(a) / sizeof(a[0]))
String DateTime(const RtcDateTime& dt, String dort)
{
  char string[20] = {0,};
  if(dort == "y") {
    snprintf_P(string, 
      countof(string),
      PSTR("%04u"),
      dt.Year());
    }
    else if(dort == "m") {
      snprintf_P(string, 
        countof(string),
        PSTR("%02u"),
        dt.Month());
    }
    else if(dort == "d") {
      snprintf_P(string, 
        countof(string),
        PSTR("%02u"),
        dt.Day());
    }
    else if(dort == "h") {
      snprintf_P(string, 
        countof(string),
        PSTR("%02u"),
        dt.Hour());
    }
    else if(dort == "min") {
      snprintf_P(string, 
        countof(string),
        PSTR("%02u"),
        dt.Minute());
    }
    else if(dort == "s") {
      snprintf_P(string, 
        countof(string),
        PSTR("%02u"),
        dt.Second());
    }
    
  return(string);
}

void setTime(const RtcDateTime& dati) {
  String sh = DateTime(dati, "h");
  String sm = DateTime(dati, "min");
  //String ss = DateTime(dati, "s");
  h = sh.toInt();
  m = sm.toInt();
  //s = ss.toInt();
}

void setAmPm() {
  if (h >= 0 && h < 12){
    strip.setPixelColor(1, r, g, b);
    if (h == 0) {
      h = 12;
    }
  }
  else {
    strip.setPixelColor(2, r, g, b);
    if (h != 12) {
      h = h - 12;
    }
  }
}

void setHour() {
  if (h == 1) {
    strip.setPixelColor(3, r, g, b);
  }
  else if (h == 2) {
    strip.setPixelColor(4, r, g, b);
  }
  else if (h == 3) {
    strip.setPixelColor(5, r, g, b);
  }
  else if (h == 4) {
    strip.setPixelColor(6, r, g, b);
  }
  else if (h == 5) {
    strip.setPixelColor(7, r, g, b);
    strip.setPixelColor(8, r, g, b);
  }
  else if (h == 6) {
    strip.setPixelColor(9, r, g, b);
    strip.setPixelColor(10, r, g, b);
  }
  else if (h == 7) {
    strip.setPixelColor(11, r, g, b);
    strip.setPixelColor(12, r, g, b);
  }
  else if (h == 8) {
    strip.setPixelColor(13, r, g, b);
    strip.setPixelColor(14, r, g, b);
  }
  else if (h == 9) {
    strip.setPixelColor(15, r, g, b);
    strip.setPixelColor(16, r, g, b);
  }
  else if (h == 10) {
    strip.setPixelColor(17, r, g, b);
  }
  else if (h == 11) {
    strip.setPixelColor(17, r, g, b);
    strip.setPixelColor(18, r, g, b);
  }
  else if (h == 12) {
    strip.setPixelColor(17, r, g, b);
    strip.setPixelColor(19, r, g, b);
  }
}

void setMinute() {
  if (m >= 10) {
    strip.setPixelColor(25 , r, g, b);
    if (m >= 20) {
      strip.setPixelColor((m / 10) + 19, r, g, b);
    }
  }
  if (m != 0) {
    strip.setPixelColor((m % 10) + 25, r, g, b);
  }
}
