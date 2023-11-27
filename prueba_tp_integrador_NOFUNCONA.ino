
//LIBRERÍAS
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SPI.h> //Why? Because library supports SPI and I2C connection
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h> //encontrar en el administrador de librerias

#define PIN_RELE 23
#define PIN_HUMEDAD 33
#define PIN_LDR 32
#define PIN_BTN_1 36
#define PIN_BTN_2 39
#define PIN_BTN_3 34
#define PIN_BTN_4 35
#define PIN_BTN_5 16
#define PIN_BUZZER 17
#define PIN_LED_1 5
#define PIN_LED_2 18
#define PIN_LED_3 19
Adafruit_BMP280 bmp;

int lcdColumns = 16;
int lcdRows = 2;
float temperature; 

LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows);  


void setup() {
  Serial.begin(115200);
  pinMode(PIN_LDR, INPUT);
  pinMode(PIN_BTN_1, INPUT);
  pinMode(PIN_BTN_2, INPUT);
  pinMode(PIN_BTN_3, INPUT);
  pinMode(PIN_BTN_4, INPUT);
  pinMode(PIN_BTN_5, INPUT);
  pinMode(PIN_RELE, OUTPUT);
  pinMode(PIN_LED_1, OUTPUT);
  pinMode(PIN_LED_2, OUTPUT);
  pinMode(PIN_LED_3, OUTPUT);
  digitalWrite(PIN_RELE,HIGH);
  digitalWrite(PIN_LED_1,LOW);

  lcd.begin();                 
  lcd.backlight();
  bmp.begin();
  Serial.println("Adafruit BMP280 test:");
}

void loop() {

  //Variables
    Serial.println(digitalRead(PIN_BTN_5));
  temperature = bmp.readTemperature();
  int sensorValue = analogRead(PIN_HUMEDAD);
  
  //Puerto serie
  Serial.print(("Hum: "));
  Serial.println(analogRead(PIN_HUMEDAD));
  Serial.print(("Temp: "));
  Serial.print(temperature);
  Serial.print("C");
  Serial.println();
  Serial.print("Marijuana Soil Humidity  is: ");
  Serial.println(sensorValue);

  if (sensorValue >= 1000)  (Serial.print("SOIL IS TOO DRY!!!!!    "));
  else if ((sensorValue <= 999)  && (sensorValue >=901)) (Serial.print("SOIL IS PERFECT!!!!!    "));
  else  if (sensorValue <= 900) (Serial.print("SOIL IS TOO WET!!!!!    "));
  else;

  //Display
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.setCursor(7,0);
  lcd.print(temperature);
  lcd.setCursor(14, 0);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Hum:");
  lcd.setCursor(5,1);
  lcd.print(sensorValue);

  if(digitalRead(PIN_BTN_1)== LOW){
    digitalWrite(PIN_LED_1,HIGH);
    digitalWrite(PIN_LED_2,HIGH);
    digitalWrite(PIN_LED_3,HIGH);
    digitalWrite(PIN_BUZZER,HIGH);
    digitalWrite(PIN_RELE,LOW);
  }
  
  if(digitalRead(PIN_BTN_2) == LOW){
    digitalWrite(PIN_LED_1,HIGH);
    digitalWrite(PIN_LED_2,HIGH);
    digitalWrite(PIN_LED_3,HIGH);
    digitalWrite(PIN_BUZZER,HIGH);
    digitalWrite(PIN_RELE,LOW);
  }

  if(digitalRead(PIN_BTN_3) == LOW){
    digitalWrite(PIN_LED_1,HIGH);
    digitalWrite(PIN_LED_2,HIGH);
    digitalWrite(PIN_LED_3,HIGH);
    digitalWrite(PIN_BUZZER,HIGH);
    digitalWrite(PIN_RELE,LOW);
  }

  if(digitalRead(PIN_BTN_4) == LOW){
    digitalWrite(PIN_LED_1,HIGH);
    digitalWrite(PIN_LED_2,HIGH);
    digitalWrite(PIN_LED_3,HIGH);
    digitalWrite(PIN_BUZZER,HIGH);
    digitalWrite(PIN_RELE,LOW);
  }

  if(digitalRead(PIN_BTN_5) == LOW){
    digitalWrite(PIN_LED_1,HIGH);
    digitalWrite(PIN_LED_2,HIGH);
    digitalWrite(PIN_LED_3,HIGH);
    digitalWrite(PIN_BUZZER,HIGH);
    digitalWrite(PIN_RELE,LOW);
  }
}
