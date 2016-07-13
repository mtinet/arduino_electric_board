#include <SoftwareSerial.h>// import the serial library
#include <Servo.h>
SoftwareSerial Bluetooth(2, 3); // RX, TX
int BluetoothData; // the data given from Computer
Servo ESC;
long previousMillis = 0;
long interval = 1000;

void setup() {
  // put your setup code here, to run once:
  Bluetooth.begin(9600);
  Serial.begin(9600);
  Serial.println("Bluetooth On");
  ESC.attach(9);
  
}

void loop() {
  // put your main code here, to run repeatedly:
   if (Bluetooth.available()){
     BluetoothData=Bluetooth.read();
     ESC.write(BluetoothData);
     Serial.println(BluetoothData);
   }
   int sensorValue = analogRead(A0);
   float voltage = sensorValue * (5.0 / 1023.0);
   
   unsigned long currentMillis = millis();
     
     if (currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;
     if (voltage <= 3.5)
          Bluetooth.println("Low Battery");
         else
          Bluetooth.println(voltage, DEC); 
     }
}
