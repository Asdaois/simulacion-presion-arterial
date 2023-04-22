#include <stdint.h>
#include "pulsador_con_rebote.h"

#ifndef VALOR_SIMULACION
#define VALOR_SIMULACION

class ValorSimulacion {
  private:
    uint8_t valor_minimo;
    uint8_t valor_maximo;
    uint8_t valor;
    PulsadorConRebote pulsador_subida;
    PulsadorConRebote pulsador_bajada;
  public:
    ValorSimulacion(uint8_t valor_inicial, uint8_t valor_minimo, uint8_t valor_maximo, uint8_t pin_subida, uint8_t pin_bajada ) {
      pulsador_subida.set_pin(pin_subida);
      pulsador_bajada.set_pin(pin_bajada);
      this->valor_minimo = valor_minimo;
      this->valor_maximo = valor_maximo;
      this->valor = valor_inicial;
    }

    void setup() {
      pulsador_subida.setup();
      pulsador_bajada.setup();
    }

    void loop() {
      pulsador_subida.loop();
      pulsador_bajada.loop();
      
      if (pulsador_subida.realizara_accion()) {

        if (pulsador_subida.esta_en_modo_continuo()) {
          this->valor += 3;
        } else {
          this->valor += 1;
        }

        if (valor >= valor_maximo) {
          valor = valor_maximo;
        }
      }

      if (pulsador_bajada.realizara_accion()) {
        
        if (pulsador_bajada.esta_en_modo_continuo()) {
          this->valor -= 3;      
        } else {
          this->valor -= 1;
        }

        if (valor <= valor_minimo) {
          valor = valor_minimo;
        }
      }
    }

    uint8_t obtener_valor() {
      return this->valor;
    }
};

#endif