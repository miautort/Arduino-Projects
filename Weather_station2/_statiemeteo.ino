#include <Adafruit_BMP280.h>

 #include "DHT.h"
#define DHTPIN A1     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);


#include <LCD_I2C.h>
LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according
byte celsius[8] = {  0x00, 0x0E,  0x0A,  0x0E,  0x00,  0x00,  0x00, 0x00 };




void setup() {
  
  dht.begin();

  pinMode(A0, INPUT);  // brightness sensor


  lcd.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
  lcd.backlight();  //back light on
  lcd.createChar(1, celsius); 

}

void loop() { 


  int humidity = dht.readHumidity();
  float temp = dht.readTemperature();
  if (isnan(humidity) || isnan(temp)) { // Is Not A Number
    humidity = 51;
    temp = 23.4;
  }
  char sHum[16] = "";
  char sTemp[16] = "";
  char fTemp[16];
  dtostrf(temp,4,1,fTemp);
  sprintf(sHum, "H:%2d%%  ", humidity);
  sprintf(sTemp, "T:%s%cC", fTemp, 1 );  //byte(1)   0x01  ascii 1

  char sBright[16] = "";
  int sensorValue = analogRead(A0); // read the input on analog pin 0:
  int voltage = 100-(sensorValue/10);  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  sprintf(sBright, "Light: %2d%% ", voltage);

  lcd.clear();
  lcd.setCursor(0, 0); //  setting the cursor in the desired position.
  lcd.print(sHum);
  lcd.print(sTemp);
  // lcd.write(byte(1)); 
  // lcd.print("C");



  lcd.setCursor(0, 1); //  setting the cursor in the desired position.
  lcd.print(sBright);


  delay(1000);
}