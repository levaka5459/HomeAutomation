#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define tempKotel D3
#define tempTrapezaria D4
#define tempTavan D10
#define tempDani D9

#define COLOR_RED    "#ff0000"
#define COLOR_YELLOW "#ffff00"
#define COLOR_GREEN  "#00ff00"

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
char auth[] = "99cfca9cc8df49f881f7363fc4e0a109";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Xiaomi_EFB5";
char pass[] = "1234567890";

// Select your pin with physical button
const int garageLED1 = D1;
const int garageLED2 = D2;

WidgetLED LED1(V0);
const int Kotel = D7;
const int garage = D6;
SimpleTimer timer;

// V3 LED Widget represents the physical button state
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
  Blynk.virtualWrite(V1, k);
  Blynk.virtualWrite(V2, t);
  Blynk.virtualWrite(V3, tv);
  Blynk.virtualWrite(V4, d);
  if (digitalRead(garageLED1) == HIGH && digitalRead(garageLED2) == HIGH) {
    LED1.on();
    LED1.setColor(COLOR_RED);
    }
  else if (digitalRead(garageLED1) == HIGH && digitalRead(garageLED2) == LOW) {
    LED1.on();
    LED1.setColor(COLOR_YELLOW);
    }
  else if (digitalRead(garageLED1) == LOW && digitalRead(garageLED2) == LOW) {
    LED1.on();
    LED1.setColor(COLOR_GREEN);
    }
}

void setup()
{
  pinMode(Kotel, OUTPUT);
  pinMode(garage, OUTPUT);
  digitalWrite(Kotel, HIGH);
  digitalWrite(garage, HIGH);
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

  // Setup physical button pin (active low)
  pinMode(garageLED1, INPUT_PULLUP);
  pinMode(garageLED2, INPUT_PULLUP);

  timer.setInterval(500L, buttonLedWidget);
}

void loop()
{
  Blynk.run();
  timer.run();
}

