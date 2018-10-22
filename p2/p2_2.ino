#include "ESP8266WiFi.h"

String incomingData;
boolean TransmissioCompleta = false;

/*
  Com no ens funciona rebre les dades i pasar-les amb el strToChar
  hem de posar el ssid i la contrasenya a aquestes variables
*/
char *c_ssid = "ssid";
char *c_pwd = "password";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(2000);
  Serial.println("Setup done");

  wifiNetworkSelection();
  
}

void connectToWiFi(String ssid, String pwd){
    Serial.println("connectToWiFi");
    
    if (WiFi.status() != WL_CONNECTED){
      int contador = 0;

      strTochar(ssid, c_ssid);
      strTochar(pwd, c_pwd);
      Serial.println("begin");
      WiFi.begin(c_ssid, c_pwd);

      while (WiFi.status() != WL_CONNECTED){
        delay(1000);
        Serial.println("Connecting...");
        contador++;
        if(contador ==10){
          break;
        }
      }
      Serial.println("Local IP:");
      Serial.println(WiFi.localIP());
    }

}

void wifiNetworkSelection(void){
    String ssid, password;
    if(WiFi.status() != WL_CONNECTED){
        Serial.println("SSID? >");
        while(!Serial.available());
        ssid = Serial.readString();
        Serial.print("SSID_selected > ");
        Serial.println(ssid);
        delay(1000);
        Serial.print("Password? > ");
        while(!Serial.available());
        password = Serial.readString();
        Serial.print("PWD > ");
        Serial.println(password);
        delay(1000);
        connectToWiFi(ssid, password);
    }
}


void strTochar(String txt, char* c){
  if(WiFi.status() != WL_CONNECTED){
    int len = txt.length();
    Serial.println(len);
    Serial.println("*************");
    c = (char*)malloc(len);
    for(int i = 0; i<len; i++){
      c[i] = txt[i];
      Serial.print(c[i]);
      }
    }
  }




void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Scan start");
  int n = WiFi.scanNetworks();
  if(n==0)
    Serial.println("no networks found");
  else{
    for(int i=0; i<n; i++){
      Serial.print(i+1);
      Serial.print(WiFi.SSID(i));
      Serial.print("(");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
      
      delay(30);
    }
    //wifiNetworkSelection();
    
  }
  Serial.println("*********************************");
  delay(5000);
}
