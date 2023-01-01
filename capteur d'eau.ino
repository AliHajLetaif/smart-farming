int water;
int rainsense= 0; // analog sensor input pin 0
int buzzerout= 10; // digital output pin 10 - buzzer output
int countval= 0; // counter value starting from 0 and goes up by 1 every second

void setup() {
   pinMode(A1, INPUT);
   pinMode(buzzerout, OUTPUT);
   pinMode(rainsense, INPUT);
   Serial.begin(9600); // ouvre le port série
}

void loop() {
  //capteur niveau d eau 
   water = analogRead(A1);
   Serial.println(water);
 
   delay(1000); // attend une seconde

//capteur de pluie

     int rainSenseReading = analogRead(rainsense);
   Serial.println(rainSenseReading); // serial monitoring message 
   delay(250);// rain sensing value from 0 to 1023.
   // from heavy rain - no rain.
   if (countval >= 35){ 
      Serial.print("Heavy rain");
      digitalWrite(buzzerout, HIGH);  //raise an alert after x time
   }
   //raining for long duration rise buzzer sound
   // there is no rain then reset the counter value
   if (rainSenseReading <350){ 
      countval++; // increment count value
   }
   else if (rainSenseReading >350) { // if not raining
      digitalWrite(buzzerout, LOW); // turn off buzzer 
      countval = 0; // reset count to 0
   }
   delay(1000);
}