 
// 			FILE: dht11.h
#include <dht11.h>
dht11 DHT11;
#define DHT11PIN 4
void setup()
{
 	Serial.begin(9600);
 	Serial.println("DHT11 TEST PROGRAM ");
 	Serial.print("LIBRARY VERSION: ");
 	Serial.println(DHT11LIB_VERSION);
 	Serial.println();
}
void loop()
{
 	Serial.println("\n");
 	int chk = DHT11.read(DHT11PIN);
 	Serial.print("Read sensor: ");
 	switch (chk)
 	{
 			case DHTLIB_OK:
 			Serial.println("OK");
 			Serial.print("Humidity (%): ");
 			Serial.println((float)DHT11.humidity, 2);
 	
 			Serial.print("Temperature (°C): ");
 			Serial.println((float)DHT11.temperature, 2);
 	
 			Serial.print("Temperature (°F): ");
 			Serial.println(Fahrenheit(DHT11.temperature), 2);
 	
 			Serial.print("Temperature (°K): ");
 			Serial.println(Kelvin(DHT11.temperature), 2);
 	
 			Serial.print("Dew PointFast (°C): ");
 			Serial.println(dewPointFast(DHT11.temperature, DHT11.humidity));
 			
 			break;
 			case DHTLIB_ERROR_CHECKSUM:
 			Serial.println("Checksum error");
 			break;
 			case DHTLIB_ERROR_TIMEOUT:
 			Serial.println("Time out error");
 			break;
 			default:
 			Serial.println("Unknown error");
 			break;
 	}
 	delay(2000);
}
//Celsius to Fahrenheit conversion
double Fahrenheit(double celsius)
{
 	return 1.8 * celsius + 32;
}
//Celsius to Kelvin conversion
double Kelvin(double celsius)
{
 	return celsius + 273.15;
}
// dewPoint function NOAA
// reference (1) : http://wahiduddin.net/calc/density_algorithms.htm
// reference (2) : http://www.colorado.edu/geography/weather_station/Geog_site/about.htm
double dewPointFast(double celsius, double humidity)
{
 	double a = 17.271;
 	double b = 237.7;
 	double temp = (a * celsius) / (b + celsius) + log(humidity*0.01);
 	double Td = (b * temp) / (a - temp);
 	return Td;
}

#ifndef dht11_h
#define dht11_h
#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#define DHT11LIB_VERSION "0.4.1"
#define DHTLIB_OK 							0
#define DHTLIB_ERROR_CHECKSUM -1
#define DHTLIB_ERROR_TIMEOUT 	-2
class dht11
{
public:
 			int read(int pin);
 	int humidity;
 	int temperature;
};
#endif
