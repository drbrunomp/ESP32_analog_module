#include <Arduino.h>

const int ReadPin = 2;
int       VdigPot = 0;
float     TensaoPot = 0,
          TensaoDig = 0;

void setup() 
{
  Serial.begin(9600);
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);
  analogSetWidth(12);
}

float signalConv(float ArgAnalog)
{  
  TensaoDig = ArgAnalog * 0.80586e-3;
  return(TensaoDig);
}

void readAnalog()
{
  VdigPot = analogRead(ReadPin); 
  TensaoPot = signalConv(VdigPot);
}

void printSerial()
{
  if(Serial.availableForWrite() != NULL)
  {
    Serial.printf("Valor Digital: %d \n", VdigPot);
    Serial.printf("Tensão Elétrica: %.2f V \n",TensaoPot);
    delay(1000);
  }
}
void loop() 
{
  readAnalog();
  printSerial();   
}
