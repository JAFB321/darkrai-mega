#include "Motor.h"
#include <Arduino.h>

int bobinas[8] = { B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001 };

Motor::Motor(int _pin1, int _pin2, int _pin3, int _pin4) {
  pin1 = _pin1;
  pin2 = _pin2;
  pin3 = _pin3;
  pin4 = _pin4;
  total_pasos = 4220;
  velocidad = 1200;
  pasos_vuelta = 8;
  paso = 0;
}

void Motor::init() {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);

  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
}

void Motor::avanzar(int pasos) {
  for (int i = 0; i < pasos; i++) {
    paso = pasoSiguiente();
    setOutput();
  }

  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
}

void Motor::retroceder(int pasos) {
  for (int i = 0; i < pasos; i++) {
    paso = pasoAnterior();
    setOutput();
  }

  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
}

void Motor::setOutput() {
  digitalWrite(pin1, bitRead(bobinas[paso], 0));
  digitalWrite(pin2, bitRead(bobinas[paso], 1));
  digitalWrite(pin3, bitRead(bobinas[paso], 2));
  digitalWrite(pin4, bitRead(bobinas[paso], 3));

  delayMicroseconds(velocidad);
}

int Motor::pasoSiguiente() {
  if(paso + 1 < pasos_vuelta) return paso + 1;
  else return 0;
}

int Motor::pasoAnterior() {
  if (paso - 1 >= 0) return paso - 1;
  else return pasos_vuelta - 1;
}


