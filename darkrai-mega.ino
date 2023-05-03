#include <ArduinoJson.h>
#include <SPI.h>
#include <MFRC522.h>
#include "Motor.h"

// ========== RFID ==========
#define SS_PIN 53
#define RST_PIN 5

MFRC522 rfid(SS_PIN, RST_PIN);

// ========== RELAY ==========
#define RELAY_PIN 7

// ========== Motores ==========
Motor motor1(22, 23, 24, 25);
Motor motor2(26, 27, 28, 29);
Motor motor3(30, 31, 32 , 33);

const int PASOS_PASTILLA = 1000;
const int TOTAL_PASTILLAS = 10;

void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);

  // Setup RFID + Relay
  SPI.begin();
  rfid.PCD_Init();
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  
  // Motores setup
  motor1.init();
  motor2.init();
  motor3.init();

  Serial.println("init");
}

void loop() {
  handleEspSerial();
  handleRFID();
}


void handleEspSerial() {
  // Lectura de datos del Serial3
  while (Serial3.available()) {
    String msg = Serial3.readString();

    if (msg == "." || msg == "..") {
      Serial.print(msg);
    } else {
      Serial.println(msg);
    }

    if (msg.charAt(0) == '{') handleAction(msg);
  }
}

void handleAction(String raw) {
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, raw);

  String action = doc["action"];
  int motor = doc["motor"];
  int cantidad = doc["cantidad"];
  int PASOS = doc["PASOS"];
  int pasos = cantidad * PASOS_PASTILLA;
  
  Serial.println(motor);
  Serial.println(cantidad);
  Serial.println(pasos);
  Serial.println(PASOS);

  if(contains(action, "ADELANTE")){
    if(motor == 1) motor1.avanzar(PASOS);
    else if(motor == 2) motor2.avanzar(PASOS);
    else if(motor == 3) motor3.avanzar(PASOS);
  }

  if(contains(action, "ATRAS")){
    if(motor == 1) motor1.retroceder(PASOS);
    else if(motor == 2) motor2.retroceder(PASOS);
    else if(motor == 3) motor3.retroceder(PASOS);
  }

}

void handleRFID() {
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    Serial.print("Tarjeta detectada: ");
    for (byte i = 0; i < rfid.uid.size; i++) {
      Serial.print(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
      Serial.print(rfid.uid.uidByte[i], HEX);
    }

    Serial.println();
    if (rfid.uid.uidByte[0] == 0x32 && rfid.uid.uidByte[1] == 0xA5 && rfid.uid.uidByte[2] == 0x0B && rfid.uid.uidByte[3] == 0x4C) {
      digitalWrite(RELAY_PIN, LOW);
      delay(1000);
      digitalWrite(RELAY_PIN, HIGH);
    }
  }
}

bool contains(String txt, String search){
  if(txt.indexOf(search) > 0){
    return true;
  }else {
    return false;
  }

}