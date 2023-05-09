#include <DHT.h>
#include <DHT_U.h>
#include <SoftwareSerial.h>
#include<Servo.h>

SoftwareSerial espSerial(5, 6);
Servo Myservo;
DHT dht(13,DHT11);
#define soundSensor A0
const int buzzer = 3;
int pos=0;
String str="";
String status="";

//#define motorPin 8

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  espSerial.begin(115200);
  pinMode(soundSensor,INPUT);
  noTone(buzzer);
  dht.begin();
  Myservo.attach(9);
  //pinMode(motorPin, OUTPUT);
}


void loop() {
  Myservo.write(pos);
  pinMode (soundSensor, INPUT);
  float t = dht.readTemperature();
  Serial.print("Temperature  ");
  Serial.println(t);
  int sample = analogRead(soundSensor);
  if (sample > 170)
  {
    Serial.print("Loud:");
    Serial.println(sample);
    status = "Baby is awake!";
    tone(buzzer,250);
    delay(500);
    noTone(buzzer);
    for(pos=0;pos<90;pos++){
    Myservo.write(pos);
    delay(100);
    }    
    delay(500);
    for(pos=90;pos>=0;pos--){
    Myservo.write(pos);
    delay(100);
    }
    delay(500);
  }
  else
  {
    Serial.print("Quiet:");
    Serial.println(sample);
    status = "Baby is asleep";
  }
//  if (t > 20)
//  {
//    //turn on dc motor
//    digitalWrite(motorPin, HIGH);
//  
//  }
//  else if (t < 10)
//  {
//    //turn off dc motor
//    digitalWrite(motorPin, LOW);
//  }
    
  str = String("Temperature in baby's room = ")+String(t)+String(" Updates = ")+String(status);
  //str = String(status)+String(t);
  espSerial.println(str);
  delay(1000);
  
}
