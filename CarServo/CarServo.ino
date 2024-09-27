#include <Servo.h>
#include "WiFi.h"
#include "ESPAsyncWebServer.h"

const gearRatio = 2;
//2:1 ratio

int Servopin = 33;
int startPos = 0; //change based off of experiments
int wantedTemp = 72;
Servo servo;

// Set your access point network credentials
const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";


// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

void setup() {
  // put your setup code here, to run once:
  servo.attach(Servopin);
  servo.write(startPos);
  Serial.begin(9600);
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/move", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readMove().c_str());
  });

  // Start server
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  while (!Serial.available()) {}
  wantedTemp = Serial.readString().toInt();
  servo.write(wantedTemp * gearRatio); //equation may change based off of experiments
}
