#include <SoftwareSerial.h> //시리얼 통신 라이브러리 호출
#include <Servo.h>

#define SIZE 50 //평균값 계산용
int xx_arr[SIZE]; //평균값 계산용
float x_sum; // 평균값 계산용
int val = 0;
int a_val = 0;
int mapval = 0;

SoftwareSerial Bluetooth(2,3);  //시리얼 통신을 위한 객체선언
Servo myServo;



void setup() {
  Bluetooth.begin(9600); //블루투스 시리얼 개방
  Serial.begin(9600);   //시리얼모니터 
  Serial.println("Bluetooth On");
  myServo.attach(9);
  delay(1000);
}
 
void loop() {
  while(Bluetooth.available())  
  {
    Serial.print("val  |  mapval | a_val | error : ");
    val = Bluetooth.read();
    Serial.print(val); 
    Serial.print("   |"); 
      
    mapval = map(val, 0,255, 40,110);
    mapval = constrain(mapval, 40,110);
    Serial.print(mapval); 
    Serial.print("   |");   

    x_sum = 0;
    
    x_sum -= xx_arr[0];
    
    for(int i=0; i<SIZE-1; i++) {
      xx_arr[i] = xx_arr[i+1];

      xx_arr[SIZE-1] = mapval;
      x_sum += xx_arr[SIZE-1];

      a_val = x_sum/SIZE;
    }        

    myServo.write(a_val); 
    Serial.print(a_val); 
    Serial.println("   |"); 
    delay(5);           //수신 문자열 끊김 방지
  }
}

