# Shelly-2.5-Blynk

In this repository, you will find Arduino sketch you can compile and flash to Shelly 2.5 for work with BlynkIoT and local external switch.
Code is prepared for one input and one relay, but in simple way is option to extend it.

## Neccessary libraries
1. https://github.com/kristianklein/PushButton
2. https://github.com/blynkkk/blynk-library
3. https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi

## V2.0
Basic version.
## V2.1
Version extended of voltage, current and power measurment. As well added notification when relay is on and there is no load on it - than it send notification to Blynk app.
Measurment on ADE7953 is based on library
https://github.com/MacWyznawca/ADE7953_ESP8266
but I modyfied a little bit for this project so better download it from my source.
