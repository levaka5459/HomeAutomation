#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define tempKotel D1
#define tempTrapezaria D2
#define tempTavan D3
#define tempDani D4

OneWire kotel(tempKotel);
OneWire trapezaria(tempTrapezaria);
OneWire tavan(tempTavan);
OneWire dani(tempDani);

DallasTemperature kotelS(&kotel);
DallasTemperature trapezariaS(&trapezaria);
DallasTemperature tavanS(&tavan);
DallasTemperature daniS(&dani);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "91f5ebac31464b8e964a09a98977c82a";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Xiaomi_EFB5";
char pass[] = "1234567890";

SimpleTimer timer;

void buttonLedWidget()
{
  // Read button
  kotelS.requestTemperatures();
  trapezariaS.requestTemperatures();
  tavanS.requestTemperatures();
  daniS.requestTemperatures();
  float k = kotelS.getTempCByIndex(0);
  float t = trapezariaS.getTempCByIndex(0);
  float tv = tavanS.getTempCByIndex(0);
  float d = daniS.getTempCByIndex(0);
  Blynk.virtualWrite(V0, k);
  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V2, tv);
  Blynk.virtualWrite(V3, d);
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  kotelS.begin();
  trapezariaS.begin();
  tavanS.begin();
  daniS.begin();
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

  timer.setInterval(500L, buttonLedWidget);
}

void loop()
{
  Blynk.run();
  timer.run();
}

