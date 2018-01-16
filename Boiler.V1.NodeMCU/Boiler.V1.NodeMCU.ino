#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//#define BLYNK_GREEN  "#00ff00"
//#define BLYNK_RED  "#ff0000"

#define tempKotel D3

OneWire kotel(tempKotel);

DallasTemperature kotelS(&kotel);

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
WidgetLED LED2(V1);
const int Kotel = D7;
const int garage = D6;
SimpleTimer timer;

// V3 LED Widget represents the physical button state
void buttonLedWidget()
{
  // Read button
  kotelS.requestTemperatures();
  float k = kotelS.getTempCByIndex(0);
  Blynk.virtualWrite(V2, k);
  if (digitalRead(garageLED1) == HIGH) {
    LED1.on();
    //LED1.setColor(BLYNK_GREEN);
  }
  else {
    LED1.off();
  }
  if (digitalRead(garageLED2) == HIGH) {
    LED2.on();
    //LED2.setColor(BLYNK_RED);
  }
  else {
    LED2.off();
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
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

  // Setup physical button pin (active low)
  pinMode(garageLED1, INPUT_PULLUP);
  pinMode(garageLED2, INPUT_PULLUP);

  timer.setInterval(1000L, buttonLedWidget);
}

void loop()
{
  Blynk.run();
  timer.run();
}

