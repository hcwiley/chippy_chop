
#include <Stepper.h>

#define BUTTON 2
#define STOP_SWITCH 4

#define FAR_FAN 7
#define NEAR_FAN 6

int dir = -1;
unsigned long last_button = 0;

const int steps = 2000;  // change this to fit the number of steps per revolution
                                     // for your motor

Stepper myStepper(steps, 12,11, 13,3);

int powIn;                                
int total;
void setup()
{
  Serial.begin(115200);
  
  pinMode(FAR_FAN, OUTPUT);
  pinMode(NEAR_FAN, OUTPUT);
  
  digitalWrite(FAR_FAN, HIGH);
  digitalWrite(NEAR_FAN, HIGH);
  
  myStepper.setSpeed(100);
  
  pinMode(BUTTON, INPUT);
  digitalWrite(BUTTON, HIGH);

  pinMode(STOP_SWITCH, INPUT);
  digitalWrite(STOP_SWITCH, HIGH);
  Serial.println("hi");
}

void goTime(){
  digitalWrite(BUTTON, HIGH);
  unsigned long cur_millis = millis();
  // debounce. if the last trigger was less than 200ms forget it!
  if(cur_millis - last_button <= 400)
    return;
  last_button = cur_millis;
  dir *= -1;
  if(dir > 0){
    digitalWrite(FAR_FAN, LOW);
    digitalWrite(NEAR_FAN, HIGH);
  } else {
    digitalWrite(FAR_FAN, HIGH);
    digitalWrite(NEAR_FAN, LOW);
  }
  Serial.println("go");
}

void stopFans(){
  digitalWrite(FAR_FAN, HIGH);
  digitalWrite(NEAR_FAN, HIGH);
}

void loop()
{
 if(digitalRead(STOP_SWITCH) == LOW){
   Serial.println("STOP!");
   stopFans();
 }
 if(digitalRead(BUTTON) == LOW){
   goTime();
 }
}
