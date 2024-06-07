#define light_pin A1
#define redled 13
#define temp_pin A0

int temp,light;

void setup() {
Serial.begin(9600);
pinMode(temp_pin, INPUT);
pinMode(light_pin, INPUT);
pinMode(redled, OUTPUT);
digitalWrite(redled, LOW);
}

//Teste de analogRead pentru termistor
//25C => 512       /1023
//30C => 456
//35C => 403
//45C => 310

//Teste de analogRead pentru fotorezistor... referinta: 100Lux = camera umbroasa
//100Lux => 322
//200Lux => 389
//300Lux => 322
//400Lux => 281
//500Lux => 249
//600Lux => 226


void loop() {
  temp = analogRead(temp_pin);
  Serial.print(temp);
  Serial.println(" temp");

  light = analogRead(light_pin);
  Serial.print(light);
  Serial.println(" light");

  if  ((temp <= 310) || (temp < 456 && light > 226))
    digitalWrite(redled, HIGH);
  else 
    digitalWrite(redled, LOW);

  delay (500);

}
