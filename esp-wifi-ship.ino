#include <ArduinoJson.h>

#include <FS.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

#define WIFI_SSID "ESP-WIFI-SHIP-CONFIG"
#define WIFI_PWD "ESP-WIFI-SHIP-CONFIG"

#define SERVO 15
#define SCREW 13

ESP8266WebServer server(80);
Servo srv;

// HTML
#define HTML_HEADER "<!doctype html>"\
  "<html><head><meta charset=\"UTF-8\"/>"\
  "<meta name=\"viewport\" content=\"width=device-width\"/>"\
  "</head><body>"
#define HTML_FOOTER "</body></html>"

void setup() {
  bool standaloneMode = false;

  Serial.begin(115200);

  pinMode(14, INPUT_PULLUP);
  standaloneMode = digitalRead(14);

  SPIFFS.begin();
  
  DynamicJsonBuffer jsonBuffer;
  File fp = SPIFFS.open("/config.json", "r");
  String line = fp.readStringUntil('\n');
  JsonObject &root = jsonBuffer.parseObject(line);

  srv.attach(SERVO);
  analogWriteRange(root["screw"]["steps"]);
  analogWrite(SCREW, 0);

  if(standaloneMode) {
    Serial.println("");
    Serial.println("AP Mode");
    WiFi.mode(WIFI_AP);
  
    IPAddress ip(192, 168, 10, 1);
    IPAddress subnet(255, 255, 255, 0);
    
    WiFi.softAPConfig(ip, ip, subnet);
    WiFi.softAP(WIFI_SSID, WIFI_PWD);
  
    Serial.print("Setting WiFi SSID:");
    Serial.println(WIFI_SSID);
    Serial.print("Setting WiFi PWD:");
    Serial.println(WIFI_PWD);
    Serial.print("Setting WiFi IP:");
    Serial.println(ip);
  } else {
    Serial.println("");
    Serial.println("WiFi Station Mode");
    Serial.print("Connect WiFi SSID:");
    Serial.println((const char*)root["wifi"]["ssid"]);
    Serial.print("Connect WiFi PWD:");
    Serial.println((const char*)root["wifi"]["password"]);
    
    WiFi.begin((const char*)root["wifi"]["ssid"], (const char*)root["wifi"]["password"]);
  
    int times = 0;
    // Wait until WiFi is connected
    Serial.println("");
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
      times++;
      if(times > 30) {
        break;
      }
    }
    if(times <= 30) {
      Serial.println("");
      Serial.println("Connected!");
      Serial.print("ESP Controll IP Address: ");
      Serial.println(WiFi.localIP());
    } else {
      Serial.println("Timeout. reboot.");
      ESP.reset();
    }
  }

  server.on("/screw", []() {
    String html = HTML_HEADER "<h1>SCREW</h1>" HTML_FOOTER;
    if(!server.argName(0).equals("value")) {
      server.send(500, "text/html", html);
    }
    String val = server.arg(0);
    analogWrite(SCREW, val.toInt());
    server.send(200, "text/html", html);
  });

  server.on("/rudder/yaw", []() {
    String html = HTML_HEADER "<h1>RUDDER</h1>" HTML_FOOTER;
    if(!server.argName(0).equals("value")) {
      server.send(500, "text/html", html);
    }
    String val = server.arg(0);
    srv.write(val.toInt());
    server.send(200, "text/html", html);
  });

  server.on("/config.json", HTTP_GET, []() {
    File f = SPIFFS.open("/config.json", "r");
    size_t sent = server.streamFile(f, "application/json");
    f.close();
  });

  server.on("/config.json", HTTP_POST, []() {
    File f = SPIFFS.open("/config.json", "w");
    f.print(server.arg("plain"));
    f.close();
    server.send(200, "application/json", "200");
  });

  server.serveStatic("/", SPIFFS, "/index.html");
  server.serveStatic("/index.html", SPIFFS, "/index.html");
  server.serveStatic("/preferences.html", SPIFFS, "/preferences.html");
  server.serveStatic("/res/jquery-3.2.1.min.js", SPIFFS, "/res/jquery-3.2.1.min.js");
  server.serveStatic("/res/lodash.min.js", SPIFFS, "/res/lodash.min.js");
  server.serveStatic("/res/material.min.css", SPIFFS, "/res/material.min.css");
  server.serveStatic("/res/material.min.js", SPIFFS, "/res/material.min.js");
  server.serveStatic("/res/getmdl-select.min.css", SPIFFS, "/res/getmdl-select.min.css");
  server.serveStatic("/res/getmdl-select.min.js", SPIFFS, "/res/getmdl-select.min.js");
  
  server.begin();
}

void loop() {
  server.handleClient();
}
