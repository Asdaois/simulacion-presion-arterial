#pragma once
// Pines 0 y 1 son para el puerto serial es recomendado no usarlos
// Pines de la pantalla
#define D_D4 2
#define D_D5 3
#define D_D6 4
#define D_D7 5
#define D_RS 7
#define D_E 6

// Pines del keypad
#define K_R1 8
#define K_R2 9
#define K_R3 10
#define K_R4 11
#define K_C1 12
#define K_C2 16
#define K_C3 14 // A0
#define K_C4 15 // A1

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
