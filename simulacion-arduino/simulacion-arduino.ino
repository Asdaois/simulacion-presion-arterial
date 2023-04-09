#include "Arduino.h"
#include "pins_arduino.h"
#include <Wire.h>
#include "datos.h"
#include "pulsador_con_rebote.h"
#include "valor_simulacion.h"

int indice_actual = 0;
unsigned long milisegundos_desde_se_mostro_onda = 0;
unsigned long milisegundos_desde_se_mostro_datos = 0;

#include <Adafruit_MCP4725.h>
Adafruit_MCP4725 dac;

#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

ValorSimulacion bpm(60, FRECUENCIA_CARDIACA_MINIMA, FRECUENCIA_CARDIACA_MAXIMA, 0, 1);
ValorSimulacion presion_minima(80, PRESION_DISTOLICA_MINIMA, PRESION_DISTOLICA_MAXIMA, 9, 8);
ValorSimulacion presion_maxima(120, PRESION_SISTOLICA_MINIMA, PRESION_SISTOLICA_MAXIMA, 11, 10);

void setup() {
  dac.begin(0x60);

  lcd.begin(16, 2);

  bpm.setup();
  presion_minima.setup();
  presion_maxima.setup();
}

void loop() {
  if ((millis() - milisegundos_desde_se_mostro_onda) > 8) {
    mostrar_sennal_cardiaca();
    milisegundos_desde_se_mostro_onda = millis();
  }

  if ((millis() - milisegundos_desde_se_mostro_datos) > 50) {
    mostrar_frecuencia_cardiaca();
    milisegundos_desde_se_mostro_datos = millis();
  }
 
  bpm.loop();
  presion_minima.loop();
  presion_maxima.loop();
}

void mostrar_sennal_cardiaca() {
  dac.setVoltage( valores_presion_base[indice_actual] * 4095, false);
  indice_actual++;
  if (indice_actual > numero_pasos - 1) {
    indice_actual = 0;
  }
}

void mostrar_frecuencia_cardiaca() {
  lcd.setCursor(0, 0);
  lcd.print("BPM:" + String(bpm.obtener_valor()));
  lcd.setCursor(0, 1);
  lcd.print("MIN:" + String(presion_minima.obtener_valor()) + " MAX:" + String(presion_maxima.obtener_valor()));
}

