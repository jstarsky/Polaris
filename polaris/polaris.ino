
// polaris main routine - - - - - - - - - - - - - - - -
// Milos Micic 2013 micicmilos@gmail.com
//     
//                 '
//           *          .
//                   *       '
//             *                *
//
// 
//  
// - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//  Code is for Arduino MEGA/MEGA SDK/ MEGA r3 it can be used on other Arduino platforms with pin revision
//
//


#include <Servo.h> 

int gasPin=0;             // pin for gas potentiometer. 
int wheelPin=1;           // pin for wheel potentimoeter.
int LPWM = 2;             // pin for left pwm motor rotation.
int RPWM = 3;             // pin for right pwm motor rotation.
int LPWMenable=10;        // pin for enabling left rotation.
int RPWMenable=9;         // pin for enabling right rotation.
int servoPin=4;           // pin for wheel servo control
int soundPin=5;           // buzzer pin
int echoPin=22;           // echo pin for HC-SR04 ultrasonic range sensor
int trigPin=24;           // trigger pin for HC-SR04 ultrasonic range sensor
Servo wheels;             // servo controling directiong of wheels
int dirAngle=0;
int wheel;
int gear=0;
int currentspeed;
boolean stopit=false;


void setup() {
  pinMode(gasPin,INPUT);
  pinMode(wheelPin,INPUT);
  pinMode(LPWM,OUTPUT);
  pinMode(RPWM,OUTPUT);
  pinMode(LPWMenable,OUTPUT);
  pinMode(RPWMenable,OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  wheels.attach(4);
  Serial.begin(9600);
  digitalWrite(LPWMenable,HIGH);
  digitalWrite(RPWMenable,HIGH);
  analogWrite(soundPin,255);


}

void loop() {

  adjustGas();
  adjustWheels();
  checkStop();
  delay(20);

}


void adjustWheels(){
  int a;
  a=analogRead(wheelPin);
  a=a/6;
  wheels.write(a);

}

void checkStop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 30 ) {
    analogWrite(soundPin,distance*2);
    stopit=true;
  } 
  else { 
    analogWrite(soundPin,255);
    stopit=false;
  }
}

void adjustGas() {

  currentspeed=analogRead(gasPin);
  if (currentspeed >400 & !stopit) {
    currentspeed=(currentspeed-300)/2; 
    analogWrite(LPWM,currentspeed);
  } 
  else {
    analogWrite(LPWM,0);  
  }
}




