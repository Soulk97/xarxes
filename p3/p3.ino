#include "ESP8266WiFi.h"

String incomingData;
boolean TransmissioCompleta = false;

// Wi-Fi Settings
char* c_ssid = "equisde"; //ssid
char* c_pwd = "12345678"; //password

WiFiClient client;

//ThingSpeak Settings
const int channelID = 624733;
String writeAPIKey = "5BFLIHGQD0DBD9NJ";
const char* server = "api.thingspeak.com";
const int postingInterval = 20 * 1000;

/* WIFI access point
char ssid[] = "WOTOFOK";
char password[] = "skfdasnfcKI8798797987897dsa89dy7s89fds";

void setup(){
  Serial.begin(9600);
  Serial.println("WiFi access point test");
  WiFi.mode(WIFI_AP);  
  WiFi.softAP(ssid, password);
  Serial.println("WiFi ON");
}*/

//WiFi client
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


// P3 loop
void loop(void){
  if(client.connect(server, 80)){
    // Measure Signal Strength (RSSI) of Wi-Fi connection
    long rssi = WiFi.RSSI();
    
    // Construct API request body
    String body = "field1=";
    body+= String(rssi);

    Serial.print("RSSI: ");
    Serial.println(rssi);

    client.println("POST /update HTTP/1.1");
    client.println("Host: api.thingspeak.com");
    client.println("User-Agent: ESP8266 (nothans)/1.0");
    client.println("Connection: close");
    client.println("X-THINGSPEAKAPIKEY: " + writeAPIKey);
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Length: " + String(body.length()));
    client.println("");
    client.print(body);
    
  }
}
