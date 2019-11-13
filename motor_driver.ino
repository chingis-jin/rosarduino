#include "commands.h";
// motor one

boolean directionLeftF = false;
boolean directionLeftB = false;
boolean directionRightF = false;
boolean directionRightB = false;

boolean direction(int i){
   if(i == LEFTF){
      return directionLeftF;
   }else if (i == LEFTB) {
      return directionLeftB;
   }else if (i == RIGHTF) {
      return directionRightF;
   }else if (i == RIGHTB) {
      return directionRightB;
   }
}
  void initMotorController() {
  // set all the motor control pins to outputs
  pinMode(PWMLF, OUTPUT);
  pinMode(DIRLF, OUTPUT);
  pinMode(PWMLB, OUTPUT);
  pinMode(DIRLB, OUTPUT);
  pinMode(PWMRF, OUTPUT);
  pinMode(DIRRF, OUTPUT);
  pinMode(PWMRB, OUTPUT);
  pinMode(PWMRB, OUTPUT);
  }

  void setMotorSpeed(int i, int spd) {
    if(spd>MAX_PWM){
      spd=MAX_PWM;
    }
       if(spd<-MAX_PWM){
      spd=-1*MAX_PWM;
    }
    if (i == LEFTF){
        if(spd>=0){
            directionLeftF = FORWARDS;
            digitalWrite(DIRLF, LOW);
            analogWrite(PWMLF, spd);
        }else if(spd < 0){
            directionLeftF = BACKWARDS;
            digitalWrite(DIRLF, HIGH);
            analogWrite(PWMLF, -spd);
        }
    }    
    else if (i == LEFTB) {
        if(spd>=0){
            directionLeftB = FORWARDS;
            digitalWrite(DIRLB, LOW);
            analogWrite(PWMLB, spd);
        }else if(spd<0){
            directionLeftB = BACKWARDS;
            digitalWrite(DIRLB, HIGH);
            analogWrite(PWMLB, -spd);
        }
    }
    else if(i== RIGHTF) {
        if(spd>=0){
            directionRightF = FORWARDS;
            digitalWrite(DIRRF, HIGH);
            analogWrite(PWMRF, spd);
        }else if(spd<0){
            directionRightF = BACKWARDS;
            digitalWrite(DIRRF, LOW);
            analogWrite(PWMRF, -spd);
        }
    }
    else if(i == RIGHTB) {
        if(spd>=0){
            directionRightB = FORWARDS;
            digitalWrite(DIRRB, HIGH);
            analogWrite(PWMRB, spd);
        }else if(spd<0){
            directionRightB = BACKWARDS;
            digitalWrite(DIRRB, LOW);
            analogWrite(PWMRB, -spd);
        }
    }
  }

  void setMotorSpeeds(int leftFSpeed,int leftBSpeed,int rightFSpeed, int rightBSpeed) {
    setMotorSpeed(LEFTF, leftFSpeed);
    setMotorSpeed(RIGHTF, rightFSpeed);
    setMotorSpeed(LEFTB, leftBSpeed);
    setMotorSpeed(RIGHTB, rightBSpeed);
  }
