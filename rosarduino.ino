#define BAUDRATE 115200
#define GET_BAUDRATE 'b'
#define PWMA 3 //L1 MOTO SPEED
#define DIRA 2 //L1 MOTO DIRECTION
#define PWMB 5 //L2 MOTO SPEED
#define DIRB 4 //L2 MOTO DIRECTION
#define PWMC 6 //R1 MOTO SPEED
#define DIRC 7 //R1 MOTO DIRECTION
#define PWMD 9 //R2 MOTO SPEED
#define DIRD 8 //R2 MOTO DIRECTION

void ADVANCE()
{
    Serial.println("go");
}
void BACK()
{
    Serial.println("BACK");
}
void LEFT()
{
    Serial.println("LEFT");
}
void LEFTM()
{
    Serial.println("LEFTM");
} 
void RIGHT()
{
    Serial.println("RIGHT");
}
void RIGHTM()
{
    Serial.println("RIGHTM");
}
void STOP()
{
    Serial.println("STOP");
}

void CMD_Control()
{
    char Cmd_Date=0;
    if(Serial.available())
    {
        Cmd_Date=Serial.read();
    }
    if(Cmd_Date=='w')
    {
        ADVANCE();
    }
    if(Cmd_Date=='B')
    {
       BACK();
    }
    if(Cmd_Date=='l')
    { 
        LEFT();
    }
    if(Cmd_Date=='L')
    {
        LEFTM();
    }
    if(Cmd_Date=='r')
    {
        RIGHT();
    }
    if(Cmd_Date=='R')
    {
        RIGHTM();
    }
    if(Cmd_Date=='s')
    {
        STOP();
    }
    if(Cmd_Date=='b')
    {
        Serial.println(BAUDRATE);
    }
    
}

void setup()
{
    Serial.begin(BAUDRATE);

}
void loop()
{
    CMD_Control();

}
