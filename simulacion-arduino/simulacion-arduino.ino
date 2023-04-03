#include <Wire.h>

#include <Adafruit_MCP4725.h>


#include "datos.h"
#define PIN_OUTPUT 9

int indice_actual = 0;
const int milis_interrupcion = 8;
int actual_milisegundos_desde_ultimo_ciclo = 0;

Adafruit_MCP4725 dac;

void setup() {
  dac.begin(0x60);
}

void loop() {
  if (millis() - actual_milisegundos_desde_ultimo_ciclo > 8) {
    mostrar_sennal_cardiaca();
    actual_milisegundos_desde_ultimo_ciclo = millis();
  }
}

void mostrar_sennal_cardiaca() {
  dac.setVoltage( valores_presion_base[indice_actual] * 4095, false);
  indice_actual++;
  if (indice_actual > numero_pasos - 1) {
    indice_actual = 0;
  }
}


