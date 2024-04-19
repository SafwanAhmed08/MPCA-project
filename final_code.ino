#include <Servo.h>
Servo myservo;

#define RIR 0
#define LIR 1
#define FIR 2
#define BIR 3

#define LM1 4
#define LM2 5

#define RM1 6
#define RM2 7

#define RF 8
#define MF 9
#define LF 10

#define GAS 11

#define SERVO 12
#define PUMP 13

bool fire = false;
int pos = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(RF,INPUT); // F1 Right side flame sensor
  pinMode(MF,INPUT); // F2 Middle flame sensor
  pinMode(LF,INPUT); // F3  Left side flame sensor
  pinMode(GAS,INPUT); // Gas sensor 1
  pinMode(RIR,INPUT); // IR 1 right
  pinMode(LIR,INPUT); // IR 2 left
  pinMode(FIR,INPUT); // IR 3 front 
  pinMode(BIR,INPUT); // IR 4 back

  pinMode(LM1,OUTPUT); // Left motor 1
  pinMode(LM2,OUTPUT); // Left motor 2
  pinMode(RM1,OUTPUT); // Right motor 1
  pinMode(RM2,OUTPUT); // Right motor 2

  pinMode(SERVO,OUTPUT);
  myservo.attach(SERVO);
  myservo.write(90);

  pinMode(PUMP,OUTPUT); // Water Pump


  Serial.begin(9600);
}


void put_off_fire(){
  digitalWrite(PUMP,HIGH);
  for(pos = 50; pos < 130; pos++){
    myservo.write(pos);
    delay(10);
  }

  for(pos = 130; pos > 0; pos--){
    myservo.write(pos);
    delay(10);
  }

  fire = false;
  digitalWrite(PUMP,LOW);
}

void go_front(){
  digitalWrite(LM1,HIGH);
  digitalWrite(LM2,HIGH);
  digitalWrite(RM1,HIGH);
  digitalWrite(RM2,HIGH);

  delay(500);

  digitalWrite(LM1,LOW);
  digitalWrite(LM2,LOW);
  digitalWrite(RM1,LOW);
  digitalWrite(RM2,LOW);
}

void go_left(){
  digitalWrite(RM1,HIGH);
  digitalWrite(RM2,HIGH);

  delay(500);

  digitalWrite(RM1,LOW);
  digitalWrite(RM2,LOW);
}

void go_right(){
  digitalWrite(LM1,HIGH);
  digitalWrite(LM2,HIGH);

  delay(500);

  digitalWrite(LM1,LOW);
  digitalWrite(LM2,LOW);  
}

void front_blocked(){
  int left_count = 0;
    if(digitalRead(LIR) == 1){
      go_left();
      while(digitalRead(RIR) == 0){
        go_front();
        left_count++;
      }
      go_right();
      while(digitalRead(RIR) == 0){
        go_front();
      }
      go_right();

      while(left_count > 0){
        go_front();
        left_count--;
      }
      go_left();
    }
    else{
      go_right();
      int right_count = 0;
      while(digitalRead(LIR) == 0){
        go_front();
        right_count++;
      }
      go_left();
      while(digitalRead(LIR) == 0){
        go_front();
      }
      go_left();
      while(right_count > 0){
        go_front();
        right_count--;
      }
      go_right();
    }
}

void move_to_fire(){
  while(digitalRead(RF) == 0){
    if(digitalRead(RIR) == 1 && digitalRead(FIR) == 1){
      go_right();
      go_front();
    }
    if(digitalRead(RIR) == 0){
      go_right();
      front_blocked();
    }
    else{
      front_blocked();
    }
  }
  while(digitalRead(MF) == 0){
    if(digitalRead(FIR) == 1){
      go_front();
    }
    else{
      front_blocked();
    }
    
  }
  while(digitalRead(LF) == 0){
    if(digitalRead(LIR) == 1 && digitalRead(FIR) == 1){
      go_left();
      go_front();
    }
    else if(digitalRead(LIR) == 0){
      go_left();
      front_blocked();
    }
    else{
      front_blocked();
    }
  }
  put_off_fire();
}

void loop() {
  // put your main code here, to run repeatedly:

  if((digitalRead(8) == 0 || digitalRead(9) == 0 || digitalRead(10) == 0) && digitalRead(GAS) == 0){
    fire = true;
    move_to_fire();
  }
}
