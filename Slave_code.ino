#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
// LPIN 2 - HIGH -> Left forward

// Left motor pins
#define EnableL 4
#define LPin1 12
#define LPin2 13

// Right motor pins
#define EnableR 14
#define RPin1 2
#define RPin2 15



void onReceiveData(const uint8_t *mac, const uint8_t *data, int len) {

  int a = (int) data[0];
  int b = (int) data[1];
  int c = (int) data[2];
  
  if( a > 90) {
    a = a - 256;
  }
  if( b > 90) {
    b = b - 256;
  }
  Serial.print(a);
  Serial.print(" : ");
  Serial.println(b);

  
  if( c > 90) {
    c = c - 256;
  }
  accel(a,b,c);
 
}
 
void setup() {
  Serial.begin(115200);
  pinMode (2, OUTPUT);
  WiFi.mode(WIFI_STA);
 
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  
  pinMode(RPin1, OUTPUT);
  pinMode(RPin2, OUTPUT);
  pinMode(LPin1, OUTPUT);
  pinMode(LPin2, OUTPUT);
  pinMode(EnableL, OUTPUT);
  pinMode(EnableR, OUTPUT);

  
  Serial.println("MPU6050 Test");
  delay(2500);
 
}
 
void loop() {
  
  esp_now_register_recv_cb(onReceiveData);
  }


void accel(int x, int y, int z){
  
  if( x<15 && x > -15 && x<15 && x > -15){
    stop_motors();
  }
  
  if(x>45 && y<35 && y>-35){
    forward();
  }
  if ( x<45 && y<(-35) && x>(-45)){
    leftTurn();
  }
  if( x<45 && y>35 && x>(-45)){
    right Turn();
  }
  if(x<(-35) && y<35 && y>-35){
    reverse();   
  }
}

void reverse()
{
  digitalWrite(EnableR,HIGH);
  digitalWrite(EnableL,HIGH);
  digitalWrite(RPin1, LOW);
  digitalWrite(RPin2, HIGH);
  digitalWrite(LPin1, HIGH);
  digitalWrite(LPin2, LOW);
  
}

void forward()
{
  digitalWrite(EnableR,HIGH);
  digitalWrite(EnableL,HIGH);
  digitalWrite(RPin1, HIGH);
  digitalWrite(RPin2, LOW);
  digitalWrite(LPin1, LOW);
  digitalWrite(LPin2, HIGH);
}

void rightTurn()  
{
  digitalWrite(EnableR,HIGH);
  digitalWrite(EnableL,HIGH);
  digitalWrite(RPin1, LOW);
  digitalWrite(RPin2, LOW);
  digitalWrite(LPin1, LOW);
  digitalWrite(LPin2, HIGH);

}
void stop_motors(){
  digitalWrite(EnableR,LOW);
  digitalWrite(EnableL,LOW);
  digitalWrite(RPin1, LOW);
  digitalWrite(RPin2, LOW);
  digitalWrite(LPin1, LOW);
  digitalWrite(LPin2, LOW);
  
}
void leftTurn()  
{
  
  digitalWrite(EnableR,HIGH);
  digitalWrite(EnableL,HIGH);
  digitalWrite(RPin1, HIGH);
  digitalWrite(RPin2, LOW);
  digitalWrite(LPin1, LOW);
  digitalWrite(LPin2, LOW);

}
