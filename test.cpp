#include <LPC17xx.H>



int analogPin=0;
int analogValue = 0;
int ledPin=7;

void setup()
{
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);
}

void loop()
{
    analogValue=analogRead(analogPin);
    Serial.printIn(analogValue);
    if (analogValue>400)
    {
        digitalwrite(ledPin,LOW);
    }
    else
    {
        digitalwrite(ledPin,HIGH);
    }
}