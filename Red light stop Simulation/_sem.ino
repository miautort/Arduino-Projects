
// red/yellow - 220ohm
// green - 2k ohm
// buzzer - parallel 2x 50ohm


#define RED_PED 12     // Digital pin connected to the DHT sensor
#define GREEN_PED 11

#define RED_CAR 2
#define YELLOW_CAR 3
#define GREEN_CAR 4

#define BUZZER A0
#define BUTTON A5


void setup() {

  pinMode(BUZZER, OUTPUT);  
  digitalWrite(BUZZER, LOW);
  
  pinMode(BUTTON, INPUT_PULLUP);

  pinMode(RED_CAR, OUTPUT);
  pinMode(YELLOW_CAR, OUTPUT);
  pinMode(GREEN_CAR, OUTPUT);
  digitalWrite(YELLOW_CAR, LOW);
  digitalWrite(RED_CAR, LOW);
  digitalWrite(GREEN_CAR, HIGH);

  pinMode(GREEN_PED, OUTPUT);
  digitalWrite(GREEN_PED, LOW);
  pinMode(RED_PED, OUTPUT);
  digitalWrite(RED_PED, HIGH);
  

}

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}


bool carprior = true;
unsigned long lastchange = 0;

void greenblink(int reps, int dl, int fr)
{
  for (int i = 0; i < reps ; i++ )
  {
      digitalWrite(GREEN_PED, HIGH);
      tone(BUZZER, fr);
      delay(dl);
      digitalWrite(GREEN_PED, LOW);
      noTone(BUZZER);
      delay(dl);
  }
}


void loop() { 
  
  if (carprior == true) 
  {

    if (digitalRead(BUTTON) == LOW)
    {
      while((millis() - lastchange) < 4000){delay(1);}

      delay(500);

      digitalWrite(GREEN_CAR, LOW);
      digitalWrite(YELLOW_CAR, HIGH); 
      delay(1500);

      digitalWrite(YELLOW_CAR, LOW);
      digitalWrite(RED_CAR, HIGH);
      delay (1000);

      digitalWrite(RED_PED, LOW);
      digitalWrite(GREEN_PED, HIGH);
        

      carprior = false;
      lastchange = millis();
    }

  }

  else
  {
    
    if ( ( (millis() - lastchange) > 10000) || (  ( (0.01723 * readUltrasonicDistance(5, 6)) <= 20) && ( (millis() - lastchange) > 4000)  )  )
    {

      greenblink(6, 500, 2000);

      delay(60);
      digitalWrite(RED_PED, HIGH);
      digitalWrite(RED_CAR, LOW);
      digitalWrite(GREEN_CAR, HIGH);
      carprior = true;
      lastchange = millis();

    } 

    delay(100);




  }
  

}

