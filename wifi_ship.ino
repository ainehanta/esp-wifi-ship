#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

#define WIFI_SSID "kurimotoLabo-G"
#define WIFI_PWD "kurimotoLabo-G"

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

  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PWD);

  // Wait until WiFi is connected
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  srv.attach(SERVO);
  analogWrite(SCREW, 0);

  // Setup WebServer Handlers
  server.on("/", HTTP_GET, []() {
    String html = HTML_HEADER "<h1>WiFi Ship Controller</h1>" HTML_FOOTER;
    server.send(200, "text/html", html);
  });

  server.on("/screw", []() {
    String html = HTML_HEADER "<h1>YAW</h1>" HTML_FOOTER;
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

  server.begin();
}

void loop() {
  server.handleClient();
}
