# HangulClock
현재 시각에 맞는 한글에 불을 밝힘으로써 시각을 나타내는 시계<br>

# 사용 부품
1 * `Arduino Nano`<br>
36 * `Adafruit Neopixel`(IP30, 60Led/m)<br>
1 * RTC모듈(`DS1302` OR `DS3231`(추천))<br>

# 참고사항
업로드를 하려면 아두이노 IDE 라이브러리에 `Adafruit_NeoPixel`, `ThreeWire` , `RtcDS1302`(`DS1302`의 경우) / `DS3231`(`DS3231`의 경우)라이브러리가 포함되어 있어야 함.<br>
`DS3231` 라이브러리 [GitHub 링크](https://github.com/NorthernWidget/DS3231)<br>
ShortCable:네오픽셀 간 케이블 연결 길이를 최소화 하기 위해 네오픽셀을 지그재그로 배치한 버전(파일 내 LED 인덱스 배치 주석 참고).
