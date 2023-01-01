

#include "DHT.h"
#define DHT11PIN 3

#include <SPI.h>
#include <LoRa.h>

#define ss 15
#define rst 16
#define dio0 2

int pos;
String msg1,msg2;

DHT dht(DHT11PIN, DHT11);
void setup()
{
  
  Serial.begin(115200);
/* Start the DHT11 Sensor */
  dht.begin();


  while (!Serial);
  Serial.println("LoRa Sender");
  LoRa.setPins(ss, rst, dio0);
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }


}

void loop()
{
  float humi = dht.readHumidity();
  float temp = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("ºC ");
  Serial.print("Humidity: ");
  Serial.println(humi);
  delay(1000);

  msg1 = String(temp) +"/";
  msg2 = String(humi) +"/";  

  Serial.print("Sending packet: ");
  // send packet to Lora
  LoRa.beginPacket();
  LoRa.print(msg1); 
  LoRa.print(msg2); 
  LoRa.endPacket(); 
  delay(3000);
}