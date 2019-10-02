#include "RTClib.h"

#define aref_voltage 3.3

RTC_DS3231 rtc;

const int tempSensorPin = 1;
const int warningLedPin = 2;
const int warningBuzzerPin = 3;

void setup() {
  // put your setup code here, to run once:
  analogReference(EXTERNAL);
  //rtc.begin();
  Serial.begin(9600);
  pinMode(warningLedPin, OUTPUT);
  pinMode(warningBuzzerPin, OUTPUT);
}

void loop() {
  int reading = analogRead(tempSensorPin);
  Serial.print(reading); Serial.println(" reading");  
 
 // converting that reading to voltage, for 3.3v arduino use 3.3
 float voltage = reading * aref_voltage;
 voltage /= 1024.0; 
 
 // print out the voltage
 Serial.print(voltage); Serial.println(" volts");
 
 // now print out the temperature
 float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 Serial.print(temperatureC); Serial.println(" degrees C");

 // now convert to Fahrenheit
 float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
 Serial.print(temperatureF); Serial.println(" degrees F");
  // put your main code here, to run repeatedly:
  //DateTime now = rtc.now();
  //Serial.print(" since midnight 1/1/1970 = ");
  //Serial.print(now.unixtime());
  //Serial.print("s = ");
  //Serial.print(now.unixtime() / 86400L);
  //Serial.println("d");
  alertOn();
  delay(500);
  alertOff();
  delay(500);
}

void alertOn() {
  digitalWrite(warningLedPin, HIGH);
  digitalWrite(warningBuzzerPin, HIGH);
}

void alertOff() {
  digitalWrite(warningLedPin, LOW);
  digitalWrite(warningBuzzerPin, LOW);
}
