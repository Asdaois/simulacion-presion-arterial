#include "ValorRestringido.h"

#define temperatura_maxima 45
#define temperatura_minima 25
#define spo2_maxima 100
#define spo2_minima 0

ValorRestringido temperatura(30, temperatura_minima, temperatura_maxima);
ValorRestringido spo2(85, spo2_minima, spo2_maxima);

void pantalla_temperatura_spo2_mostrar() {
  pantalla_actual = PantallaActual::TemperaturaYSO2;
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
  dac_temperatura(((double)temperatura.get_valor() / (double)temperatura_maxima) * 4095);
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
  dac_spo2(((double)spo2.get_valor() / (double)spo2_maxima) * 4095);
}
