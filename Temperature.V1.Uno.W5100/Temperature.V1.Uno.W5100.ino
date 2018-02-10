//#define BLYNK_PRINT Serial

#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>
#include <SimpleTimer.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define tempKotel 2
#define tempTrapezaria 3
#define tempTavan 6
#define tempDani 5

char auth[] = "45c9713ba05642288e10d3c22cfcd5d4";

#define W5100_CS  10
#define SDCARD_CS 4

OneWire kotel(tempKotel);
OneWire trapezaria(tempTrapezaria);
OneWire tavan(tempTavan);
OneWire dani(tempDani);

DallasTemperature kotelS(&kotel);
DallasTemperature trapezariaS(&trapezaria);
DallasTemperature tavanS(&tavan);
DallasTemperature daniS(&dani);

SimpleTimer timer;

void timer1() 
{
  kotelS.requestTemperatures();
  float k = kotelS.getTempCByIndex(0);
  trapezariaS.requestTemperatures();
  float t = trapezariaS.getTempCByIndex(0);
  tavanS.requestTemperatures();
  float tv = tavanS.getTempCByIndex(0);
  daniS.requestTemperatures();
  float d = daniS.getTempCByIndex(0);
  if (k > -50 || t > -50 || tv > -50 || d > -50) 
  {
    Blynk.virtualWrite(V0, k);
    Blynk.virtualWrite(V1, t);
    Blynk.virtualWrite(V2, tv);
    Blynk.virtualWrite(V3, d);
  }
}

void setup()
{
  //Serial.begin(9600);

  pinMode(SDCARD_CS, OUTPUT);
  digitalWrite(SDCARD_CS, HIGH);
  Blynk.begin(auth);

  pinMode(7, OUTPUT);

  kotelS.begin();
  trapezariaS.begin();
  tavanS.begin();
  daniS.begin();

  timer.setInterval(1000L, timer1);
}

void loop()
{
  Blynk.run();
  timer.run();
}
