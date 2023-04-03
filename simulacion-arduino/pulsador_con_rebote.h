#include "Arduino.h"
#include <stdint.h>
#ifndef PULSADOR_CON_REBOTE
#define PULSADOR_CON_REBOTE

#define ANTIREBOTE_TIEMPO 50

class PulsadorConRebote
{
private:
  uint8_t pin;
  bool accion_pendiente = false;
  bool ultimo_valor = true;
  unsigned long ultimo_rebote = 0;
  
  bool estaRebotando() {
    return (millis() - ultimo_rebote) < ANTIREBOTE_TIEMPO; 
  }

public:
  PulsadorConRebote(uint8_t pin)
  {
    this->pin = pin;
  }

  void loop()
  {
    if (estaRebotando()) {
      return;
    }

    bool valor_actual = digitalRead(pin);

    if (valor_actual == false && valor_actual != ultimo_valor)
    {
      accion_pendiente = true;
      ultimo_rebote = millis();
    }

    ultimo_valor = valor_actual;
  }

  bool realizara_accion()
  {
    if (accion_pendiente == false)
    {
      return false;
    }

    this->accion_pendiente = false;

    return true;
  }

  void setup()
  {
    pinMode(pin, INPUT_PULLUP);
  }
};

#endif