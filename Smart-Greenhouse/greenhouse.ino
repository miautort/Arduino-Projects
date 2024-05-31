#include <LCD_I2C.h>
LCD_I2C lcd(0x3F , 16, 2);  // Default address of most PCF8574 modules, change according

#define GLED 3
#define RLED 2
#define PUMP 12
//#define PUMP2 11
#define PLUS_BUTTON 5
#define MIN_BUTTON 4

#define HUM A2
#define HUM_POWER 7
#define LEVEL A1
#define LEVEL_POWER 10

//practic fct asta permite sa nu corodem senzorul de nvl
int readLevel() {
  digitalWrite(LEVEL_POWER, HIGH);  // Turn the sensor ON
  delay(10);                        // wait 10 milliseconds
  int val = analogRead(LEVEL);      // Read the analog value form sensor
  digitalWrite(LEVEL_POWER, LOW);   // Turn the sensor OFF
  return val;                       // send current reading
}

// la fel dar pt soil senzor
int readHum() {
  digitalWrite(HUM_POWER, HIGH);  // Turn the sensor ON
  delay(10);                      // wait 10 milliseconds
  int val = analogRead(HUM);      // Read the analog value form sensor
  digitalWrite(HUM_POWER, LOW);   // Turn the sensor OFF
  return val;                     // send current reading
}

int target_hum = 50;

void setup() {

  pinMode(PLUS_BUTTON, INPUT_PULLUP);
  pinMode(MIN_BUTTON, INPUT_PULLUP);

  pinMode(GLED, OUTPUT);
  pinMode(RLED, OUTPUT);
  pinMode(PUMP, OUTPUT);
//  pinMode(PUMP2, OUTPUT);
  
  digitalWrite(GLED, LOW);
  digitalWrite(RLED, LOW);
  digitalWrite(PUMP, LOW);
  //digitalWrite(PUMP2, LOW);

  //senzor hum
  pinMode(HUM, INPUT);
  pinMode(HUM_POWER, OUTPUT);
  digitalWrite(HUM_POWER, LOW);
  //senzor nvl apa
  pinMode(LEVEL, INPUT);
  pinMode(LEVEL_POWER, OUTPUT);
  digitalWrite(LEVEL_POWER, LOW);

  //pornim ecranul
  lcd.begin();      // If you are using more I2C devices using the Wire library use lcd.begin(false)
  lcd.backlight();  //back light on
}

void loop() {

  int hum = readHum();
  int level = readLevel();

  if (isnan(hum) || isnan(level)) {  // If either sensor reading is Not a Number
    lcd.clear();
    lcd.setCursor(0, 0);  // Setting the cursor in the desired position.
    lcd.print("Check sensors");

    lcd.setCursor(0, 1);  // Setting the cursor in the desired position.
    lcd.print("??");

    digitalWrite(PUMP, LOW);
    //digitalWrite(PUMP2, LOW);
    digitalWrite(RLED, HIGH);
    digitalWrite(GLED, LOW);
  } else {
    char sHum[16];
    sprintf(sHum, "H:%2d%%  ", hum);

    if (level > 50) {
      digitalWrite(RLED, LOW);
      digitalWrite(GLED, HIGH);

      lcd.clear();
      lcd.setCursor(0, 0);  // Setting the cursor in the desired position.
      lcd.print(sHum);

      lcd.setCursor(1, 0);  // Setting the cursor in the desired position.
      lcd.print("Target:");
      lcd.print(target_hum);

      lcd.setCursor(0, 1);  // Setting the cursor in the desired position.
      lcd.print("Crrnt hum:");
      lcd.print(map(hum, 0, 1023, 100, 0));

      if (digitalRead(PLUS_BUTTON) == LOW && target_hum < 100) {
        target_hum += 5;
        delay(200);  // Debounce delay
      }

      if (digitalRead(MIN_BUTTON) == LOW && target_hum > 0) {
        target_hum -= 5;
        delay(200);  // Debounce delay
      }

      if (map(hum, 0, 1023, 100, 0) > target_hum)
       { digitalWrite(PUMP, LOW);
 //       digitalWrite(PUMP2, LOW);
       }
      else
       { digitalWrite(PUMP, HIGH);
 //       digitalWrite(PUMP2, HIGH);
       }
    } else {
      lcd.clear();
      lcd.setCursor(0, 1);  // Setting the cursor in the desired position.
      lcd.print("Is there water??");
      digitalWrite(PUMP, LOW);
//      digitalWrite(PUMP2, LOW);
      digitalWrite(RLED, HIGH);
      digitalWrite(GLED, LOW);

    }
  }

  delay(300);  // Delay to reduce the update rate of the LCD and sensor reads
}