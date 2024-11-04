uint temperatura_maxima = 160;
uint temperatura_minima = 40;
uint spo2_maxima = 220;
uint spo2_minima = 80;

uint temperatura = 59;
uint spo2 = 60;

void pantalla_temperatura_spo2_mostrar() {
  pantalla_actual = PantallaActual::TemperaturaYSO2;
  pantalla_mostrar("Temperatura",
                   "Valor: " + String(temperatura),
                   "SPO2",
                   "Valor: " + String(spo2));
}

void temperatura_aumentar() {
  temperatura++;
  pantalla_temperatura_spo2_mostrar();
}

void temperatura_disminuir() {
  temperatura--;
  pantalla_temperatura_spo2_mostrar();
}

void spo2_aumentar() {
  spo2++;
  pantalla_temperatura_spo2_mostrar();
}

void spo2_disminuir() {
  spo2--;
  pantalla_temperatura_spo2_mostrar();
}