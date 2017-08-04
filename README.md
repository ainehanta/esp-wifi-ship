# ESP8266 WiFi Ship Controller

## Circuit

* pin 15 -> Rudder yawing servo
* pin 13 -> Screw motor

## How to Use?

1. Download this repository

  Please click "Clone or download" on upper right of your window, and then click "Download ZIP" button in showing balloon.

2. Unzip and Open sketch

  Please double click the downloaded zip file and open uncompressed directory.

  Please open "wifi_ship.ino" file.

3. Change the WIFI_SSID and WIFI_PWD

  In arduino IDE, please change WIFI_SSID and WIFI_PWD constants to your WiFi Netowrk.

4. Write sketch to your ESP8266

  Please click "Upload" button of Arduino IDE.

5. Open controll panel

  Please open "ainehanta.github.io/esp-wifi-ship" in your browser.

6. Setup controll panel

  To use controll panel, please set ip address of your esp8266. The sketch output ip address of your esp8266 to serial monitor.

7. Controll your ship!

## Controll panel server

Normally, you can open the controll panel from github.
But if you customized the controll panel, you must serve the controll panel yourself.

We prepared some server samples.

### Windows

Please cd to uncompressed this repository's directory in PowerShell and cd "docs" directory.
And then input ".\windows.ps1" to launch the server.

### Android

Please use following apps.

[HTTP Server powered by Apache](https://play.google.com/store/apps/details?id=com.esminis.server.apache)

[File Manager](https://play.google.com/store/apps/details?id=com.asus.filemanager)

Uncompress the repository and copy 'docs/index.html' to 'htdocs/public/'. Launch http server and access to server.

### ruby

```
$ cd $REPOSITORY_DIRECTORY/docs
$ ruby -run -e httpd
```
