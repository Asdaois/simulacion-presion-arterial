uint distolica_maxima = 160;
uint distolica_minima = 40;
uint sistolica_maxima = 220;
uint sistolica_minima = 80;

uint distolica = 59;
uint sistolica = 60;

void pantalla_presion_mostrar() {
  pantalla_mostrar("Sistolica",
                   "Valor: " + String(distolica),
                   "Distolica",
                   "Valor: " + String(sistolica));
}

void presion_distolica_aumentar() {
  distolica++;
  pantalla_presion_mostrar();
}

void presion_distolica_disminuir() {
  distolica--;
  pantalla_presion_mostrar();
}

void presion_sistolica_aumentar() {
  sistolica++;
  pantalla_presion_mostrar();
}

void presion_sistolica_disminuir() {
  sistolica--;
  pantalla_presion_mostrar();
}