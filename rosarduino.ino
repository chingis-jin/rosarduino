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
    Serial.println("ADVANCE");
}
void BACK()
{
    Serial.println("BACK");
}
void LEFT()
{
    Serial.println("LEFT");
}
void 