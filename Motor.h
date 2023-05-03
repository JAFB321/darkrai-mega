// Motor.h
#ifndef Motor_h
#define Motor_h

#include <Arduino.h>

class Motor {
  private:
    int pin1;
    int pin2;
    int pin3;
    int pin4;
    int total_pasos;
    int pasos_vuelta;
    int velocidad;
    int paso;
    
    void setOutput();
    int pasoSiguiente();
    int pasoAnterior();

  public:
    Motor(int pin1, int pin2, int pin3, int pin4);
    void init();
    void avanzar(int pasos);
    void retroceder(int pasos);
};

#endif
