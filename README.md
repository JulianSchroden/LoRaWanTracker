# LoRaWanTracker
GPS tracker which transmits its location via LoRaWan to the [The Things Network](https://www.thethingsnetwork.org/).

## Table of contents
<!-- toc -->
- [Setup](#setup)
   * [Used components](#used-components)
   * [Pinout](#pinout)
   * [Required Libraries](#required-libraries)
- [Usage](#usage)
- [Suggestions](#suggestions)
<!-- tocstop -->


## Setup
### Used components
|Component name                                                   | Source                                                                                                                         |
|:----------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------|
|ESP32 Development Board                                          |[Amazon.de](https://www.amazon.de/AZDelivery-NodeMCU-Development-Nachfolgermodell-ESP8266/dp/B071P98VTG/)                       |
|Adafruit RFM95W LoRa Radio Transceiver Breakout - 868 or 915 MHz |[Exp-tech.de](https://www.exp-tech.de/module/wireless/funk/7310/adafruit-rfm95w-lora-radio-transceiver-breakout-868-or-915-mhz) |
|868 MHz Antenna                                                  |[Amazon.de](https://www.amazon.de/gp/product/B06Y1RNFBT/)                                                                       |
|NEO-6M GPS Modul                                                 |[Amazon.de](https://www.amazon.de/AZDelivery-NEO-6M-GPS-baugleich-u-blox/dp/B01N38EMBF/)                                        |
|0,96" I²C 128x64 Pixel OLED Display                              |[Amazon.de](https://www.amazon.de/AZDelivery-Display-Arduino-Raspberry-gratis/dp/B01L9GC470/)                                   |
|KY-040 Rotary Encoder                                            |[Amazon.de](https://www.amazon.de/gp/product/B01G1EWAAG/)                                                                       |
|Battery Holder 2*AA                                              |[Exp-tech.de](https://www.exp-tech.de/zubehoer/batterien-akkus/batteriehalter/7871/batteriehalter-2x-aa-mit-schalter)           |
|Step-Up Voltage Converter 1-5V to 5V                             |[Amazon.de](https://www.amazon.de/Boost-Converter-DC-DC-Step-Up-Arduino/dp/B01MSWNF05/)                                         |


###  Pinout
//TODO: Upload and link image


### Required libraries
|Library name                             | Source                                                          |
|:----------------------------------------|:----------------------------------------------------------------|
|Adafruit-GFX-Library                     |<https://github.com/adafruit/Adafruit-GFX-Library>               |
|Adafruit_SSD1306                         |<https://github.com/adafruit/Adafruit_SSD1306>                   |
|TinyGPSPlus                              |<https://github.com/mikalhart/TinyGPSPlus>                       |
|Arduino-LMIC library (slightly modified) |<https://github.com/JulianSchroden/arduino-lmic/tree/testing>    |
|activity-runtime-for-arduino             |<https://github.com/JulianSchroden/activity-runtime-for-arduino> |


## Usage



## Suggestions

