#define BLYNK_TEMPLATE_ID "-gPGo3v"
#define BLYNK_DEVICE_NAME "Mech Agri"
#define BLYNK_AUTH_TOKEN "-c36Hf2HO2x0"                  

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define RXD2 16
#define TXD2 17

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "wifi";
char pass[] = "password";

BlynkTimer timer;

int cloudTemp = V0;
int cloudHumid = V1;
int cloudSensor1 = V2;
int cloudSensor2 = V3;
int cloudSensor3 = V4;

int localTemp;
int localHumid;
int localSensor1;
int localSensor2;
int localSensor3;

BLYNK_CONNECTED()
{
  Serial.print("connected");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(cloudTemp, localTemp);
  Blynk.virtualWrite(cloudHumid, localHumid);
  Blynk.virtualWrite(cloudSensor1, localSensor1);
  Blynk.virtualWrite(cloudSensor2, localSensor2);
  Blynk.virtualWrite(cloudSensor3, localSensor3);
}

void setup()
{
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Serial.println(Serial2.readString());
  localTemp = Serial2.readString().toInt();
  localHumid = Serial2.readString().toInt();
  localSensor1 = Serial2.readString().toInt();
  localSensor2 = Serial2.readString().toInt();
  localSensor3 = Serial2.readString().toInt();
  
  Blynk.run();
  timer.run();
}
