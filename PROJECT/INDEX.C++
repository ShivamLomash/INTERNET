#define BLYNK_TEMPLATE_ID "TMPL3UzHtTwJy"
#define BLYNK_TEMPLATE_NAME "soil moisture sensor"
#define BLYNK_AUTH_TOKEN "najdFBEV_oYqSDwSJsetJ7QQTbNlbjVg"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "Airtel_hello123";
char pass[] = "sanjay@123";

#define SOIL_PIN A0
#define RED_LED D1
#define BUZZER D5

BlynkTimer timer;

void sendData() {
  int moistureValue = analogRead(SOIL_PIN);

  Serial.print("Moisture: ");
  Serial.println(moistureValue);

  Blynk.virtualWrite(V0, moistureValue);

  // 🔴 VERY DRY (>800)
  if (moistureValue > 800) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, HIGH);
    Blynk.virtualWrite(V1, "VERY DRY 🔴");
  }

  // 🟡 DRY (700–800)
  else if (moistureValue > 700) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, HIGH);
    Blynk.virtualWrite(V1, "DRY 🟡");
  }

  // 🟢 WET (<700)
  else {
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER, LOW);
    Blynk.virtualWrite(V1, "WET 🟢");
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(BUZZER, LOW);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(500L, sendData);
}

void loop() {
  Blynk.run();
  timer.run();
}