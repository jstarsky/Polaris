
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

#include <Servo.h> 

int gasPin=0;            // pin for gas potentiometer. 
int wheelPin=1;          // pin for wheel potentimoeter.
int LPWM = 2;            // pin for left pwm motor rotation.
int RPWM = 3;            // pin for right pwm motor rotation.
int LPWMenable=10;        // pin for enabling left rotation.
int RPWMenable=9;        // pin for enabling right rotation.
int servoPin=4;          // pin for wheel servo control
int soundPin=5;          // buzzer pin
int echoPin=22;
int trigPin=24;
Servo wheels;            // servo controling directiong of wheels
int dirAngle=0;
int wheel;
int gear=0;


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
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 100 ) {
  analogWrite(soundPin,distance*2);
  } else { 
  analogWrite(soundPin,255);
  }
  adjustGas();
  adjustWheels();
  delay(50);

}


void adjustWheels(){
  int a;
  a=analogRead(wheelPin);
  a=a/6;
  wheels.write(a);

}

void checkStop() {
}

void adjustGas() {
  int a;
  a=analogRead(gasPin);
  if (a>400) {
    a=(a-300)/2; 
    analogWrite(LPWM,a);
  } 
  else {
    analogWrite(LPWM,0);
  }
}

