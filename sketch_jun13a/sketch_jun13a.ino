#include <dummy.h>

#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
const int LM35 = A0;
// — — — — — — Wifi bilgileri girilecek— — — — -//
char ssid[] = "Deniz YURT"; //SSID
char pass[] = "deniz1234"; // Sifre
// — — — — — — — — — — — — — — — — — — — — — -//

WiFiClient client;

unsigned long myChannelNumber = 1766485; // Channel ID buraya
const int FieldNumber = 1;
const char * myWriteAPIKey = "MMJTPUF4QUWYLGSS"; // Thingspeak API kodumuz buraya

void setup()
{
Serial.begin(115200);
WiFi.mode(WIFI_STA);
ThingSpeak.begin(client);
}
void loop()
{
if (WiFi.status() != WL_CONNECTED)
{
Serial.print("Attempting to connect to SSID: ");
Serial.println(ssid);
while (WiFi.status() != WL_CONNECTED)
{
WiFi.begin(ssid, pass);
Serial.print(".");
delay(5000);
}
Serial.println("\nConnected.");
}
int ADC;
float temp;
ADC = analogRead(LM35); /* Read Temperature */
temp = (ADC/1024.0)*3300; /* Convert adc value to equivalent voltage */
temp = (temp / 10); /* LM35 gives output of 10mv/°C */
Serial.print("Temperature = ");
Serial.print(temp);
Serial.println(" *C");
delay(1000);
ThingSpeak.writeField(myChannelNumber, FieldNumber, temp, myWriteAPIKey);
delay(1000);
}
