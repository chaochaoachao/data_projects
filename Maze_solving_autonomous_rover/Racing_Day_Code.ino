#include <Servo.h>                           // Include servo library

int trigPin_1 = 8;    // Trigger sensor 1
int echoPin_1 = 9;    // Echo 1
float duration_1, L_1;

int trigPin_2 = 2;    // Trigger sensor 2
int echoPin_2 = 3;    // Echo 2
float duration_2, L_2;

int trigPin_3 = 4;    // Trigger sensor 3
int echoPin_3 = 5;    // Echo 3
float duration_3, L_3;

int trigPin_4 = 6;    // Trigger sensor 4
int echoPin_4 = 7;    // Echo 4
float duration_4, L_4;

int fwdtime=1000;
int left_trntime=2300; 
int right_trntime=1100;
int stay=2000;
int minor_change=400; 
int minor_change_fwd=200; 
int minor_left=255;
int mionr_right=122;

Servo servoLeft;                             // Declare left servo
Servo servoRight;                            // Declare right servo


void setup(){                                 // Built in initialization block
  Serial.begin(115200);
  servoLeft.attach(11);                      // Attach left signal to pin 11
  servoRight.attach(12);                    // Attach right signal to pin 12                   

  pinMode(trigPin_1, OUTPUT);
  pinMode(echoPin_1, INPUT);

  pinMode(trigPin_2, OUTPUT);
  pinMode(echoPin_2, INPUT);
  
  pinMode(trigPin_3, OUTPUT);
  pinMode(echoPin_3, INPUT);
  
  pinMode(trigPin_4, OUTPUT);
  pinMode(echoPin_4, INPUT);
}  




void loop(){                                  // Main loop auto-repeats

  //motor forward
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin_1, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_1, LOW);


  pinMode(echoPin_1, INPUT);
  duration_1 = pulseIn(echoPin_1, HIGH);

  L_1 = (duration_1/2)*0.0343; 


  digitalWrite(trigPin_2, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_2, LOW);


  pinMode(echoPin_2, INPUT);
  duration_2 = pulseIn(echoPin_2, HIGH);

   L_2 = (duration_2/2) *0.0343;


  digitalWrite(trigPin_3, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin_3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_3, LOW);

  pinMode(echoPin_3, INPUT);
  duration_3 = pulseIn(echoPin_3, HIGH);

  L_3 = (duration_3/2) *0.0343;


  digitalWrite(trigPin_4, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin_4, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_4, LOW);

  pinMode(echoPin_4, INPUT);
  duration_4 = pulseIn(echoPin_4, HIGH);

  L_4 = (duration_4/2) *0.0343;

  Serial.println(L_1);
  Serial.println(L_2);
  Serial.println(L_3);
  Serial.println(L_4);
  Serial.println();

  //https://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/  ultrasonic sensor obtaining destances
  
  if (L_1 >= 30){


      if (   (L_2 + L_4) < 15.0 && L_2 < 5.50){ // translate adjustment
        minor_left_shift();
        //Serial.println("left translate"); // not tilted, but too close to the right wall, translate the robot leftwards
       } 
       
      else if (   (L_2 + L_4) < 15.0 && L_4 < 5.50){
        minor_right_shift();
        //Serial.println("right translate"); // not tilted, but too close to the left wall, translate the robot leftwards
       }

      else if ( (L_2 + L_4) > 15.0){  // tilting adjustment
  
        if( (L_2 > L_4) && (L_1 > L_3)){
          right_minor();
          //Serial.println('3'); // tilted clockwise, close to left wall, right motor forward
        } else if ( (L_2 >L_4) && (L_1 < L_3)){
          left_minor();
          //Serial.println('4'); // tilted counterclockwise, close to left wall, right motor backward
        }
  
        else if( (L_2 < L_4) && (L_1 > L_3)){
          left_minor();
          //Serial.println('5'); // tilted counterclockwise, close to right wall, left motor forward
        } else if ( (L_2 < L_4) && (L_1 < L_3)){
          right_minor();
          //Serial.println('6'); // tilted clockwise, close to right wall, left motor backward
        }
      }
      else {
        Move_Fwd();
        //Serial.println("move");
      }
  }
if (L_1 < 30 && L_1 > 9.5) {
   Move_Fwd();
}

  if (L_1 < 9.5){ //turning
    
            
    if (L_2 < 23.00 && L_4 < 23.00){ // hit a dead end!!!!!!!!!!!!!!!!!!! turn 180 deg and find a turning point and turn.
      Right_Turn();
      Right_Turn();
      //Serial.println('9');} //right turn 180 deg


        /* while (L_2<23.00 && L_4 < 23.00){
                                                                         if (   (L_2 + L_4) < 17.50 && L_2 < 5.50){ // translate adjustment
                              Serial.println("left translate"); // not tilted, but too close to the right wall, translate the robot leftwards

                          delay (1000);
                               }
                          
                              else if (   (L_2 + L_4) < 17.50 && L_4 < 5.50){
                              Serial.println("right translate"); // not tilted, but too close to the left wall, translate the robot leftwards
                          delay(1000);
                               }
                        
                          
                        
                              else if ( (L_2 + L_4) > 17.50){  // tilting adjustment
                          
                                if( (L_2 >L_4) && (L_1>L_3)){
                                 Serial.println('3'); // tilted clockwise, close to left wall, right motor forward
                                delay (1000);
                                }else if ( (L_2 >L_4) && (L_1<L_3)){
                                 Serial.println('4'); // tilted counterclockwise, close to left wall, right motor backward
                              delay (1000);
                                         
                                  }
                          
                                  else if( (L_2 <L_4) && (L_1>L_3)){
                                   Serial.println('5'); // tilted counterclockwise, close to right wall wall, left motor forward
                                  delay (1000);
                                  } else if ( (L_2 <L_4) && (L_1<L_3)){
                                     Serial.println('6'); // tilted clockwise, close to right wall, left motor backward
                                     
                                      delay (1000);
                                      }
                                  }
                                                                                
                                                     
                          // before these are the adjustment
                            else { Serial.println("move");
                                  delay (1000);
                                        }
                                  }
                               if (L_2 >23.00 ){
                          
                              Serial.println('7'); //right turn 90 deg
                              }
                          
                               else if (L_4 >23.00 ){
                          
                              Serial.println('8'); //left turn 90 deg
                              }
    } */
    }

    if (L_2 > 23.00 && L_4 < 23.00){
      Right_Turn();
       Move_Fwd();
      //Serial.println('7'); //right turn 90 deg
    }
            
    if (L_2<23.00 && L_4>23.00){
      Left_Turn();
       Move_Fwd();
      //Serial.println('8'); //left turn 90 deg
    }
            
    else if (L_2>23.00 && L_4>23.00){
      Right_Turn();
       Move_Fwd();
      //Serial.println('7'); //right turn 90 deg
    }

    delay(1000);
          
    }

  }




  void Right_Turn(){
  servoLeft.writeMicroseconds(1530);         // right turn
  servoRight.writeMicroseconds(1550);        
  delay(right_trntime);  
  }

  void Left_Turn(){
  servoLeft.writeMicroseconds(1455);         
  servoRight.writeMicroseconds(1450);        // left turn
  delay(left_trntime);  
  }

  void Move_Fwd(){
  servoLeft.writeMicroseconds(1545);         
  servoRight.writeMicroseconds(1420);        // fwd
  delay(fwdtime);
  }
  
  void minor_right_shift(){
  servoLeft.writeMicroseconds(1530);         // minor shift to right step 1-small right turn
  servoRight.writeMicroseconds(1550);        
  delay(minor_change); 

  servoLeft.writeMicroseconds(1545);         // fwd
  servoRight.writeMicroseconds(1420);        
  delay(minor_change_fwd);

  servoLeft.writeMicroseconds(1455);         // minor shift to right step 2-small left turn
  servoRight.writeMicroseconds(1450);        
  delay(minor_change*23/11);
  }  

  void minor_left_shift(){
  servoLeft.writeMicroseconds(1455);         // minor shift to left step 1-small right turn
  servoRight.writeMicroseconds(1450);        
  delay(minor_change*23/11);
 

  servoLeft.writeMicroseconds(1545);         // fwd
  servoRight.writeMicroseconds(1420);        
  delay(minor_change_fwd);

  servoLeft.writeMicroseconds(1530);         // minor shift to left step 2-small left turn
  servoRight.writeMicroseconds(1550);        
  delay(minor_change); 
  }

  void left_minor(){ 
  servoLeft.writeMicroseconds(1455);         
  servoRight.writeMicroseconds(1450);        // minor left turn
  delay(minor_left);
  }
  
  void right_minor(){
  servoLeft.writeMicroseconds(1530);         // minor right turn
  servoRight.writeMicroseconds(1550);        
  delay(mionr_right);    
  }
  void parking(){
  servoLeft.detach();                        // stay
  servoRight.detach();       
  delay(stay);  
  }

  void reactive(){
  servoLeft.attach(7);                        //  Re-sending servo signals
  servoRight.attach(12);
  }
