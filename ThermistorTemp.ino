#include <math.h> 

#define ThermistorPIN 1                // Analog Pin 0
int limit = 25; //Define limite da temperatura para disparar evento

int ledPin = 13;

float vcc = 4.91;                       // only used for display purposes, if used set to the measured Vcc.

float pad = 9850;                       // balance/pad resistor value, set this to the measured resistance of your pad resistor

float thermr = 10000;                   // thermistor nominal resistance

 

float Thermistor(int RawADC) {

  long Resistance; 

  float Temp;  // Dual-Purpose variable to save space.

  Resistance=((1024 * pad / RawADC) - pad);

  Temp = log(Resistance); // Saving the Log(resistance) so not to calculate  it 4 times later

  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));

  Temp = Temp - 273.15;  // Convert Kelvin to Celsius

  return Temp;           // Return the Temperature

}



void setup() {

  Serial.begin(9600);   

  pinMode(ledPin, OUTPUT);

}



void loop() {

  float temp;

  temp=Thermistor(analogRead(ThermistorPIN));       // read ADC and  convert it to Celsius

  Serial.print("Celsius: ");

  Serial.print(temp,1);                            // Mostra a temperatura em °C

  Serial.println("");

if (temp >= limit){

    digitalWrite(ledPin,HIGH);  //acende o led indicando que a temperatura ultrapassou o limite estabelecido 

     Serial.println("Passou de 25°C");  

     delay(5000);

  } else {

    digitalWrite(ledPin,LOW);  //apaga o led caso a temperatura esteja abaixo do estabelecido

    Serial.println("Abaixo de 25°C");  

    delay(5000);

  }  

}
