# Simulation Intelligente d'un Système Feu de Passage Piéton

### Block diagram

<!-- Make sure the path to the picture is correct -->
![Block Diagram](Red light stop Simulation/Block-diagramme.png)

### Schematic

![Schematic](Red light stop Simulation/Schema.png)

[CODE](Red light stop Simulation/_sem.ino)

# Code 
```C

#define RED_PED 12     
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
  pinMode(triggerPin, OUTPUT);  
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
 
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
 
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
    
    if ( ( (millis() - lastchange) > 10000) || (  ( (0.01723 * readUltrasonicDistance(5, 5)) <= 20) && ( (millis() - lastchange) > 4000)  )  )
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
```
