uint temperatura_maxima = 45;
uint temperatura_minima = 25;
uint spo2_maxima = 100;
uint spo2_minima = 0;

uint temperatura = 30;
uint spo2 = 85;

void pantalla_temperatura_spo2_mostrar() {
  pantalla_actual = PantallaActual::TemperaturaYSO2;
  generar_onda_temperatura();
  generar_onda_spo2();
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

void generar_onda_temperatura() {
  dac_temperatura(((double)temperatura / (double)temperatura_maxima) * 4095);
}

void spo2_aumentar() {
  spo2++;
  pantalla_temperatura_spo2_mostrar();
}

void spo2_disminuir() {
  spo2--;
  pantalla_temperatura_spo2_mostrar();
}

void generar_onda_spo2() {
  dac_spo2(((double)spo2 / (double)100) * 4095);
}
