#define BAUDRATE     115200
#define MAX_PWM        255

#include "Arduino.h"
#include "commands.h"
#include "motor_driver.h"
#include "encoder_driver.h"
#include "diff_controller.h"
#define PID_RATE           30     // Hz
const int PID_INTERVAL = 1000 / PID_RATE;
unsigned long nextPID = PID_INTERVAL;
#define AUTO_STOP_INTERVAL 2000
long lastMotorCommand = AUTO_STOP_INTERVAL;

/* Variable initialization */
int arg = 0;
int indexx = 0;
char chr;
char cmd;
char argv1[16];
char argv2[16];
char argv3[16];
char argv4[16];
long arg1;
long arg2;
long arg3;
long arg4;

void resetCommand() {
  cmd = NULL;
  memset(argv1, 0, sizeof(argv1));
  memset(argv2, 0, sizeof(argv2));
  memset(argv3, 0, sizeof(argv3));
  memset(argv4, 0, sizeof(argv4));
  arg1 = 0;
  arg2 = 0;
  arg3 = 0;
  arg4 = 0;
  arg = 0; 
  indexx = 0;
}

int runCommand() {
  int i = 0;
  char *p = argv1;
  char *str;
  int pid_args[4];
  arg1 = atoi(argv1);
  arg2 = atoi(argv2);
  arg3 = atoi(argv3);
  arg4 = atoi(argv4);

  switch (cmd) {
    case GET_BAUDRATE:
      Serial.println(BAUDRATE);
      break;
    case READ_PIDIN:
      Serial.print( readPidIn(LEFTF));
      Serial.print(" ");
      Serial.print( readPidIn(LEFTB));
      Serial.print(" ");
      Serial.print( readPidIn(RIGHTF));
      Serial.print(" ");
      Serial.println( readPidIn(RIGHTB));
      break;      
    case READ_PIDOUT:
      Serial.print( readPidOut(LEFTF));
      Serial.print(" ");
      Serial.print( readPidOut(LEFTB));
      Serial.print(" ");
      Serial.print( readPidOut(RIGHTF));
      Serial.print(" ");
      Serial.println( readPidOut(RIGHTB));
      break;
    case READ_ENCODERS:
      Serial.print(readEncoder(LEFTF));
      Serial.print(" ");
      Serial.print(readEncoder(LEFTB));
      Serial.print(" ");
      Serial.print(readEncoder(RIGHTF));
      Serial.print(" ");
      Serial.println(readEncoder(RIGHTB));
      break;
    case RESET_ENCODERS:
      resetEncoders();
      resetPID();
      Serial.println("OK");
      break;
    case MOTOR_SPEEDS:
      lastMotorCommand = millis();
      if (arg1 == 0 && arg2 == 0 && arg3 == 0 && arg4 ==0) {
        setMotorSpeeds(0,0,0,0);
        moving = 0;
      }
      else moving = 1;
      leftFPID.TargetTicksPerFrame = arg1;
      leftBPID.TargetTicksPerFrame = arg2;
      rightFPID.TargetTicksPerFrame = arg3;
      rightBPID.TargetTicksPerFrame = arg4;
      Serial.println(arg1);
      Serial.println(arg2);
      Serial.println(arg3);
      Serial.println(arg4);
      Serial.println("OK");
      break;
    case UPDATE_PID:
      while ((str = strtok_r(p, ":", &p)) != '\0') {
        pid_args[i] = atoi(str);
        i++;
      }
      Kp = pid_args[0];
      Kd = pid_args[1];
      Ki = pid_args[2];
      Ko = pid_args[3];
      Serial.println("OK");
      break;
    case ANALOG_READ:
      Serial.println(analogRead(arg1));
      break;
    case DIGITAL_READ:
      Serial.println(digitalRead(arg1));
      break;
    case ANALOG_WRITE:
      analogWrite(arg1, arg2);
      Serial.println("OK");
      break;
    case DIGITAL_WRITE:
      if (arg2 == 0) digitalWrite(arg1, LOW);
      else if (arg2 == 1) digitalWrite(arg1, HIGH);
      Serial.println("OK");
      break;
    case PIN_MODE:
      if (arg2 == 0) pinMode(arg1, INPUT);
      else if (arg2 == 1) pinMode(arg1, OUTPUT);
      Serial.println("OK");
      break;
    default:
      Serial.println("Invalid Command");
      break;
  }
}

unsigned long timex = 0, old_time = 0;
void setup() {
  Serial.begin(BAUDRATE);
  initEncoders();
  initMotorController();
  resetPID();
}

void loop() {
  while (Serial.available() > 0) {
    chr = Serial.read();
    if (chr == 13) {
      if (arg == 1) argv1[indexx] = NULL;
      else if (arg == 2) argv2[indexx] = NULL;
      else if (arg == 3) argv3[indexx] == NULL;
      else if (arg == 4) argv4[indexx] == NULL;
      runCommand();
      resetCommand();
    }
    else if (chr == ' ') {
      if (arg == 0) arg = 1;
      else if (arg == 1)  {
        argv1[indexx] = NULL;
        arg = 2;
        indexx = 0;
      }
      else if (arg == 2){
        argv2[indexx] = NULL;
        arg = 3;
        indexx = 0;
      }
      else if (arg == 3){
        argv3[indexx] = NULL;
        arg = 4;
        indexx = 0;
      }
      continue;
    }
    else {
      if (arg == 0) {
        cmd = chr;
      }
      else if (arg == 1) {
        argv1[indexx] = chr;
        indexx++;
      }
      else if (arg == 2) {
        argv2[indexx] = chr;
        indexx++;
      }
      else if (arg == 3){
        argv3[indexx] =chr;
        indexx++;  
      }
      else if (arg ==4){
        argv4[indexx] =chr;
        indexx++;
      }
    }
  }

  if (millis() > nextPID) {
    updatePID();
    nextPID += PID_INTERVAL;
  }

  if ((millis() - lastMotorCommand) > AUTO_STOP_INTERVAL) {
    ;
    setMotorSpeeds(0,0,0,0);
    moving = 0;
  }
}
