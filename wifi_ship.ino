#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define WIFI_SSID "kurimotoLabo-G"
#define WIFI_PWD "kurimotoLabo-G"

ESP8266WebServer server(80);

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

  pinMode(13, OUTPUT);

//  server.on("/", HTTP_OPTIONS, []() {
//    server.sendHeader("Access-Control-Max-Age", "10000");
//    server.sendHeader("Access-Control-Allow-Methods", "POST,GET,OPTIONS");
//    server.sendHeader("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
//    server.send(200, "text/plain", "" );
//  });

  // Setup WebServer Handlers
  server.on("/", HTTP_GET, []() {
//    server.sendHeader("Access-Control-Allow-Methods", "POST,GET,OPTIONS");
//    server.sendHeader("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
    String html = HTML_HEADER "<h1>WiFi Ship Controller</h1>" HTML_FOOTER;
    server.send(200, "text/html", html);
  });

  server.on("/screw/on", []() {
//    server.sendHeader("Access-Control-Allow-Methods", "POST,GET,OPTIONS");
//    server.sendHeader("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
    String html = HTML_HEADER "<h1>SCREW ON</h1>" HTML_FOOTER;
    digitalWrite(13, HIGH);
    server.send(200, "text/html", html);
  });

  server.on("/screw/off", []() {
//    server.sendHeader("Access-Control-Allow-Methods", "POST,GET,OPTIONS");
//    server.sendHeader("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
    String html = HTML_HEADER "<h1>SCREW OFF</h1>" HTML_FOOTER;
    digitalWrite(13, LOW);
    server.send(200, "text/html", html);
  });

  server.on("/rudder/yaw", []() {
//    server.sendHeader("Access-Control-Allow-Methods", "POST,GET,OPTIONS");
//    server.sendHeader("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
    String html = HTML_HEADER "<h1>RUDDER</h1>" HTML_FOOTER;
    if(!server.argName(0).equals("value")) {
      server.send(500, "text/html", html);
    }
    String val = server.arg(0);
    analogWrite(15, val.toInt());
    server.send(200, "text/html", html);
  });

  server.begin();
}

void loop() {
  server.handleClient();
}
