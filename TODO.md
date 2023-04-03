
# Simulador de presión arterial
## Primera Iteración
- [X] Simular la presión arterial normal 
  - [X] cuales son los valores 120/80, diferencia de 40
- [X] Simular la presión arterial alta 
  - [X] cuales son los valores 140/90, diferencia de 50
- [X] Simular la presión arterial baja 
  - [X] cuales son los valores 90/60, diferencia de 30
- [X] Cual es la frecuencia cardíaca 60-100 latidos por minuto
- [X] Amplitud de monitores de signos vitales

- [X] Crear señal base ("presión normal") 
- [X] Crear formulas de interpolación lineal para presiones
  - [X] Normal
  - [X] Baja
  - [X] Alta 

- [X] Funcionamiento
  - [X] Tendrá tres botones para seleccionar la presión a mostrar
  - [X] Las salidas de las presiones es compartida tendrá una sola salida

- [ ] Hardware
  - [ ] Usar DAC MCP4725 para generar la onda 
  - [ ] Agregar un amplificador operacional para aislar la salida


## Segunda Iteración
- [ ] Cambiar la frecuencia cardíaca
  - [ ] Presión cardiaca minima 40 ("Si eres atleta")
  - [ ] Presión cardíaca maxima 120
  - [ ] Usar dos botones una para aumentarla, y una para disminuirla