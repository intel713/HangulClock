//#include <DS3231.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <time.h>
#include "RTClib.h"

#define LED_PIN 3 //네오픽셀 Data 단자와 연결할 핀
#define LED_COUNT 36 //네오픽셀 LED 개수 (6 X 6)

RTC_DS3231 RTC;
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

//색과 밝기 설정
#define DEFAULT_COLOR strip.Color(255, 255, 255)
#define BRIGHTNESS 255

#define AM_COLOR strip.Color(255, 255, 32)
#define PM_COLOR strip.Color(96, 64, 255)

#define hour_startH 7000
#define hour_endH 35000

#define minute_startH 500
#define minute_endH 6000

uint32_t hour_color = strip.Color(255, 255, 255);
uint32_t minute_color = strip.Color(225, 115, 44);

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


bool h12 = false, hPM = false;

bool am = true;
int h = 0;
int m = 0;
//int s = 0;

void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  RTC.begin();
  Serial.begin(115200);
}

void loop() {
  // strip.clear();
  // setTime();
  // setColor();
  // setAmPm();
  // setHour();
  // setMinute();
  // strip.show();
  // delay(100);

  for (int i = 0; i <= 23; i++) {
    for (int j = 0; j <= 59; j++) {
      h = i;
      m = j;

      strip.clear();
      setAmPm();
      setColor();
      setHour();
      setMinute();
      strip.show();
      delay(5);
    }
  }
}


void setTime()
{
  DateTime now = RTC.now();
  
  h = now.hour();
  m = now.minute();
  //s = RTC.getSecond();
}

void setAmPm()
{
  if (0 <= h and h < 12){
    strip.setPixelColor(0, AM_COLOR);
    strip.setPixelColor(1, AM_COLOR);
    if (h == 0) {
      h = 12;
      am = true;
    }
  }
  else {
    strip.setPixelColor(0, PM_COLOR);
    strip.setPixelColor(2, PM_COLOR);
    am = false;
    if (h != 12) {
      h = h - 12;
    }
  }
}

void setHour()
{
  strip.setPixelColor(20, hour_color); //시

  if (h == 1) {
    strip.setPixelColor(3, hour_color);
  }
  else if (h == 2) {
    strip.setPixelColor(4, hour_color);
  }
  else if (h == 3) {
    strip.setPixelColor(5, hour_color);
  }
  else if (h == 4) {
    strip.setPixelColor(6, hour_color);
  }
  else if (h == 5) {
    strip.setPixelColor(7, hour_color);
    strip.setPixelColor(8, hour_color);
  }
  else if (h == 6) {
    strip.setPixelColor(9, hour_color);
    strip.setPixelColor(10, hour_color);
  }
  else if (h == 7) {
    strip.setPixelColor(11, hour_color);
    strip.setPixelColor(12, hour_color);
  }
  else if (h == 8) {
    strip.setPixelColor(13, hour_color);
    strip.setPixelColor(14, hour_color);
  }
  else if (h == 9) {
    strip.setPixelColor(15, hour_color);
    strip.setPixelColor(16, hour_color);
  }
  else if (h == 10) {
    strip.setPixelColor(17, hour_color);
  }
  else if (h == 11) {
    strip.setPixelColor(17, hour_color);
    strip.setPixelColor(18, hour_color);
  }
  else if (h == 12) {
    strip.setPixelColor(17, hour_color);
    strip.setPixelColor(19, hour_color);
  }
}

void setMinute()
{
  if (m >= 10) {
    strip.setPixelColor(25 , minute_color);
    if (m >= 20) {
      strip.setPixelColor((m / 10) + 19, minute_color);
    }
  }
  if (m != 0) {
    strip.setPixelColor((m % 10) + 25, minute_color);
    
    strip.setPixelColor(35, minute_color); //분
  }
}

void setColor()
{
  // if (am == true)
  // {
  //   if (0 <= h and h < 6 or h == 12)
  //   {
  //     hour_color = strip.Color(9, 24, 63);
  //     //minute_color = strip.Color(9, 24, 63);
  //   }
  //   else if (6 <= h and h < 7)
  //   {
  //     hour_color = strip.Color(170, 113, 132);
  //     //minute_color = strip.Color(170, 113, 132);
  //   }
  //   else if (7 <= h and h < 9)
  //   {
  //     hour_color = strip.Color(235, 216, 131);
  //     //minute_color = strip.Color(235, 216, 131);
  //   }
  //   else if (9 <= h and h < 12)
  //   {
  //     hour_color = strip.Color(146, 204, 252);
  //     //minute_color = strip.Color(146, 204, 252);
  //   }
  // }
  // else
  // {
  //   if (0 <= h and h < 4 or h == 12)
  //   {
  //     hour_color = strip.Color(60, 131, 210);
  //     //minute_color = strip.Color(60, 131, 210);
  //   }
  //   else if (4 <= h and h < 6)
  //   {
  //     hour_color = strip.Color(225, 115, 44);
  //     //minute_color = strip.Color(225, 115, 44);
  //   }
  //   else if (6 <= h and h < 8)
  //   {
  //     hour_color = strip.Color(99, 80, 135);
  //     //minute_color = strip.Color(99, 80, 135);
  //   }
  //   else if (8 <= h and h < 12)
  //   {
  //     hour_color = strip.Color(9, 24, 63);
  //     //minute_color = strip.Color(9, 24, 63);
  //   }
  // }


  hour_color = strip.ColorHSV(map(h, 0, 23, hour_startH, hour_endH), 255, 255);
  minute_color = strip.ColorHSV(map(m, 0, 59, minute_startH, minute_endH), 255, 255);
}
