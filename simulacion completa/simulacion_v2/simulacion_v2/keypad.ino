#include "./pines.h"

#define COLUMNAS 4
#define FILAS 4

char keys[FILAS][COLUMNAS] = {
  { '0', '1', '2', '3' },
  { '4', '5', '6', '7' },
  { '8', '9', 'A', 'B' },
  { 'C', 'D', 'E', 'F' }
};

byte pines_filas[FILAS] = { K_R1, K_R2, K_R3, K_R4 };
byte pines_columnas[COLUMNAS] = { K_C1, K_C2, K_C3, K_C4 };

#include <Keypad.h>
Keypad teclado = Keypad(makeKeymap(keys), pines_filas, pines_columnas, FILAS, COLUMNAS);

void teclado_configurar() {
  teclado.addEventListener(teclado_evento);
}

char teclado_obtener_key() {
  return teclado.getKey();
}

int teclado_obtener_estado() {
  return teclado.getState();
}