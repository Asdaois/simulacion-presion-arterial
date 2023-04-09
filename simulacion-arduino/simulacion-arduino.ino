#include "Arduino.h"
#include "pins_arduino.h"
#include <Wire.h>
#include "datos.h"
#include "pulsador_con_rebote.h"
#include "valor_simulacion.h"

int indice_actual = 0;
unsigned long micros_ultimo_dato_mostrado = 0;
unsigned long milisegundos_desde_se_mostro_datos = 0;

#include <Adafruit_MCP4725.h>
Adafruit_MCP4725 dac;

#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

ValorSimulacion bpm(FRECUENCIA_CARDIACA_NORMAL, FRECUENCIA_CARDIACA_MINIMA, FRECUENCIA_CARDIACA_MAXIMA, 0, 1);
ValorSimulacion presion_minima(80, PRESION_DISTOLICA_MINIMA, PRESION_DISTOLICA_MAXIMA, 9, 8);
ValorSimulacion presion_maxima(120, PRESION_SISTOLICA_MINIMA, PRESION_SISTOLICA_MAXIMA, 11, 10);
unsigned long tiempo_cambio_datos  = DISTANCIA_ENTRE_DATOS_MICROS;
double ultimo_valor_bpm = FRECUENCIA_CARDIACA_NORMAL;

void setup() {
  dac.begin(0x60);

  lcd.begin(16, 2);

  bpm.setup();
  presion_minima.setup();
  presion_maxima.setup();
}

void loop() {
  if (ultimo_valor_bpm != bpm.obtener_valor()) {
    tiempo_cambio_datos = (FRECUENCIA_CARDIACA_NORMAL / (double)bpm.obtener_valor() ) * DISTANCIA_ENTRE_DATOS_MICROS;
    ultimo_valor_bpm = bpm.obtener_valor();
  }

  if ((micros() - micros_ultimo_dato_mostrado) > tiempo_cambio_datos) {
    mostrar_sennal_cardiaca();
    micros_ultimo_dato_mostrado = micros();
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
  auto valor_tabla_actual = valores_presion_base[indice_actual];
  auto valor_presion = (presion_maxima.obtener_valor() - presion_minima.obtener_valor()) * valor_tabla_actual + presion_minima.obtener_valor();
  auto valor_presion_normalizada = valor_presion / PRESION_MONITOR_MAXIMA;
  
  dac.setVoltage( valor_presion_normalizada * 4095, false);

  indice_actual++;
  if (indice_actual > numero_pasos - 1) {
    indice_actual = 0;
  }
}

void mostrar_frecuencia_cardiaca() {
  lcd.setCursor(0, 0);
  lcd.print("BPM:" + String(bpm.obtener_valor()));
  // lcd.print(String(micros_ultimo_dato_mostrado));
  // lcd.print(String(micros() - micros_ultimo_dato_mostrado)+ "<->" + String(tiempo_cambio_datos));
  lcd.setCursor(0, 1);
  lcd.print("MIN:" + String(presion_minima.obtener_valor()) + " MAX:" + String(presion_maxima.obtener_valor()));
  // lcd.print("BPM:" + String(bpm.obtener_valor()));
}

