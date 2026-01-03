#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = A3, d5 = A2, d6 = A1, d7 = 6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Default address is 0x53, alternate address is 0x1D
#define ACCEL1_ADDRESS 0x53  // Sensor 1
#define ACCEL2_ADDRESS 0x1D  // Sensor 2 (ALT ADDRESS pin connected to VCC)

Adafruit_ADXL345_Unified accel1 = Adafruit_ADXL345_Unified(12345);  // ID 12345 for sensor 1
Adafruit_ADXL345_Unified accel2 = Adafruit_ADXL345_Unified(67890);  // ID 67890 for sensor 2
int X;
int Y;
float TIME = 0;
float FREQUENCY = 0;
float WATER = 0;
float TOTAL = 0;
float LS = 0;
const int input = A0;
int rain = 10;
int led = 8;
int buzzer = 7;
String msg;
void setup() {
  Serial.begin(9600);
  pinMode(rain, INPUT);
  pinMode(input, INPUT);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(led, LOW);
  digitalWrite(buzzer, LOW);
  // accel1.begin(ACCEL1_ADDRESS);
  // accel2.begin(ACCEL2_ADDRESS);
  Serial.println("sensor initization.......");
  lcd.begin(16, 2);
  lcd.print("Networked MEMS pressure");
  lcd.setCursor(0, 1);
  lcd.print("sensor design to detect");
  delay(1000);
  lcd.clear();
  lcd.print("pore water pressure for");
  lcd.setCursor(0, 1);
  lcd.print("landslide monitoring");
  delay(1000);
  // Initialize sensor 1 with default address
  if (!accel1.begin(ACCEL1_ADDRESS)) {
    Serial.println("Failed to initialize ADXL345 sensor 1");
    lcd.clear();
    lcd.print(" SENSOR1 Failed to initialize");
    delay(1000);
    while (1)
      ;
  }
  accel1.setRange(ADXL345_RANGE_2_G);

  // Initialize sensor 2 with alternate address
  if (!accel2.begin(ACCEL2_ADDRESS)) {
    Serial.println("Failed to initialize ADXL345 sensor 2");
    lcd.clear();
    lcd.print(" SENSOR2 Failed to initialize");
    delay(1000);
    while (1)
      ;
  }
  accel2.setRange(ADXL345_RANGE_2_G);
  delay(1000);
}
void loop() {
  int raindrop = digitalRead(rain);
  X = pulseIn(input, HIGH);
  Y = pulseIn(input, LOW);
  TIME = X + Y;
  FREQUENCY = 1000000 / TIME;
  WATER = FREQUENCY / 7.5;
  LS = WATER / 60;
  if (FREQUENCY >= 0) {
    if (isinf(FREQUENCY)) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("VOL. :0.00");
      lcd.setCursor(0, 1);
      lcd.print("TOTAL:");
      lcd.print(TOTAL);
      lcd.print("L");
      delay(1000);
    } else {
      TOTAL = TOTAL + LS;
      Serial.println(FREQUENCY);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("FLOW WATER.:");
      lcd.print(WATER);
      lcd.print(" L/M");
      lcd.setCursor(0, 1);
      lcd.print("TOTAL:");
      lcd.print(TOTAL);
      lcd.print(" L");
      delay(1000);
      if (WATER > 40.0 || TOTAL > 10.0) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("WATER OVER FLOW");
        // Siren-style flashing and buzzing
        for (int i = 0; i < 20; i++) {  // Repeat the pattern 5 times
          digitalWrite(led, HIGH);
          digitalWrite(buzzer, HIGH);
          delay(150);
          digitalWrite(led, LOW);
          digitalWrite(buzzer, LOW);
          delay(150);
        }
        msg = "WATER OVER FLOW......,";
        SendMessage();
      }
    }
  }
  Serial.print("Rain drop :");
  Serial.println(raindrop);
  lcd.clear();
  lcd.print("RAINDROP :");
  lcd.print(raindrop);
  delay(1500);
  sensors_event_t event1;
  sensors_event_t event2;

  accel1.getEvent(&event1);
  accel2.getEvent(&event2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MOUNTAIN 1:");
  lcd.setCursor(0, 1);
  lcd.print(event1.acceleration.x);
  lcd.setCursor(8, 1);
  lcd.print(event1.acceleration.y);
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MOUNTAIN 2:");
  lcd.setCursor(0, 1);
  lcd.print(event2.acceleration.x);
  lcd.setCursor(8, 1);
  lcd.print(event2.acceleration.y);
  delay(1500);
  if (raindrop == 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("HEAVY RAINFALL");
    // Siren-style flashing and buzzing
    for (int i = 0; i < 20; i++) {  // Repeat the pattern 5 times
      digitalWrite(led, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(150);
      digitalWrite(led, LOW);
      digitalWrite(buzzer, LOW);
      delay(150);
    }
    msg = "FULL RAINING......,";
    SendMessage();
  } else if (event1.acceleration.x > 7 || event1.acceleration.x < -7 || event1.acceleration.y > 7 || event1.acceleration.y < -7) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("LANDSLIDE IN ");
      lcd.setCursor(0, 1);
      lcd.print("AREA 1");
      // Siren-style flashing and buzzing
      for (int i = 0; i < 20; i++) {  // Repeat the pattern 5 times
        digitalWrite(led, HIGH);
        digitalWrite(buzzer, HIGH);
        delay(150);
        digitalWrite(led, LOW);
        digitalWrite(buzzer, LOW);
        delay(150);
      }
      msg = "LANDSLIDE IN AREA 1......,";
      SendMessage();
    }
  else if (event2.acceleration.x > 7 || event2.acceleration.x < -7 || event2.acceleration.y > 7 || event2.acceleration.x < -7) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LANDSLIDE IN");
    lcd.setCursor(0, 1);
    lcd.print("AREA 2");
    // Siren-style flashing and buzzing
    for (int i = 0; i < 20; i++) {  // Repeat the pattern 5 times
      digitalWrite(led, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(150);

      digitalWrite(led, LOW);
      digitalWrite(buzzer, LOW);
      delay(150);
    }
    msg = "LANDSLIDE IN AREA 2......,";
    SendMessage();
  }
  else {
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
  }
  delay(1000);
}
void SendMessage() {
  Serial.println("AT");  //test check communication with gsm module
  delay(500);
  Serial.println("ATE0");  //ATE0: Switch echo off. ATE1: Switch echo on.
  delay(500);
  Serial.println("AT+CMGF=1");  //set sms text mode
  delay(500);
  Serial.println("AT+CMGS=\"+919632634474\"\r");  //send specfic number
  delay(500);
  Serial.println("ALERT...!");
  Serial.println(msg);
  delay(500);
  Serial.write(26);
  delay(1000);
  Serial.println("Message sent..");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MSG SENT..!:)");
  delay(2000);
}