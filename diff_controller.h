typedef struct {
  double TargetTicksPerFrame;    // target speed in ticks per frame
  long Encoder;                  // encoder count
  long PrevEnc;                  // last encoder count
  int PrevInput;                // last input
  int ITerm;                    //integrated term
  long output;                    // last motor setting
}
SetPointInfo;

SetPointInfo leftFPID,leftBPID, rightFPID,rightBPID;

int Kp = 20;
int Kd = 12;
int Ki = 0;
int Ko = 50;

unsigned char moving = 0; // is the base in motion?

void resetPID(){
   leftFPID.TargetTicksPerFrame = 0.0;
   leftFPID.Encoder = readEncoder(LEFTF);
   leftFPID.PrevEnc = leftFPID.Encoder;
   leftFPID.output = 0;
   leftFPID.PrevInput = 0;
   leftFPID.ITerm = 0;


   leftBPID.TargetTicksPerFrame = 0.0;
   leftBPID.Encoder = readEncoder(LEFTB);
   leftBPID.PrevEnc = leftBPID.Encoder;
   leftBPID.output = 0;
   leftBPID.PrevInput = 0;
   leftBPID.ITerm = 0;

   rightFPID.TargetTicksPerFrame = 0.0;
   rightFPID.Encoder = readEncoder(RIGHTF);
   rightFPID.PrevEnc = rightFPID.Encoder;
   rightFPID.output = 0;
   rightFPID.PrevInput = 0;
   rightFPID.ITerm = 0;
   
   rightBPID.TargetTicksPerFrame = 0.0;
   rightBPID.Encoder = readEncoder(RIGHTB);
   rightBPID.PrevEnc = rightBPID.Encoder;
   rightBPID.output = 0;
   rightBPID.PrevInput = 0;
   rightBPID.ITerm = 0;
}

void doPID(SetPointInfo * p) {
  long Perror;
  long output;
  int input;
  input = p->Encoder - p->PrevEnc;
  Perror = p->TargetTicksPerFrame - input;

  output = (Kp * Perror - Kd * (input - p->PrevInput) + p->ITerm) / Ko;
  p->PrevEnc = p->Encoder;

  output += p->output;
  if (output >= MAX_PWM)
    output = MAX_PWM;
  else if (output <= -MAX_PWM)
    output = -MAX_PWM;
  else
    p->ITerm += Ki * Perror;

  p->output = output;
  p->PrevInput = input;
}

void updatePID() {
  leftFPID.Encoder = readEncoder(LEFTF);
  rightFPID.Encoder = readEncoder(RIGHTF);
  leftBPID.Encoder = readEncoder(LEFTB);
  rightBPID.Encoder = readEncoder(RIGHTB);
  
  if (!moving){
    if (leftFPID.PrevInput != 0 || rightFPID.PrevInput != 0|| rightBPID.PrevInput != 0|| leftBPID.PrevInput != 0) resetPID();
    return;
  }

  doPID(&rightFPID);
  doPID(&leftFPID);
  doPID(&rightBPID);
  doPID(&leftBPID);
  setMotorSpeeds(leftFPID.output,leftBPID.output, rightFPID.output,rightBPID.output);
}

long readPidIn(int i) {
  long pidin=0;
    if (i == LEFTF){
    pidin = leftFPID.PrevInput;
  }else if (i == LEFTB) {
    pidin = leftBPID.PrevInput;
  }else if (i == RIGHTF) {
    pidin = rightFPID.PrevInput;
  }else if (i == RIGHTB) {
    pidin = rightBPID.PrevInput;
  }
  return pidin;
}

long readPidOut(int i) {
  long pidout=0;
    if (i == LEFTF){
    pidout = leftFPID.output;
  }else if (i == LEFTB) {
    pidout = leftBPID.output;
  }else if (i == RIGHTF) {
    pidout = rightFPID.output;
  }else if (i == RIGHTB) {
    pidout = rightBPID.output;
  }
  return pidout;
}
