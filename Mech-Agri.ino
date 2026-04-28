#include "DHT.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHTPIN 2
#define DHTTYPE DHT22
#define screen_width 128
#define screen_height 32

Adafruit_SSD1306 display(screen_width, screen_height);
DHT dht(DHTPIN, DHTTYPE);

int moistureLevelInt1;
int moistureLevelInt2;
int moistureLevelInt3;

int relay1 = 3;
int relay2 = 4;
int relay3 = 5;
int relay4 = 6;

int sensorPin1 = A0;
int sensorPin2 = A1;
int sensorPin3 = A2;

int moistureLevelPercentage1;
int moistureLevelPercentage2;
int moistureLevelPercentage3;

int temp;
int humid; 

int dry = 574;
int wet = 294;

void setup()
{
  Serial.begin(9600);
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);

  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  pinMode(sensorPin3, INPUT);
}
void loop()
{
  moistureLevelInt1 = analogRead(A0);
  moistureLevelInt2 = analogRead(A1);
  moistureLevelInt3 = analogRead(A2);
  
  temp = dht.readTemperature();
  humid = dht.readHumidity();

  if (isnan(humid) || isnan(temp)) 
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Failed to read from DHT sensor!");
    display.display();
    
    return;
  }

  moistureLevelPercentage1 = map(moistureLevelInt1, dry, wet, 0, 100);
  moistureLevelPercentage2 = map(moistureLevelInt2, dry, wet, 0, 100);
  moistureLevelPercentage3 = map(moistureLevelInt3, dry, wet, 0, 100);

  Display();
  Serial.println(" ");
  Serial.println(temp);
  Serial.println(humid);
  Serial.println(moistureLevelPercentage1);
  Serial.println(moistureLevelPercentage2);
  Serial.println(moistureLevelPercentage3);
  
   // These are the if statements for the relay 1
  if (moistureLevelPercentage1 < 20)
  {
    digitalWrite(relay1, HIGH);
  }
  else
  {
    digitalWrite(relay1, LOW);
  }
  // These are the if statements for the relay 2
  if (moistureLevelPercentage2 < 20)
  {
    digitalWrite(relay2, HIGH);
  }
  else
  {
    digitalWrite(relay2, LOW);
  }
  // These are the if statements for the relay 3
  if (moistureLevelPercentage3 < 20)
  {
    digitalWrite(relay3, HIGH);
  }
  else
  {
    digitalWrite(relay3, LOW);
  }
  // These are if statements for the relay 4
  if (moistureLevelPercentage1 < 20 || moistureLevelPercentage2 < 20 || moistureLevelPercentage3 < 20)
  {
    digitalWrite(relay4, HIGH);
  }
  else
  {
    digitalWrite(relay4, LOW);
  }
  
  /*Serial.print("Temprature:");
  Serial.print(temp);
  Serial.println("°C");
  Serial.print("Humidity:");
  Serial.print(humid);
  Serial.println("%");
  Serial.print("Moisture level:");
  Serial.print(moistureLevelPercentage1);
  Serial.print(", ");
  Serial.print(moistureLevelPercentage2);
  Serial.print(", ");
  Serial.println(moistureLevelPercentage3);
  
  Serial.println("  ");*/
  delay(1000);
}
void Display()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Moisture:");
  display.print(moistureLevelPercentage1);
  display.print(", ");
  display.print(moistureLevelPercentage2);
  display.print(", ");
  display.println(moistureLevelPercentage3);
  display.setCursor(0, 10);
  display.print("Temprature:");
  display.println(temp);
  display.setCursor(0, 20);
  display.print("Humidity:");
  display.println(humid);
  display.display();
}
