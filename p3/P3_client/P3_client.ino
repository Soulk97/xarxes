#include "ESP8266WiFi.h"

String incomingData;
boolean TransmissioCompleta = false;

// Wi-Fi Settings
char* c_ssid; //ssid
char* c_pwd; //password

WiFiClient client;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(2000);
  Serial.println("Setup done");

  scanWiFi();
  wifiNetworkSelection();

}

void connectToWiFi(String ssid, String pwd){    
    Serial.println("connectToWiFi");
    
    if (WiFi.status() != WL_CONNECTED){
      int contador = 0;

      Serial.println("begin");
      Serial.println(ssid.length());
      Serial.println(pwd.length());
      
      c_ssid = (char*) malloc(sizeof(char) * ssid.length());
      c_pwd = (char*) malloc(sizeof(char) * pwd.length());

      ssid.toCharArray(c_ssid, ssid.length());
      pwd.toCharArray(c_pwd, pwd.length());
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

void scanWiFi(void) {
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
    
  }
  Serial.println("*********************************");
  delay(5000);
}

void loop() {
  if(client.connect(c_ssid, 80)){
    char value = client.read();
    Serial.println(value);
    
  }
}
