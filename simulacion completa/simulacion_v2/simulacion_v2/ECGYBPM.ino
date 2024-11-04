enum EstadosECG {
  Normal,
  Arritmia,
  Soplo,
};

EstadosECG estadoECG = EstadosECG::Normal;
uint bpm = 60;

String estado_ecg_to_string() {
    switch (estadoECG) {
        case EstadosECG::Normal: return "Normal";
        case EstadosECG::Arritmia: return "Arritmia";
        case EstadosECG::Soplo: return "Soplo";
    }
}

void pantalla_ecg_bpm_mostrar() {
  pantalla_mostrar("ECG",
                   "Estado: " + estado_ecg_to_string(),
                   "BPM",
                   "Valor: " + String(bpm));
}

void ecg_cambiar_estado_normal() {
  estadoECG = EstadosECG::Normal;
  pantalla_ecg_bpm_mostrar();
}

void ecg_cambiar_estado_arritmia() {
  estadoECG = EstadosECG::Arritmia;
  pantalla_ecg_bpm_mostrar();
} 

void ecg_cambiar_estado_soplo() {
  estadoECG = EstadosECG::Soplo;
  pantalla_ecg_bpm_mostrar();
} 