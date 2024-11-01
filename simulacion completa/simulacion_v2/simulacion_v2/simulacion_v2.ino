
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
      pantalla_mostrar(String(key), "", "", "");
      Serial.println(String(key));
      break;

    case RELEASED:
      break;

    case HOLD:
      break;

    default:
      break;
  }
}