#include <Servo.h>
#include <SoftwareSerial.h>
 
#define SIZE 50

SoftwareSerial Bluetooth(2,3);
Servo mx;

int p_BluetoothData=0; 
int c_BluetoothData=0;
int xx_arr[SIZE];
int xx_angle;
float x_sum;

long previousMillis = 0;
long interval = 1000;
 
void setup(){
  Bluetooth.begin(9600);
  Serial.begin(9600);
  Serial.println("Bluetooth On");
  mx.attach(9);
  
 x_sum=0;
 for(int i=0; i<SIZE; i++)
 {
   xx_arr[i] = c_BluetoothData;
   if(xx_arr[i] > 180)
    xx_arr[i] = 180;
   else if(xx_arr[i] < 0)
    xx_arr[i] = 0;
    x_sum+=xx_arr[i];
 }
}
 
void loop() {
////////////////////////////////////////////////
  if (Bluetooth.available()) {
    p_BluetoothData = Bluetooth.read();

  x_sum-=xx_arr[0];  
 
  for(int i=0; i<SIZE-1; i++)
    xx_arr[i] = xx_arr[i+1];

  xx_arr[SIZE-1] = c_BluetoothData;
  x_sum+=xx_arr[SIZE-1];
   
  xx_angle = x_sum/SIZE;

  if(xx_angle > 180)
  xx_angle = 180;
  else if(xx_angle < 0)
   xx_angle = 0;
  }
////////////////////////////////////////////////
  Serial.print(p_BluetoothData);
  Serial.print("     ");
  Serial.print(c_BluetoothData);
  Serial.print("     ");
  Serial.println(xx_angle);
     
  mx.write(xx_angle);
   
  delay(2);

   // voltage check :
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
