#include <PID_v1.h>

#include "Arduino.h"
#define echoPin 13        //Sensor echo 
#define trigPin 12       //Sensor trigger
#define cikis 9          //cikisimiz (PWM)
#define switch1 2        //referans noktasına karar veren anahtar  
#define switch2 4        //kontrolcü türüne karar veren anahtar
long duration, distance; //sensör pulse uzunluğu(s)ve ölçtüğü mesafe(cm)
double Setpoint, Input, Output;   //PID nesne kurucusu parametreleri 
PID myPID(&Input, &Output, &Setpoint,6.1,3,2.74, DIRECT); //PID nesnesi
                         
void setup() 
{
 Serial.begin (9600);
 pinMode(trigPin, OUTPUT); 
 pinMode(echoPin, INPUT);
 pinMode(switch1,INPUT);
 pinMode(switch2,INPUT);
 myPID.SetMode(AUTOMATIC);  //PID mod tanımı
}

void loop() 
{  
  if(digitalRead(switch1)==HIGH)  //yarı noktası
  {
    Setpoint=22;
  }
  else                    // 3 çeyrek noktası
  {
  Setpoint=33;
  }
 
  if(digitalRead(switch2)==HIGH)  // PID 
  {
     digitalWrite(trigPin, LOW); 
     delayMicroseconds(2); 

     digitalWrite(trigPin, HIGH);
     delayMicroseconds(10); 
 
     digitalWrite(trigPin, LOW);
     duration = pulseIn(echoPin, HIGH);
     distance = duration/58.2;
     Input = distance;        // mesafe PID’nin inputu 
     myPID.Compute();         // output hesaplanması
     //Serial.println(Output);
     analogWrite(cikis,Output);    // PWM cikisi
     Serial.println(Input);   //Input degerinin Serial Monitor’a yazılması
     delay(50);
  }
  else        // Ac-Kapa Kontrolcu
  {
     digitalWrite(trigPin, LOW); 
     delayMicroseconds(2); 

     digitalWrite(trigPin, HIGH);
     delayMicroseconds(10); 
 
     digitalWrite(trigPin, LOW);
     duration = pulseIn(echoPin, HIGH);
     distance = duration/58.2;
     
 
     Serial.println(distance);  // Mesafenin Serial Monitor’a yazilması
     if(distance>=Setpoint)    //Eger top daha yukarida ise
       analogWrite(cikis,00);  //Motor 50 PWM degerinde calisacak
     else if(distance<Setpoint) //Top daha asagida ise
       analogWrite(cikis,200);   //Motor 80 PWM degerinde calisacak
     delay(50);
  }
}

