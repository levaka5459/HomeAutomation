#include <UIPEthernet.h>
#include <BlynkSimpleUIPEthernet.h>
#include <SimpleTimer.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define tempKotel 1
#define tempTrapezaria 2
#define tempTavan 3
#define tempDani 4

OneWire kotel(tempKotel);
OneWire trapezaria(tempTrapezaria);
OneWire tavan(tempTavan);
OneWire dani(tempDani);

DallasTemperature kotelS(&kotel);
DallasTemperature trapezariaS(&trapezaria);
DallasTemperature tavanS(&tavan);
DallasTemperature daniS(&dani);

char auth[] = "91f5ebac31464b8e964a09a98977c82a";

SimpleTimer timer;

void timer1()
{
  kotelS.requestTemperatures();
  float k = kotelS.getTempCByIndex(0);
Blynk.virtualWrite(V0, k);

}

void timer2()
{
  trapezariaS.requestTemperatures();
  float t = trapezariaS.getTempCByIndex(0);
Blynk.virtualWrite(V1, t);
}

void timer3()
{
  tavanS.requestTemperatures();
  float tv = tavanS.getTempCByIndex(0);
Blynk.virtualWrite(V2, tv);
}

void timer4()
{
  daniS.requestTemperatures();
  float d = daniS.getTempCByIndex(0);
Blynk.virtualWrite(V3, d);
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
  timer.setInterval(1000L, timer2);
  timer.setInterval(1500L, timer3);
  timer.setInterval(2000L, timer4);
}

void loop()
{
  Blynk.run();
  timer.run();
}
