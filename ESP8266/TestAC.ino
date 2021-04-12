// #include "printf.h"
#include "user_defined.h"
#include "Globalvariables.h"

#include <DNSServer.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include "ESPAsyncWebServer.h"
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
SoftwareSerial s(3, 1);
#define test_master_
// Replace with your network credentials
const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";
const char* ssid_ = "Smart_Door";
const char* password_ = "12345678";
const char*   _apName                 = "no-net";
const char*   _apPassword             = NULL;


const char* PARAM_MESSAGE_ftxtmode4 = "running_mode1";

const char* PARAM_MESSAGE_ftxt = "ftxt";
const char FILESETTING[] PROGMEM = "/config.json";

// Create AsyncWebServer object on port 80
DNSServer dnsServer;
AsyncWebServer server(80);

//#include <Servo.h>
//Servo myservo;
//#include <Wire.h>

class CaptiveRequestHandler : public AsyncWebHandler {
  public:
    CaptiveRequestHandler() {}
    virtual ~CaptiveRequestHandler() {}

    bool canHandle(AsyncWebServerRequest *request) {
      //request->addInterestingHeader("ANY");
      return true;
    }

    void handleRequest(AsyncWebServerRequest *request) {
      AsyncResponseStream *response = request->beginResponseStream("text/html");
      response->print("<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/><title>{v}</title><style>#box{text-align: center;align-items: center;margin: 0px auto;}#myProgress{width: 300px;height: 30px;position: relative;background-color: white;border: 2px solid black;border-radius: 20px;text-align: center;align-items: center;margin: 0px auto;} #myBar {box-shadow: inset 0px 0px 20px rgb(52, 52, 245);border-radius: 20px;width: 0px;height: 30px;position: absolute;text-align: center;align-items: center;margin: 0px auto;}</style><script>function move() {var elem = document.getElementById('myBar');var width = 0;var id = setInterval(frame, 500);function frame() {if (width == 100) {clearInterval(id);} else {width=width+20;elem.style.width = width + '%';}}setTimeout(function(){location.href='http://192.168.4.1';},3000);}</script></head><body onload='move()'>");
      response->print("<div id='box'><h1 style='color: red;'>Smart Home App</h1><br><h1> Waiting few second! Loading...</h1><div id='myProgress'><div id='myBar'></div></div></div>");
      response->print("</body></html>");
      request->send(response);
    }
};

void setup() {

  Serial.begin(9600);
  s.begin(9600);
  init_wifi();
  Wire.begin();

  //  Serial.println("......");
  //  Serial.println("AirConditioner Controller Center");
  //  Serial.println("VerAug182020 13h40");

}

void loop() {
  // put your main code here, to run repeatedly:
  dnsServer.processNextRequest();

}

int init_wifi() {
  // Initialize SPIFFS
  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return 1;
  }
  BTS_wifi(ssid_, password_);
  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });
  // Route to load logo.png file
  server.on("/logo", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/logo.png", "image/png");
  });
  server.on("/get1", HTTP_GET, [] (AsyncWebServerRequest * request) {
    s.print("ON");
    request->send(200, "text/html", "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/><title>{v}</title><style>#box{text-align: center;align-items: center;margin: 0px auto;}#myProgress{width: 300px;height: 30px;position: relative;background-color: white;border-radius: 20px;border: 2px solid black;text-align: center;align-items: center;margin: 0px auto;} #myBar {border-radius: 20px;box-shadow: inset 0px 0px 20px rgb(52, 52, 245);width: 0px;height: 30px;position: absolute;text-align: center;align-items: center;margin: 0px auto;}</style><script>function move() {var elem = document.getElementById('myBar');var width = 0;var id = setInterval(frame, 250);function frame() {if (width == 100) {clearInterval(id);} else {width=width+50;elem.style.width = width + '%';}}setTimeout(function(){history.back();},1);}</script></head><body onload='move()'> <div id='box'><h1>Sent ok! Waiting few second! Loading...</h1><div id='myProgress'><div id='myBar'></div></div></div></body></html>");

    if (s.available()) {
      Serial.println(char(s.read()));
    }
  });


  server.onNotFound(notFound);
  // Start server
  server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);//only when requested from AP
  server.begin();
  return 0;
}

void BTS_wifi(char const *apName, char const *apPassword) {
  _apName = apName;
  _apPassword = apPassword;

  WiFi.mode(WIFI_AP);
  WiFi.softAP(_apName, _apPassword);//password option
  //  delay(500); // Without delay I've seen the IP address blank
  Serial.println(F("AP IP address: "));
  dnsServer.start(53, "*", WiFi.softAPIP());
  Serial.println(WiFi.softAPIP());
}
String processor(const String& var) {
  String s_;
  Serial.println(var);
}
void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}
