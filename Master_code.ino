#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <GY6050.h>
GY6050 gyro(0x68);
uint8_t broadcastAddress[] = {0xFF, 0xFF,0xFF,0xFF,0xFF,0xFF};
 
void setup() {
  Serial.begin(115200);
  gyro.initialisation();
  WiFi.mode(WIFI_STA);
  Serial.println();
  Serial.println(WiFi.macAddress());
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  else{
    Serial.println("Initialized successfully");
  }
  // register peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  else{
    Serial.println("Succeded to add peer");
  }
  
  
}

void loop() {
  uint8_t a[3];
  a[0] = gyro.refresh('A', 'X'); 
  a[1]=  gyro.refresh('A', 'Y');
  a[2] = gyro.refresh('A', 'Z');
  Serial.print("AcX = ");
  Serial.print(gyro.refresh('A', 'X'));           
  Serial.print(" | AcY = ");
  Serial.print(gyro.refresh('A', 'Y'));           
  Serial.print(" | AcZ = ");
  Serial.println(gyro.refresh('A', 'Z') );  
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t*)&a, sizeof(a));
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  
  }
