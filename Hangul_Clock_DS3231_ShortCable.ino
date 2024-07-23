#include <DS3231.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <time.h>

#define LED_PIN 5 //네오픽셀 Data 단자와 연결할 핀
#define LED_COUNT 36 //네오픽셀 LED 개수 (6 X 6)

DS3231 RTC;
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

/* 위치 구성
오 전 후 한 두 세
네 다 섯 여 섯 일
곱 여 덟 아 홉 열
한 두 시 이 삼 사
오 십 일 이 삼 사
오 육 칠 팔 구 분
00 01 02 03 04 05
11 10 09 08 07 06 *
12 13 14 15 16 17
23 22 21 20 19 18 *
24 25 26 27 28 29
35 34 33 32 31 30 *
*/

//색과 밝기 설정
int r = 255;
int g = 255;
int b = 255;
int brightness = 255;

bool h12 = false, hPM = false;

void setup() {
  strip.begin();
  strip.setBrightness(brightness);
  //Serial.begin(57600);
}

int h = 0;
int m = 0;
//int s = 0;

void loop() {
  strip.clear();
  strip.setPixelColor(0, r, g, b); //오(전/후)
  strip.setPixelColor(21, r, g, b); //시
  setTime();
  setAmPm();
  setHour();
  setMinute();
  strip.show();
  delay(200);
}


void setTime() {
  h = RTC.getHour(h12, hPM);
  m = RTC.getMinute();
  //s = RTC.getSecond();
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
    strip.setPixelColor(11, r, g, b);
  }
  else if (h == 5) {
    strip.setPixelColor(10, r, g, b);
    strip.setPixelColor(9, r, g, b);
  }
  else if (h == 6) {
    strip.setPixelColor(8, r, g, b);
    strip.setPixelColor(7, r, g, b);
  }
  else if (h == 7) {
    strip.setPixelColor(6, r, g, b);
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
    strip.setPixelColor(23, r, g, b);
  }
  else if (h == 12) {
    strip.setPixelColor(17, r, g, b);
    strip.setPixelColor(22, r, g, b);
  }
}

void setMinute() {
  if (m >= 10) {
    strip.setPixelColor(25 , r, g, b);
    if (m >= 50) {
      strip.setPixelColor(24 , r, g, b);
    }
    else if (m >= 50) {
      strip.setPixelColor(24 , r, g, b);
    }
    else if (m >= 40) {
      strip.setPixelColor(18 , r, g, b);
    }
    else if (m >= 30) {
      strip.setPixelColor(19 , r, g, b);
    }
    else if (m >= 20) {
      strip.setPixelColor(20 , r, g, b);
    }
  }
  if (m != 0) {
    if (m % 10 <= 4) {
      strip.setPixelColor((m % 10) + 25, r, g, b);
    }
    else {
      strip.setPixelColor(40 - (m % 10), r, g, b);
    }

    strip.setPixelColor(30, r, g, b); //분
  }
}
