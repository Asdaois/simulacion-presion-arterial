#include "Arduino.h"
#include "pins_arduino.h"
#include <Wire.h>
#include "datos.h"
#include "pulsador_con_rebote.h"
#include "valor_simulacion.h"

#define BPM_MIN 40
#define BPM_MAX 120

int indice_actual = 0;
unsigned long milisegundos_desde_se_mostro_onda = 0;
unsigned long milisegundos_desde_se_mostro_datos = 0;

#include <Adafruit_MCP4725.h>
Adafruit_MCP4725 dac;

#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

ValorSimulacion bpm(60, BPM_MIN, BPM_MAX, 0, 1);

void setup() {
  dac.begin(0x60);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Simulacion");
  lcd.setCursor(0, 1);
  lcd.print("Presion Arterial");
  
  bpm.setup();
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
}

