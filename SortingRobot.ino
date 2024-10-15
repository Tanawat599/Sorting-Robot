  #include <Servo.h>

/*
const int trig0 = 13;
int echo0 = 12;
const int trig1 = 6; 
const int echo1 = 7;
long duration0, distance0;
long duration1, distance1;*/

Servo servo0;
Servo servo1;
Servo servo2;

int posRight = 0;
int posLeft = 0;



/*
const int enA = 6;  // Enable pin for motor A
const int in1 = 2;  // Control pin 1 for motor A
const int in2 = 3;  // Control pin 2 for motor A
const int enB = 7; // Enable pin for motor B
const int in3 = 8;  // Control pin 1 for motor B
const int in4 = 5;  // Control pin 2 for motor B
*/
bool StatusPo = false;

bool StatusRd = false;


int Relay = 2;

int Time = 0;
void setup() {
  Serial.begin(9600);

  servo0.attach(3); // Attach right servo to pin 9
  servo1.attach(9); // Attach left servo to pin 10
  servo2.attach(6);
  servo0.write(0); // Attach left servo to pin 10
  servo1.write(50);
  servo2.write(90);
/*
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);*/
  pinMode(Relay, OUTPUT);
  pinMode(13,OUTPUT);

  digitalWrite(13, LOW);

/**
  pinMode(echo0, INPUT); 
  pinMode(trig0, OUTPUT);
  pinMode(echo1, INPUT); 
  pinMode(trig1, OUTPUT);
*/
  // Turn off motors initially
  /*
  ditalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
*/

}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    if(command == "start"){
      
      StatusPo = true;
    }
    else if (command == "stop") {
      StatusPo = false;
      digitalWrite(13, LOW);
    }
    while(StatusPo){
        
        digitalWrite(13, LOW);
        servo2.write(-360);
        delay(480);
        servo2.write(360);
        delay(120);
        servo2.write(90);
        delay(100);

       
        //delay(400);
        conveyor();
        command = Serial.readStringUntil('\n');
        Serial.println("Hi");
        if(command.startsWith("box=")){ //box=
          
          Serial.println("Box");
          //servo1.write(50);  
          //delay(500);

          
          servo0.write(50);
          delay(100);
          digitalWrite(Relay, HIGH); 
          delay(2500);
          digitalWrite(Relay, LOW); 
          servo0.write(0);
          
        }
        
        else if(command.startsWith("circle=")){
          
          Serial.println("Circle");
          //servo0.write(0);
          //delay(500);

          
          servo1.write(0);
          delay(100);
          digitalWrite(Relay, HIGH); 
          delay(2500);
          digitalWrite(Relay, LOW); 
          servo1.write(50);
        }

        if(command == "stop"){
          digitalWrite(13, LOW);
          StatusPo = false;
          break;
        }
        Time++;
        if(Time == 5){
          servo2.write(360);
          delay(2000);
          servo2.write(90);
          delay(2000);
        }

        
    }

    if(command == "random=1"){
          digitalWrite(13, LOW);
          StatusRd = true;
          Time = 0;
          while(StatusRd){
            digitalWrite(13, HIGH);
            servo2.write(-360);
            delay(470);
            servo2.write(360);
            delay(120);
            servo2.write(90);
            delay(200);

            digitalWrite(13, HIGH);
            //delay(400);
            conveyor();
            command = Serial.readStringUntil('\n');
            Serial.println("Hi");
            if(command.startsWith("circle=")){ //box=
          
              Serial.println("Circle");
              //servo1.write(50);  
              delay(100);

            
              servo0.write(50);
              delay(100);
              digitalWrite(Relay, HIGH); 
              delay(2500);
              digitalWrite(Relay, LOW); 
              servo0.write(0);
          
            }
            else if(command.startsWith("box=")){//circle=
          
              Serial.println("Box");
              //servo0.write(0);
              delay(100);

              
              servo1.write(0);
              delay(100);
              digitalWrite(Relay, HIGH); 
              delay(2500);
              digitalWrite(Relay, LOW); 
              servo1.write(50);
            }

            if(command == "stop"){
              digitalWrite(13, LOW);
              StatusRd = false;
              servo2.write(360);
              delay(2000);
              servo2.write(90);
              delay(100);
              break;
            }
            Time++;
            if(Time == 5){
              servo2.write(360);
              delay(3200);
              servo2.write(90);
              delay(2000);
            }


          }
    }
      





  }
  
}
/*
void Motor0(int speed){
  if(speed > 0){
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enB, speed);
  }
  else if(speed < 0){
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enB, speed);
  }
  else{
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
}

void Motor1(int speed){
  if(speed > 0){
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enA, speed);
  }
  else if(speed < 0){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, speed);
  }
  else{
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
}*/
void conveyor(){
  digitalWrite(Relay, HIGH);
  delay(180);
  digitalWrite(Relay, LOW);
  delay(4000);
  digitalWrite(Relay, HIGH);
  delay(100);
  digitalWrite(Relay, LOW);
  delay(2000);
  //digitalWrite(Relay, HIGH);

  digitalWrite(Relay, LOW);
  delay(100);
  /*
  digitalWrite(Relay, HIGH);
  delay(300);
  digitalWrite(Relay, LOW);
  delay(500);
  digitalWrite(Relay, HIGH);
  delay(300);
  digitalWrite(Relay, LOW);
  delay(500);*/
}

/*
void Ultrasonic(){
  digitalWrite(trig0, LOW); 
  delayMicroseconds(5); 
  digitalWrite(trig0, HIGH); 
  delayMicroseconds(5); 
  digitalWrite(trig0, LOW); //ใช้งานขา trig
 
  duration0 = pulseIn(echo0, HIGH); //อ่านค่าของ echo
  distance0 = (duration0/2) / 29.1; //คำนวณเป็น centimeters
  Serial.print(distance0); 
  Serial.print(" cm\n");

  digitalWrite(trig1, LOW); 
  delayMicroseconds(5); 
  digitalWrite(trig1, HIGH); 
  delayMicroseconds(5); 
  digitalWrite(trig1, LOW); //ใช้งานขา trig
 
  duration1 = pulseIn(echo1, HIGH); //อ่านค่าของ echo
  distance1 = (duration1/2) / 29.1; //คำนวณเป็น centimeters
  Serial.print(distance1); 
  Serial.print(" cm\n");

}*/

/*
if (command.startsWith("Right")) {
      posRight = command.substring(6).toInt();
      //servoRight.write(posRight);
    } 
    else if (command.startsWith("Left")) {
      posLeft = command.substring(5).toInt();
      //servoLeft.write(posLeft);
    }

    else if (command == "leftForward") {
      // Move left motor forward
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(enA, 255); // Full speed
    } else if (command == "leftBackward") {
      // Move left motor backward
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(enA, 255); // Full speed
    } else if (command == "rightForward") {
      // Move right motor forward
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(enB, 255); // Full speed
    } else if (command == "rightBackward") {
      // Move right motor backward
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      analogWrite(enB, 255); // Full speed
    } else if (command == "stop") {
      // Stop all motors
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
    }
*/