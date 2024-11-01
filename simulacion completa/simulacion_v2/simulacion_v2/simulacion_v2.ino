void setup() {
  pantalla_configurar();
  pantalla_mostrar("Nada aca", "Segunda Linea", "Tercera Linea", "Cuarta Linea");
}

void loop() {
  // put your main code here, to run repeatedly:
}

void pantalla_mostrar(String linea1, String linea2, String linea3, String linea4) {
  pantalla_mostrar_implementacion(linea1, linea2, linea3, linea4);
}