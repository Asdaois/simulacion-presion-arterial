#include "librerias.h"

#define TIEMPO_CUANDO_PRESIONADO 500
#define FRECUENCIA_CARDIACA_NORMAL 60
#define DISTANCIA_ENTRE_DATOS_MICROS 7692
#define NUMERO_DATOS 130;

uint ultimo_tiempo_presionado = 0;
char key_sostenida = '#';

enum PantallaActual {
  Presion,
  BPMYECG,
  TemperaturaYSpO2,
};

PantallaActual pantalla_actual;

Adafruit_MCP4728 mcp;

void setup() {
  Serial.begin(9600);
  pantalla_configurar();
  pantalla_mostrar("Configurando", "Teclado matricial", "", "");
  delay(100);
  teclado_configurar();
  Serial.println("Programa iniciado");

  pantalla_mostrar("Configurando", "Chip MCP", "", "");
  mcp.begin();
  delay(200);
  if (!mcp.begin()) {
    pantalla_mostrar("Error", "Con Chip MCP", "", "");
    Serial.println("Fallo al conectarse con MCP4728 chip");
    while (1) {
      delay(10);
    }
  }
  pantalla_ecg_bpm_mostrar();
}

uint tiempo_cambio_datos = DISTANCIA_ENTRE_DATOS_MICROS;
unsigned long micros_ultimo_dato_mostrado = 0;
uint i = 0;

void loop() {
  char key = teclado_obtener_key();
  manejar_key_sostenida();

  // loop_simulacion_presion();
  // loop_simulacion_ecg();
  
  if ((micros() - micros_ultimo_dato_mostrado) > tiempo_cambio_datos) {
    micros_ultimo_dato_mostrado = micros();
    Serial.println(micros_ultimo_dato_mostrado);

    interrupt_simulation_ecg(i);
    interrupt_simulation_presion(i);
    Serial.println();

    if (i > NUMERO_DATOS - 1) {
      i = 0;
    }
  }
}

void pantalla_mostrar(String linea1, String linea2, String linea3, String linea4) {
  pantalla_mostrar_implementacion(linea1, linea2, linea3, linea4);
}


void teclado_evento(char key) {
  switch (teclado_obtener_estado()) {
    case PRESSED:
      switch (key) {
        case ECG_NORMAL:
          ecg_cambiar_estado_normal();
          Serial.println("Tecla presionada: ECG Normal");
          break;

        case ECG_SOBLO_CORAZON:
          ecg_cambiar_estado_soplo();
          Serial.println("Tecla presionada: ECG Soblo Corazón");
          break;

        case ECG_ARRITMIA:
          ecg_cambiar_estado_arritmia();
          Serial.println("Tecla presionada: ECG Arritmia");
          break;

        case POR_DEFINIR:
          pantalla_mostrar("Por Definir", "", "", "");
          Serial.println("Tecla presionada: Por Definir");
          break;

        case PRESION_DISTOLICA_SUBIR:
          presion_distolica_aumentar();
          Serial.println("Tecla presionada: Presion Diastolica Subir");
          break;

        case PRESION_DISTOLICA_BAJAR:
          presion_distolica_disminuir();
          Serial.println("Tecla presionada: Presion Diastólica Bajar");
          break;

        case PRESION_SISTOLICA_SUBIR:
          presion_sistolica_aumentar();
          Serial.println("Tecla presionada: Presion Sistolica Subir");
          break;

        case PRESION_SISTOLICA_BAJAR:
          presion_sistolica_disminuir();
          Serial.println("Tecla presionada: Presion Sistolica Bajar");
          break;

        case BMP_SUBIR:
          bpm_subir();
          Serial.println("Tecla presionada: BMP Subir");
          break;

        case BMP_BAJAR:
          bpm_bajar();
          Serial.println("Tecla presionada: BMP Bajar");
          break;

        case MENU_SUBIR:
          menu_arriba();
          Serial.println("Tecla presionada: Menú Subir");
          break;

        case MENU_BAJAR:
          menu_abajo();
          Serial.println("Tecla presionada: Menú Bajar");
          break;

        case TEMPERATURA_SUBIR:
          temperatura_aumentar();
          Serial.println("Tecla presionada: Temperatura Subir");
          break;

        case TEMPERATURA_BAJAR:
          temperatura_disminuir();
          Serial.println("Tecla presionada: Temperatura Bajar");
          break;

        case SO2_SUBIR:
          spo2_aumentar();
          Serial.println("Tecla presionada: SO2 Subir");
          break;

        case SO2_BAJAR:
          spo2_disminuir();
          Serial.println("Tecla presionada: SO2 Bajar");
          break;

        default:
          pantalla_mostrar("Tecla Desconocida", "", "", "");
          Serial.println("Tecla presionada: Desconocida");
      }
      break;

    case RELEASED:
      key_sostenida = '#';
      break;

    case HOLD:
      key_sostenida = key;
      break;

    default:
      break;
  }
}

void menu_arriba() {
  // bpmecg -> presion -> tempso2
  switch (pantalla_actual) {
    case PantallaActual::BPMYECG:
      pantalla_presion_mostrar();
      break;
    case PantallaActual::Presion:
      pantalla_temperatura_spo2_mostrar();
      break;
    case PantallaActual::TemperaturaYSpO2:
      pantalla_ecg_bpm_mostrar();
      break;
  }
}

void menu_abajo() {
  // bpmecg <- presion <- tempso2
  switch (pantalla_actual) {
    case PantallaActual::BPMYECG:
      pantalla_temperatura_spo2_mostrar();
      break;
    case PantallaActual::Presion:
      pantalla_ecg_bpm_mostrar();
      break;
    case PantallaActual::TemperaturaYSpO2:
      pantalla_presion_mostrar();
      break;
  }
}

void manejar_key_sostenida() {
  static uint tiempo_actual = 0;
  static uint tiempo_previo = 0;

  tiempo_actual = millis();
  if (key_sostenida == '#') { return; }

  if ((tiempo_actual - tiempo_previo) < 50) {
    return;
  }

  tiempo_actual = tiempo_previo;
  switch (key_sostenida) {

    case PRESION_DISTOLICA_SUBIR:
      presion_distolica_aumentar();
      Serial.println("Tecla presionada: Presion Diastolica Subir");
      break;

    case PRESION_DISTOLICA_BAJAR:
      presion_distolica_disminuir();
      Serial.println("Tecla presionada: Presion Diastólica Bajar");
      break;

    case PRESION_SISTOLICA_SUBIR:
      presion_sistolica_aumentar();
      Serial.println("Tecla presionada: Presion Sistolica Subir");
      break;

    case PRESION_SISTOLICA_BAJAR:
      presion_sistolica_disminuir();
      Serial.println("Tecla presionada: Presion Sistolica Bajar");
      break;

    case BMP_SUBIR:
      bpm_subir();
      Serial.println("Tecla presionada: BMP Subir");
      break;

    case BMP_BAJAR:
      bpm_bajar();
      Serial.println("Tecla presionada: BMP Bajar");
      break;

    case TEMPERATURA_SUBIR:
      temperatura_aumentar();
      Serial.println("Tecla presionada: Temperatura Subir");
      break;

    case TEMPERATURA_BAJAR:
      temperatura_disminuir();
      Serial.println("Tecla presionada: Temperatura Bajar");
      break;

    case SO2_SUBIR:
      spo2_aumentar();
      Serial.println("Tecla presionada: SO2 Subir");
      break;

    case SO2_BAJAR:
      spo2_disminuir();
      Serial.println("Tecla presionada: SO2 Bajar");
      break;

    default:
      Serial.println("Tecla no valida on hold");
  }
}


void dac_presion(uint valor) {
  mcp.setChannelValue(MCP4728_CHANNEL_A, valor);
}
void dac_ecg(uint valor) {
  mcp.setChannelValue(MCP4728_CHANNEL_B, valor);
}
void dac_temperatura(uint valor) {
  mcp.setChannelValue(MCP4728_CHANNEL_C, valor);
}
void dac_spo2(uint valor) {
  mcp.setChannelValue(MCP4728_CHANNEL_D, valor);
}
