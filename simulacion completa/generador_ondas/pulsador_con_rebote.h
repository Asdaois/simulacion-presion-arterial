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
  bool modo_continuo = false;
  
  bool estaRebotando() {
    return (millis() - ultimo_rebote) < ANTIREBOTE_TIEMPO; 
  }

  bool entraraModoContinuo(bool valor_actual) {
    return (millis() - ultimo_rebote) > 500 && valor_actual == false;
  }

public:
  
  PulsadorConRebote() {}
  PulsadorConRebote(uint8_t pin)
  {
    this->pin = pin;
  }

  void set_pin(uint8_t pin) {
    this->pin = pin;
  } 
  void loop()
  {
    bool valor_actual = digitalRead(pin);
    if (estaRebotando()) {
      return;
    }

    if (entraraModoContinuo(valor_actual)){
      modo_continuo = true;
    }

    bool pulsador_es_presionado = valor_actual == false && valor_actual != ultimo_valor;
    if (pulsador_es_presionado)
    {
      accion_pendiente = true;
      ultimo_rebote = millis();
      modo_continuo = false;
    }

    if (modo_continuo && valor_actual == false) {
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

  bool esta_en_modo_continuo() {
    return this->modo_continuo;
  }
};

#endif