#include "librerias.h"

#define temperatura_maxima 45
#define temperatura_minima 25
#define spo2_maxima 100
#define spo2_minima 0

ValorRestringido temperatura(30, temperatura_minima, temperatura_maxima);
ValorRestringido spo2(85, spo2_minima, spo2_maxima);

void set_temperatura(uint valor) {
  temperatura.set_valor(valor);
  pantalla_temperatura_spo2_mostrar();
}

void set_spo2(uint valor) {
  spo2.set_valor(valor);
  pantalla_temperatura_spo2_mostrar();
}


void pantalla_temperatura_spo2_mostrar() {
  pantalla_actual = PantallaActual::TemperaturaYSpO2;
  generar_onda_temperatura();
  generar_onda_spo2();
  pantalla_mostrar("Temperatura",
                   "Valor: " + temperatura.obtenerS(),
                   "SPO2",
                   "Valor: " + spo2.obtenerS());
}

void temperatura_aumentar() {
  temperatura.aumentar(1);
  pantalla_temperatura_spo2_mostrar();
}

void temperatura_disminuir() {
  temperatura.disminuir(1);
  pantalla_temperatura_spo2_mostrar();
}

void generar_onda_temperatura() {
  auto valor = ((double)temperatura.get_valor() / (double)temperatura_maxima) * 4095;
  dac_temperatura((uint)valor);
}

void spo2_aumentar() {
  spo2.aumentar(1);
  pantalla_temperatura_spo2_mostrar();
}

void spo2_disminuir() {
  spo2.disminuir(1);
  pantalla_temperatura_spo2_mostrar();
}

void generar_onda_spo2() {
  auto valor = ((double)spo2.get_valor() / (double)spo2_maxima) * 4095;
  dac_spo2((uint)valor);
}
