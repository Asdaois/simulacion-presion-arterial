#include "Arduino.h"
#pragma once
// Librerías de Arduino
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Adafruit_MCP4728.h>
#include <Wire.h>

// Librerías propias
#include "pines.h"
#include "ValorRestringido.h"

// Tipos de datos personalizados
typedef unsigned int uint;

struct ConfiguracionEstado {
  uint sis;
  uint dis;
  uint O2;
  uint T;
  uint bpm;
};

ConfiguracionEstado configuracionEstadoNormal = {120, 80, 99, 37, 80};
ConfiguracionEstado configuracionEstadoAlta= {145, 95, 91, 40, 100};
ConfiguracionEstado configuracionEstadoBaja = {90, 60, 84, 34, 40};