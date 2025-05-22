#include "librerias.h"


enum EstadosECG {
  Normal,
  Arritmia,
  Soplo,
};

EstadosECG estadoECG = EstadosECG::Normal;

#define FRECUENCIA_CARDIACA_MINIMA 40
#define FRECUENCIA_CARDIACA_MAXIMA 180


ValorRestringido bpm(FRECUENCIA_CARDIACA_NORMAL, FRECUENCIA_CARDIACA_MINIMA, FRECUENCIA_CARDIACA_MAXIMA);
unsigned long micros_ultimo_dato_mostrado_ecg = 0;

#define NUMERO_DATOS_ECG 130;
int indice_actual_ECG = 0;
const byte ECG[256] PROGMEM = {
  73, 74, 75, 74, 73, 73, 71, 68, 67, 68, 67, 62, 59, 56, 55, 54, 55, 55, 55, 54, 51,
  49, 52, 77, 132, 207, 255, 234, 154, 68, 17, 0, 6, 20, 36, 52, 61, 65, 67, 68,
  70, 71, 71, 71, 71, 72, 73, 74, 75, 77, 79, 81, 83, 86, 91, 96, 100, 104, 109,
  115, 121, 125, 127, 127, 127, 125, 121, 116, 109, 102, 95, 89, 84, 79, 76, 74,
  72, 69, 67, 67, 68, 69, 69, 69, 69, 71, 73, 74, 75, 75, 75, 74, 73, 73, 72, 72,
  71, 71, 71, 70, 70, 69, 69, 70, 70, 68, 67, 67, 66, 66, 65, 65, 65, 65, 64, 63,
  64, 65, 65, 65, 64, 64, 64, 64, 65, 65, 67, 69, 70, 72
};

unsigned long tiempo_cambio_datos_ECG = 7692;


String estado_ecg_to_string() {
  pantalla_actual = PantallaActual::BPMYECG;
  switch (estadoECG) {
    case EstadosECG::Normal: return "Normal";
    case EstadosECG::Arritmia: return "Arritmia";
    case EstadosECG::Soplo: return "Soplo";
  }
}

void pantalla_ecg_bpm_mostrar() {
  pantalla_mostrar("ECG",
                   "Estado: " + estado_ecg_to_string(),
                   "BPM",
                   "Valor: " + bpm.obtenerS());
}

void ecg_cambiar_estado_normal() {
  estadoECG = EstadosECG::Normal;
  pantalla_ecg_bpm_mostrar();
}

void ecg_cambiar_estado_arritmia() {
  estadoECG = EstadosECG::Arritmia;
  pantalla_ecg_bpm_mostrar();
}

void ecg_cambiar_estado_soplo() {
  estadoECG = EstadosECG::Soplo;
  pantalla_ecg_bpm_mostrar();
}

void bpm_subir() {
  bpm.aumentar(1);
  pantalla_ecg_bpm_mostrar();
  actualizar_dac_presion(bpm.get_valor());
  actualizar_dac_ecg(bpm.get_valor());
}

void loop_simulacion_ecg() {
  if ((micros() - micros_ultimo_dato_mostrado_ecg) > tiempo_cambio_datos_ECG) {
    generar_onda_ecg();
    micros_ultimo_dato_mostrado_ecg = micros();
  }
}

void interrupt_simulation_ecg(uint i) {
  auto valor_tabla_actual = valor_index_ecg(i);
  auto valor_ecg = (int)(((double)valor_tabla_actual / (double)255) * 4095);
  if (valor_ecg > 4095) {
    valor_ecg = 4095;
  }
  dac_ecg(valor_ecg);
}

void actualizar_dac_ecg(uint bpm) {
  tiempo_cambio_datos_ECG = (FRECUENCIA_CARDIACA_NORMAL / (double)bpm) * tiempo_cambio_datos_ECG;
}

void generar_onda_ecg() {
  auto valor_tabla_actual = valor_index_ecg(indice_actual_ECG);
  auto valor_ecg = valor_tabla_actual / (double)127;

  dac_ecg(valor_ecg * 4095);

  indice_actual_ECG++;

  if (indice_actual_ECG > NUMERO_DATOS_ECG - 1) {
    indice_actual_ECG = 0;
  }
}

void bpm_bajar() {
  bpm.disminuir(1);
  actualizar_dac_presion(bpm.get_valor());
  actualizar_dac_ecg(bpm.get_valor());
  pantalla_ecg_bpm_mostrar();
}

byte valor_index_ecg(int i) {
  return pgm_read_byte(&ECG[i]);
}