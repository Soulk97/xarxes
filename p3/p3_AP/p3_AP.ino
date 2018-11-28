#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"

String incomingData;
boolean TransmissioCompleta = false;

char ssid[] = "wololo";
char password[] = "12345678";
char str[4];

WiFiClient client;

ESP8266WebServer server(80);

void setup(){
  Serial.begin(9600);
  Serial.println("WiFi access point test");
  WiFi.mode(WIFI_AP);  
  WiFi.softAP(ssid, password);

  IPAddress server_ip = WiFi.softAPIP();
  Serial.print("Server IP: ");
  Serial.println(server_ip);
  Serial.println("WiFi ON");
}

void loop() {

  char a = 'a';

  while(!client.available()){
    delay(1);
  }
  
  if(client.connected()){
    Serial.write(a);
    Serial.write('\n');
  }else{
    Serial.println(" \nClient disconnected");
    client.stop();
  }

  delay(1);
}
