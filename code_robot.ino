//L9110s_Diagnostic By FalconXCLi
#include <L9110s.h>

#define MS 3      // Middle Sensor
#define LS 4      // Left sensor
#define RS 2      // Right sensor

L9110s car;

int XIX; //AIA = 9 AIB = 5
int YIY; //BIA = 10 BIB = 6
char input;

void setup(){
  Serial.begin(9600);
  pinMode(XIX, OUTPUT);
  pinMode(YIY, OUTPUT);
  pinMode(MS, INPUT);
  pinMode(LS, INPUT);
  pinMode(RS, INPUT);

}

int spd = 190;

void loop()
{

  if(digitalRead(MS))     // Middle Sensor On Line
  {
    if(!digitalRead(LS) && !digitalRead(RS)) //LS and RS not on line
    {car.forward(spd);
    
    }
    
    if(digitalRead(LS) && !digitalRead(RS)) //Sharp Left
    {
    car.left(spd);
    
    }
    if(!digitalRead(LS) && digitalRead(RS)) //Sharp Right
    {
    car.right(spd);
   
    }
    if(digitalRead(LS) && digitalRead(RS)) 
    {
    car.STOP();

    }
  }

  else 
  car.STOP();

delay(5);
}