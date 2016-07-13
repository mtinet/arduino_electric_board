#include <SoftwareSerial.h> //시리얼 통신 라이브러리 호출
#include <Servo.h>

SoftwareSerial Bluetooth(2,3);  //시리얼 통신을 위한 객체선언
Servo myServo;

void setup() {
  Bluetooth.begin(9600); //블루투스 시리얼 개방
  Serial.begin(9600);   //시리얼모니터 
  Serial.println("Bluetooth On");
  Serial.println("val   |   error");
  myServo.attach(9);
  delay(3000);
}
 
void loop() {
  while(Bluetooth.available())  
  {
    int val = Bluetooth.read();
    if(val!=255){
      myServo.write(val); 
      Serial.print(val); 
      Serial.println("   |"); 
      delay(5);           //수신 문자열 끊김 방지
    }
    else{
      Serial.print("      | "); 
      Serial.println(val); 
      delay(5);           //수신 문자열 끊김 방지
    }

  }
}

