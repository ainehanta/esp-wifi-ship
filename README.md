# ESP8266 WiFi Ship Controller

## Circuit

* pin 15 -> Rudder yawing servo
* pin 13 -> Screw motor
* pin 14 -> Standalone(when it open) or Client(when it short to ground) mode select

## How to Use?

1. Download this repository

  Please click "Clone or download" on upper right of your window, and then click "Download ZIP" button in showing balloon.

2. Unzip and Open sketch

  Please double click the downloaded zip file and open uncompressed directory and move directory to arduino sketches directory.
  Next, please open esp-wifi-ship in arduino IDE.

4. Write sketch to your ESP8266

  Please click "Upload" button of Arduino IDE and upload spiffs data by ['ESP8266 Sketch Data Upload'](https://github.com/esp8266/arduino-esp8266fs-plugin).

5. Open controll panel

  If you use standalone mode, please connect SSID:"ESP-WIFI-SHIP-CONFIG", PASS:"ESP-WIFI-SHIP-CONFIG" network.
  Please open 192.168.10.1 (standalone) or another ip (client) in your browser.

  And load initial settings to esp if you launch first time. Open '<IP ADDRESS of ESP>/preferences.html' and click 'RESET' button, then click 'SAVE' button.
  Reset esp.

7. Controll your ship!

## Open Source License

This project contains following library.

* [Material Design Lite (Apache License)](https://getmdl.io/)
* [getmdl-select(MIT License)](http://creativeit.github.io/getmdl-select/)
* [jQuery(MIT License)](https://jquery.com/)
* [Lodash(MIT License)](https://lodash.com/)
