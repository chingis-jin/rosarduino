#include "motor_driver.h"
#include "commands.h";

/* encode */
volatile long leftF_enc_pos = 0L;
volatile long rightF_enc_pos = 0L;
volatile long leftB_enc_pos = 0L;
volatile long rightB_enc_pos = 0L;
int leftF_rotate = 0;
int rightF_rotate = 0;
int leftB_rotate = 0;
int rightB_rotate = 0;

void initEncoders(){
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(SDA1, INPUT);
  pinMode(SCL1, INPUT);
  attachInterrupt(A4, encoderLeftFISR, CHANGE);  
  attachInterrupt(A5, encoderLeftFISR,  CHANGE);  
  attachInterrupt(A2, encoderLeftBISR, CHANGE);
  attachInterrupt(A3, encoderLeftBISR, CHANGE);
  attachInterrupt(A0, encoderRightFISR, CHANGE);  
  attachInterrupt(A1, encoderRightFISR,  CHANGE);  
  attachInterrupt(SDA1, encoderRightBISR, CHANGE);
  attachInterrupt(SCL1, encoderRightBISR, CHANGE);
}

void encoderLeftFISR(){
    if(direction(LEFTF) == BACKWARDS){
        leftF_enc_pos--;
    }else{
        leftF_enc_pos++;
    }
}

void encoderRightFISR(){
    if(direction(RIGHTF) == BACKWARDS){
      rightF_enc_pos--;
    }else{
      rightF_enc_pos++;
    }
}
void encoderLeftBISR(){
    if(direction(LEFTB) == BACKWARDS){
        leftB_enc_pos--;
    }else{
        leftB_enc_pos++;
    }
}

void encoderRightBISR(){
    if(direction(RIGHTB) == BACKWARDS){
      rightB_enc_pos--;
    }else{
      rightB_enc_pos++;
    }
}

  long readEncoder(int i) {
      long encVal = 0L;
  if (i == LEFTF)  {
    noInterrupts();
    encVal = leftF_enc_pos;
    interrupts();
  }
  else if(i == RIGHTF){
    noInterrupts();
    encVal = rightF_enc_pos;
    interrupts();
  }  else if(i == LEFTB){
    noInterrupts();
    encVal = leftB_enc_pos;
    interrupts();
  }  else if(i == RIGHTB){
    noInterrupts();
    encVal = rightB_enc_pos;
    interrupts();
  }
  return encVal;
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFTF){
      noInterrupts();
      leftF_enc_pos=0L;
      interrupts();
      return;
    } else if(i == LEFTB) { 
      noInterrupts();
      leftB_enc_pos=0L;
      interrupts();
      return;
    } else if(i == RIGHTF) { 
      noInterrupts();
      rightF_enc_pos=0L;
      interrupts();
      return;
    } else if(i == RIGHTB) { 
      noInterrupts();
      rightB_enc_pos=0L;
      interrupts();
      return;
    }
  }

void resetEncoders() {
  resetEncoder(LEFTF);
  resetEncoder(RIGHTF);
  resetEncoder(LEFTB);
  resetEncoder(RIGHTB);
}
