#include "ValorRestringido.h"


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

#define NUMERO_DATOS_ECG 256;
int indice_actual_ECG = 0;
const byte ECG[256] PROGMEM = {
  73, 74, 75, 75, 74, 73, 73, 73, 73, 72, 71, 69, 68, 67, 67, 67,
  68, 68, 67, 65, 62, 61, 59, 57, 56, 55, 55, 54, 54, 54, 55, 55,
  55, 55, 55, 55, 54, 53, 51, 50, 49, 49, 52, 61, 77, 101, 132,
  169, 207, 238, 255, 254, 234, 198, 154, 109, 68, 37, 17, 5,
  0, 1, 6, 13, 20, 28, 36, 45, 52, 57, 61, 64, 65, 66, 67, 68, 68,
  69, 70, 71, 71, 71, 71, 71, 71, 71, 71, 72, 72, 72, 73, 73, 74,
  75, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 86, 88, 91, 93, 96,
  98, 100, 102, 104, 107, 109, 112, 115, 118, 121, 123, 125,
  126, 127, 127, 127, 127, 127, 126, 125, 124, 121, 119, 116,
  113, 109, 105, 102, 98, 95, 92, 89, 87, 84, 81, 79, 77, 76, 75,
  74, 73, 72, 70, 69, 68, 67, 67, 67, 68, 68, 68, 69, 69, 69, 69,
  69, 69, 69, 70, 71, 72, 73, 73, 74, 74, 75, 75, 75, 75, 75, 75,
  74, 74, 73, 73, 73, 73, 72, 72, 72, 71, 71, 71, 71, 71, 71, 71,
  70, 70, 70, 69, 69, 69, 69, 69, 70, 70, 70, 69, 68, 68, 67, 67,
  67, 67, 66, 66, 66, 65, 65, 65, 65, 65, 65, 65, 65, 64, 64, 63,
  63, 64, 64, 65, 65, 65, 65, 65, 65, 65, 64, 64, 64, 64, 64, 64,
  64, 64, 65, 65, 65, 66, 67, 68, 69, 71, 72, 73
};

unsigned long tiempo_cambio_datos_ECG = 3906;


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


void actualizar_dac_ecg(uint bpm) {
  tiempo_cambio_datos_ECG = (FRECUENCIA_CARDIACA_NORMAL / (double)bpm) * 3096.25;
}

void generar_onda_ecg() {
  auto valor_tabla_actual = valor_index_ecg(indice_actual_ECG);
  auto valor_ecg = valor_tabla_actual / (double)255;

  dac_ecg(valor_ecg * 4095);

  indice_actual_ECG++;

  if (indice_actual_ECG > 255) {
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