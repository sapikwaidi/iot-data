#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"

WiFiClient client;

const char *USER_EMAIL = "sapikwaidi@gmail.com"; //ganti email firebase
const char *USER_PASSWORD = "ronabumigumilang"; //ganti password firebase
const char *API_KEY = "AIzaSyC1ZRi9QmWvGFy2bV0h4A6vI40MEwnvb3A"; //ganti API firebase
const char *DATABASE_URL = "https://wegodev-iot-c8fc6-default-rtdb.asia-southeast1.firebasedatabase.app/"; //ganti url firebase

const char *WIFI_SSID = "4111"; //ganti nama wifi
const char *WIFI_PASSWORD = "ronakanindaaurora";//ganti password

String uid; // user id

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
FirebaseJson json;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // konek wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print(" Connecting to wifi...");

  while (WiFi.status() != WL_CONNECTED){
  Serial.print(".");
  delay(1000);
  }

  Serial.print("\n");
  Serial.print("IP address : ");
  Serial.print(WiFi.localIP());
  Serial.print("\n");
  Serial.print("MAC : ");
  Serial.println(WiFi.macAddress());
  Serial.print("Terhubung dengan : ");
  Serial.println(WIFI_SSID);

  config.database_url = DATABASE_URL;
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);

  config.token_status_callback = tokenStatusCallback;
  config.max_token_generation_retry = 5;

  Firebase.begin(&config, &auth);

  Serial.println("Getting user Id");
  while(auth.token.uid == ""){
    Serial.print(".");
  }

  uid = auth.token.uid.c_str();
  Serial.print("User Id: ");
  Serial.print(uid);
}

void loop() {
  // put your main code here, to run repeatedly:

}
