#include "Arduino.h"
#include "pins_arduino.h"
#include <Wire.h>
#include "datos.h"

#define PRESION_MINIMA 40;
#define PRESION_MAXIMA 120;

int indice_actual = 0;
int milis_interrupcion = 8;
int actual_milisegundos_desde_ultimo_ciclo = 0;


#include <Adafruit_MCP4725.h>
Adafruit_MCP4725 dac;

#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
  dac.begin(0x60);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Simulacion");
  lcd.setCursor(0, 1);
  lcd.print("Presion Arterial");
  
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


