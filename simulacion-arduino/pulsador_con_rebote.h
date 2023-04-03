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

public:
  PulsadorConRebote(uint8_t pin)
  {
    this->pin = pin;
  }

  void loop()
  {
    bool valor_actual = digitalRead(pin);

    if (valor_actual == false)
    {
      accion_pendiente = true;
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