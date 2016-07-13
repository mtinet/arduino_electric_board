#include <Servo.h>
#include <SoftwareSerial.h>

Servo servoA;
SoftwareSerial Bluetooth(2,3);

void setup(){
  Serial.begin(9600);
  Bluetooth.begin(9600);
  Serial.println("Bluetooth On");
}

void loop(){
  int var = analogRead(A0);
  Serial.print(var);
  int t_var=map(var,0,650,40,120);
  t_var = constrain(t_var, 0,255);
  Serial.print("   ");
  Serial.println(t_var);
  Bluetooth.write(t_var);
  delay(10);
}
