#include "./pines.h"

#define COLUMNAS 16
#define FILAS 4

#include <LiquidCrystal.h>
LiquidCrystal pantalla(D_RS, D_E, D_D7, D_D6, D_D5, D_D4);

void pantalla_configurar() {
  pantalla.begin(COLUMNAS, FILAS);
}

void pantalla_mostrar_implementacion(String linea1, String linea2, String linea3, String linea4) {
  pantalla.clear();
  pantalla.setCursor(0, 0);
  pantalla.println(linea1);
  pantalla.setCursor(0, 1);
  pantalla.println(linea2);
  pantalla.setCursor(0, 2);
  pantalla.println(linea3);
  pantalla.setCursor(0, 3);
  pantalla.println(linea4);
}