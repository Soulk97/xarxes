#include "ESP8266WiFi.h"

String incomingData;
boolean TransmissioCompleta = false;

char ssid[] = "wololo";
char password[] = "12345678";
char str[4];

void setup(){
  Serial.begin(9600);
  Serial.println("WiFi access point test");
  WiFi.mode(WIFI_AP);  
  WiFi.softAP(ssid, password);
  Serial.println("WiFi ON");
}

void loop() {

  int value=1234;
  char a = 'a';

  Serial.write(a);
  Serial.write('\n');

}
