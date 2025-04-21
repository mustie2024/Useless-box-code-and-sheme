#include <ESP32Servo.h>

Servo armservo;

const int switchPin = 4;
const int servoPin = 13;

const int down = 160;
const int up = 10;

bool switchTriggered = false;
unsigned long triggerTime = 0;
unsigned long maxWaitTime = 6000;  // Maksimalno ignorisanje: 6 sekundi

void setup() {
  Serial.begin(115200);
  pinMode(switchPin, INPUT_PULLUP);
  armservo.attach(servoPin);
  armservo.write(down);
  delay(500);
}

void loop() {
  int state = digitalRead(switchPin);

  if (state == LOW && !switchTriggered) {
    switchTriggered = true;
    triggerTime = millis();

    int randAction = random(1, 6);
    Serial.print("Zločesta Akcija: "); Serial.println(randAction);

    switch (randAction) {
      case 1: pokretNormalan(); break;
      case 2: trollNapola(); break;
      case 3: gledanje(); break;
      case 4: ignorisi(); break;
      case 5: napad(); break;
      case 6: premisljanje(); break; // Novi slučaj
    }
  }

  // Ako se slučajno zaglavi, isključi prekidač nakon maksimalnog vremena
  if (switchTriggered && millis() - triggerTime > maxWaitTime) {
    Serial.println("Vrijeme isteklo — prekidač se mora ugasiti!");
    pokretNormalan();  // Osiguraj isključivanje
    switchTriggered = false;
  }

  // Reset kada se prekidač vrati u HIGH (nakon što ga servo ugasi)
  if (state == HIGH && switchTriggered) {
    switchTriggered = false;
  }

  delay(10);
}

// Normalno isključivanje
void pokretNormalan() {
  armservo.write(up);
  delay(600);
  armservo.write(down);
  delay(600);
}

// Izviri, ali ništa ne uradi
void trollNapola() {
  armservo.write(up + 40);
  delay(500);
  armservo.write(down);
  delay(500);
}

// Gledanje više puta
void gledanje() {
  for (int i = 0; i < 2; i++) {
    armservo.write(up + 30);
    delay(300);
    armservo.write(down);
    delay(300);
  }
  armservo.write(up);
  delay(600);
  armservo.write(down);
  delay(600);
}

// Ignorisanje sa vremenskim ograničenjem
void ignorisi() {
  int waitTime = random(2000, 5000); // 2 do 5 sekundi
  Serial.print("Ignorišem te na "); Serial.print(waitTime); Serial.println("ms");
  delay(waitTime);

  armservo.write(up);
  delay(600);
  armservo.write(down);
  delay(600);
}

// Brzi napadi
void napad() {
  for (int i = 0; i < 3; i++) {
    armservo.write(up + 20);
    delay(200);
    armservo.write(down);
    delay(200);
  }
  armservo.write(up);
  delay(600);
  armservo.write(down);
  delay(600);
}

// Novi slučaj: "Premišljanje" – servo se pomiče gore-dole, pa stane i razmišlja.
void premisljanje() {
  Serial.println("Premišlja se... 🤔");

  for (int i = 0; i < 3; i++) {
    armservo.write(up);
    delay(500);
    armservo.write(down);
    delay(500);

    Serial.print("Hoće li se vratiti?"); delay(1000);  // Dramska pauza
  }

  // Na kraju, mora se vratiti
  armservo.write(up);
  delay(600);
  armservo.write(down);
  delay(600);
}


