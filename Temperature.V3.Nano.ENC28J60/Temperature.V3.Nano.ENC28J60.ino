#include <UIPEthernet.h>
#include <BlynkSimpleUIPEthernet.h>
#include <SimpleTimer.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define tempKotel 2
#define tempTrapezaria 3
#define tempTavan 4
#define tempDani 5

OneWire kotel(tempKotel);
OneWire trapezaria(tempTrapezaria);
OneWire tavan(tempTavan);
OneWire dani(tempDani);

DallasTemperature kotelS(&kotel);
DallasTemperature trapezariaS(&trapezaria);
DallasTemperature tavanS(&tavan);
DallasTemperature daniS(&dani);

char auth[] = "43f1954afcb84059b17a87bd8becbf14";

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
  // Debug console
  kotelS.begin();
  trapezariaS.begin();
  tavanS.begin();
  daniS.begin();
  Blynk.begin(auth);
  
  timer.setInterval(500L, timer1);
}

void loop()
{
  Blynk.run();
  timer.run();
}
