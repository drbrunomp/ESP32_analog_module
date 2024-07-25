#include <Arduino.h>

const int ReadPin = 2,
          Valv1Pin = 18,
          Valv2Pin = 19,
          PumpPin = 21;
int       Valv1 = 0,
          Valv2 = 0,
          Pump = 0,
          VdigPot = 0;
float     TensaoPot = 0,
          TensaoDig = 0,
          LevelTankFunction = 0,
          LevelTank = 0;

void setup() 
{
  Serial.begin(9600);
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);
  analogSetWidth(12);
  pinMode(Valv1Pin, OUTPUT);
  pinMode(Valv2Pin, OUTPUT);
  pinMode(PumpPin, OUTPUT);
}

float signalConv(float ArgAnalog)
{  
  TensaoDig = ArgAnalog * 0.80586e-3;
  return(TensaoDig);
}

float levelConv(float ArgLevel)
{
  LevelTankFunction = ArgLevel / 0.00033;
  return(LevelTankFunction);
}

void resultFunctions()
{
  VdigPot = analogRead(ReadPin); 
  TensaoPot = signalConv(VdigPot);
  LevelTank = levelConv(TensaoPot);
}

void printSerial()
{
  if(Serial.availableForWrite() != NULL)
  {
    Serial.printf("Valor Digital: %d \n", VdigPot);
    Serial.printf("Tensão Elétrica: %.2f V \n",TensaoPot);
    Serial.printf("Nivel do Tanque: %.0f Litros \n",LevelTank);
    delay(1000);
  }
}

void controlLogic()
{
  if(LevelTank > (0.75 * 10000))
  {
    Valv1 = LOW;
    Valv2 = HIGH;
    Pump = LOW;
  }
  else if(LevelTank > (0.50 * 10000) && LevelTank <= (0.75 * 10000))
  {
    Valv1 = HIGH;
    Valv2 = HIGH;
    Pump = HIGH;
  }
  else
  {
    Valv1 = HIGH;
    Valv2 = LOW;
    Pump = HIGH;
  }
}

void driveOutputs()
{
  digitalWrite(Valv1Pin, Valv1);
  digitalWrite(Valv2Pin, Valv2);
  digitalWrite(PumpPin, Pump);
}

void loop() 
{
  resultFunctions();
  printSerial(); 
  controlLogic();  
  driveOutputs();
}