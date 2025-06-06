#include "librerias.h"

#define PRESION_DISTOLICA_MINIMA 40
#define PRESION_DISTOLICA_MAXIMA 160
#define PRESION_SISTOLICA_MINIMA 120
#define PRESION_SISTOLICA_MAXIMA 220

#define NUMERO_DATOS_PRESION 130;


int indice_actual = 0;
const float valores_presion_base[] PROGMEM = {
  0, 0.004309611, 0.011562908, 0.022145005, 0.03642549, 0.054741148, 0.077373676, 0.10452465,
  0.13628997, 0.17263258, 0.21336693, 0.2581447, 0.30645913, 0.3576594, 0.41098028, 0.46557996,
  0.52058, 0.57510304, 0.62830573, 0.6794079, 0.727719, 0.772659, 0.8137785, 0.85076016,
  0.8834239, 0.911715, 0.93568736, 0.9554836, 0.9713093, 0.98341006, 0.9920496, 0.9974943,
  1, 0.9990795, 0.99714094, 0.99220383, 0.9851842, 0.9762542, 0.96557367, 0.9532934,
  0.93956006, 0.92451984, 0.9083213, 0.8911149, 0.87305063, 0.85427475, 0.8349272, 0.81514144,
  0.7950472, 0.77477294, 0.75444657, 0.7341991, 0.71416444, 0.69447887, 0.67527956, 0.6567002,
  0.6388638, 0.6218763, 0.6058207, 0.5907527, 0.57670134, 0.5636676, 0.55162996, 0.5405471,
  0.53036535, 0.52102345, 0.51245606, 0.50459754, 0.49738058, 0.490736, 0.48459172, 0.4788711,
  0.4734958, 0.46838543, 0.46346283, 0.45865467, 0.4538946, 0.4491235, 0.44428632, 0.43933317,
  0.43421677, 0.42889306, 0.42332318, 0.41747487, 0.41132534, 0.40486154, 0.39807898, 0.39097694,
  0.3835551, 0.37581053, 0.36774018, 0.35934383, 0.3506312, 0.34162286, 0.3323516, 0.32286,
  0.3131951, 0.303402, 0.29352152, 0.28358522, 0.27361685, 0.2636342, 0.25364807, 0.24366567,
  0.23368979, 0.22372292, 0.21376781, 0.20382774, 0.19390646, 0.18400593, 0.1741272, 0.16427027,
  0.15443711, 0.1446305, 0.13485569, 0.12511769, 0.115422, 0.10577589, 0.096192636, 0.08669752,
  0.07733512, 0.06817503, 0.05931618, 0.05089102, 0.04306481, 0.03603612, 0.030034564, 0.02531981,
  0.022180311, 0.020934077
};


ValorRestringido distolica(80, PRESION_DISTOLICA_MINIMA, PRESION_DISTOLICA_MAXIMA);

ValorRestringido sistolica(120, PRESION_SISTOLICA_MINIMA, PRESION_SISTOLICA_MAXIMA);


void set_presion(uint sis, uint dis) {
  sistolica.set_valor(sis);
  distolica.set_valor(dis);
}

void pantalla_presion_mostrar() {
  pantalla_actual = PantallaActual::Presion;
  pantalla_mostrar(F("Sistolica"),
                   "Valor: " + sistolica.obtenerS(),
                   F("Distolica"),
                   "Valor: " + distolica.obtenerS());
}

void presion_distolica_aumentar() {
  if (distolica.get_valor() + 1 > sistolica.get_valor()) {
    return;
  }
  distolica.aumentar(1);
  pantalla_presion_mostrar();
}

void presion_distolica_disminuir() {
  distolica.disminuir(1);
  pantalla_presion_mostrar();
}

void presion_sistolica_aumentar() {
  sistolica.aumentar(1);
  pantalla_presion_mostrar();
}

void presion_sistolica_disminuir() {
  if (sistolica.get_valor() - 1 < distolica.get_valor()) {
    return;
  }
  sistolica.disminuir(1);
  pantalla_presion_mostrar();
}

void actualizar_dac_presion(uint bpm) {
  tiempo_cambio_datos = (FRECUENCIA_CARDIACA_NORMAL / (double)bpm) * DISTANCIA_ENTRE_DATOS_MICROS;
}

void loop_simulacion_presion() {
  if ((micros() - micros_ultimo_dato_mostrado) > tiempo_cambio_datos) {
    generar_onda_presion();
    micros_ultimo_dato_mostrado = micros();
  }
}

void generar_onda_presion() {
  auto valor_tabla_actual = valor_index_presion(indice_actual);
  auto valor_presion = (sistolica.get_valor() - distolica.get_valor()) * valor_tabla_actual + distolica.get_valor();
  auto valor_presion_normalizada = valor_presion / PRESION_SISTOLICA_MAXIMA;
  // dac_presion.setVoltage(valor_presion_normalizada * 4095, false);
  dac_presion(valor_presion_normalizada * 4095);

  indice_actual++;

  if (indice_actual > NUMERO_DATOS_PRESION - 1) {
    indice_actual = 0;
  }
}

void interrupt_simulation_presion(uint i) {
  auto valor_tabla_actual = valor_index_presion(i);
  auto valor_presion = (sistolica.get_valor() - distolica.get_valor()) * valor_tabla_actual + distolica.get_valor();
  auto valor_presion_normalizada = valor_presion / PRESION_SISTOLICA_MAXIMA;
  // dac_presion.setVoltage(valor_presion_normalizada * 4095, false);
  dac_presion(valor_presion_normalizada * 4095);
}

float valor_index_presion(int i) {
  return pgm_read_float(&valores_presion_base[i]);
}