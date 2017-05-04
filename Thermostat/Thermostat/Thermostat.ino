/*
 * Author@Jun-Shuo Ng
 * Made with reference to Seeed Studio Serial LCD Guide 
 */
// Grove - Button connect to D3
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

byte heart[8] = {           //initiate heart character
    0b00000,
    0b01010,
    0b11111,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000
};

const int pinTemp = A0;      // pin of temperature sensor
const int pinButton = 3;     // pin of button define here

float tempC;                 //get reading to be converted to Celsius
float tempF;                 //get reading to be converted to Fahrenheit
int B=3975;                  // B value of the thermistor
float resistance;

void setup()
{
    Serial.begin(9600);                         //begin serial monitoring
    lcd.begin(16, 2);                           //begin LCD
    pinMode(pinButton, INPUT);                  // set button INPUT
    lcd.createChar(0, heart);                   // create heart character
}

void loop()
{
    if(digitalRead(pinButton))
    {
      int val = analogRead(pinTemp);                                        // get analog value
      resistance=(float)(1023-val)*10000/val;                               // get resistance
      tempF = (1/(log(resistance/10000)/B+1/298.15)-273.15)*9/5+32;      // calc temperature
      Serial.println(tempF);
      lcd.print(tempF);                                                     //prints temperature on LCD in Fahrenheit
      lcd.setCursor(0,1);
      lcd.print("Fahrenheit");
    }
    else
    {
      int val = analogRead(pinTemp);                               // get analog value
      resistance=(float)(1023-val)*10000/val;                      // get resistance
      tempC = 1/(log(resistance/10000)/B+1/298.15)-273.15;         // calc temperature
      Serial.println(tempC);
      lcd.print(tempC);                                            //prints temperature on LCD in Celsius
      lcd.setCursor(0,1);
      lcd.print("Celsius");
    }
    delay(1000);                                                  // delay 1s
    lcd.clear();                                                  //shows only one instance of reading
}




