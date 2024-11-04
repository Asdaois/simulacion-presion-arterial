#define ECG_NORMAL '0'
#define ECG_SOBLO_CORAZON '1'
#define ECG_ARRITMIA '2'
#define POR_DEFINIR '3'

#define PRESION_DISTOLICA_SUBIR '4'
#define PRESION_DISTOLICA_BAJAR '5'
#define PRESION_SISTOLICA_SUBIR '6'
#define PRESION_SISTOLICA_BAJAR '7'

#define BMP_SUBIR '8'
#define BMP_BAJAR '9'

#define MENU_SUBIR 'A'
#define MENU_BAJAR 'B'

#define TEMPERATURA_SUBIR 'C'
#define TEMPERATURA_BAJAR 'D'

#define SO2_SUBIR 'E'
#define SO2_BAJAR 'F'

void setup() {
  Serial.begin(9600);
  pantalla_configurar();
  pantalla_mostrar("Nada aca", "Segunda Linea", "Tercera Linea", "Cuarta Linea");
  teclado_configurar();
  Serial.println("Programa iniciado");
}

void loop() {
  char key = teclado_obtener_key();
}

void pantalla_mostrar(String linea1, String linea2, String linea3, String linea4) {
  pantalla_mostrar_implementacion(linea1, linea2, linea3, linea4);
}

#include <Keypad.h>
void teclado_evento(char key) {
  switch (teclado_obtener_estado()) {
    case PRESSED:
      switch (key) {
        case ECG_NORMAL:
          pantalla_mostrar("ECG Normal", "", "", "");
          Serial.println("Tecla presionada: ECG Normal");
          break;

        case ECG_SOBLO_CORAZON:
          pantalla_mostrar("ECG Soblo Corazon", "", "", "");
          Serial.println("Tecla presionada: ECG Soblo Corazón");
          break;

        case ECG_ARRITMIA:
          pantalla_mostrar("ECG Arritmia", "", "", "");
          Serial.println("Tecla presionada: ECG Arritmia");
          break;

        case POR_DEFINIR:
          pantalla_mostrar("Por Definir", "", "", "");
          Serial.println("Tecla presionada: Por Definir");
          break;

        case PRESION_DISTOLICA_SUBIR:
          pantalla_mostrar("Presion Diastolica Subir", "", "", "");
          Serial.println("Tecla presionada: Presion Diastolica Subir");
          break;

        case PRESION_DISTOLICA_BAJAR:
          pantalla_mostrar("Presion Diastolica Bajar", "", "", "");
          Serial.println("Tecla presionada: Presion Diastólica Bajar");
          break;

        case PRESION_SISTOLICA_SUBIR:
          pantalla_mostrar("Presion Sistolica Subir", "", "", "");
          Serial.println("Tecla presionada: Presion Sistolica Subir");
          break;

        case PRESION_SISTOLICA_BAJAR:
          pantalla_mostrar("Presion Sistolica Bajar", "", "", "");
          Serial.println("Tecla presionada: Presion Sistolica Bajar");
          break;

        case BMP_SUBIR:
          pantalla_mostrar("BMP Subir", "", "", "");
          Serial.println("Tecla presionada: BMP Subir");
          break;

        case BMP_BAJAR:
          pantalla_mostrar("BMP Bajar", "", "", "");
          Serial.println("Tecla presionada: BMP Bajar");
          break;

        case MENU_SUBIR:
          pantalla_mostrar("Menu Subir", "", "", "");
          Serial.println("Tecla presionada: Menú Subir");
          break;

        case MENU_BAJAR:
          pantalla_mostrar("Menu Bajar", "", "", "");
          Serial.println("Tecla presionada: Menú Bajar");
          break;

        case TEMPERATURA_SUBIR:
          pantalla_mostrar("Temperatura Subir", "", "", "");
          Serial.println("Tecla presionada: Temperatura Subir");
          break;

        case TEMPERATURA_BAJAR:
          pantalla_mostrar("Temperatura Bajar", "", "", "");
          Serial.println("Tecla presionada: Temperatura Bajar");
          break;

        case SO2_SUBIR:
          pantalla_mostrar("SO2 Subir", "", "", "");
          Serial.println("Tecla presionada: SO2 Subir");
          break;

        case SO2_BAJAR:
          pantalla_mostrar("SO2 Bajar", "", "", "");
          Serial.println("Tecla presionada: SO2 Bajar");
          break;

        default:
          pantalla_mostrar("Tecla Desconocida", "", "", "");
          Serial.println("Tecla presionada: Desconocida");
      }
      break;

    case RELEASED:
      break;

    case HOLD:
      break;

    default:
      break;
  }
}