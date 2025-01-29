#include "iostream"
#include "vector"
#include "cstdint"

int main() {
  std::vector<float> valores_presion_base = {
  73, 74, 75, 75, 74, 73, 73, 73, 73, 72, 71, 69, 68, 67, 67, 67,
  68, 68, 67, 65, 62, 61, 59, 57, 56, 55, 55, 54, 54, 54, 55, 55,
  55, 55, 55, 55, 54, 53, 51, 50, 49, 49, 52, 61, 77, 101, 132,
  169, 207, 238, 255, 254, 234, 198, 154, 109, 68, 37, 17, 5,
  0, 1, 6, 13, 20, 28, 36, 45, 52, 57, 61, 64, 65, 66, 67, 68, 68,
  69, 70, 71, 71, 71, 71, 71, 71, 71, 71, 72, 72, 72, 73, 73, 74,
  75, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 86, 88, 91, 93, 96,
  98, 100, 102, 104, 107, 109, 112, 115, 118, 121, 123, 125,
  126, 127, 127, 127, 127, 127, 126, 125, 124, 121, 119, 116,
  113, 109, 105, 102, 98, 95, 92, 89, 87, 84, 81, 79, 77, 76, 75,
  74, 73, 72, 70, 69, 68, 67, 67, 67, 68, 68, 68, 69, 69, 69, 69,
  69, 69, 69, 70, 71, 72, 73, 73, 74, 74, 75, 75, 75, 75, 75, 75,
  74, 74, 73, 73, 73, 73, 72, 72, 72, 71, 71, 71, 71, 71, 71, 71,
  70, 70, 70, 69, 69, 69, 69, 69, 70, 70, 70, 69, 68, 68, 67, 67,
  67, 67, 66, 66, 66, 65, 65, 65, 65, 65, 65, 65, 65, 64, 64, 63,
  63, 64, 64, 65, 65, 65, 65, 65, 65, 65, 64, 64, 64, 64, 64, 64,
  64, 64, 65, 65, 65, 66, 67, 68, 69, 71, 72, 73
  };

  auto len = valores_presion_base.size();
  std::cout << "vector len " << len << std::endl;
  uint8_t bpm = 60;
  long tiempo_cambio_datos = (bpm / 60) * 1000000 / len;
  std::cout << "Tiempo cambio datos" << tiempo_cambio_datos;

  auto mostrar = true;
  for (auto valor : valores_presion_base) {
    if (mostrar)
      std::cout << valor << ", ";

    mostrar = !mostrar;
  }
  std::cout << "\n";

  auto datos_nuevos = {
 73, 75, 74, 73, 73, 71, 68, 67, 68, 67, 62, 59, 56, 55, 54, 55, 55, 55, 54, 51,
 49, 52, 77, 132, 207, 255, 234, 154, 68, 17, 0, 6, 20, 36, 52, 61, 65, 67, 68,
 70, 71, 71, 71, 71, 72, 73, 74, 75, 77, 79, 81, 83, 86, 91, 96, 100, 104, 109,
 115, 121, 125, 127, 127, 127, 125, 121, 116, 109, 102, 95, 89, 84, 79, 76, 74,
 72, 69, 67, 67, 68, 69, 69, 69, 69, 71, 73, 74, 75, 75, 75, 74, 73, 73, 72, 72,
 71, 71, 71, 70, 70, 69, 69, 70, 70, 68, 67, 67, 66, 66, 65, 65, 65, 65, 64, 63,
 64, 65, 65, 65, 64, 64, 64, 64, 65, 65, 67, 69, 72
  };

  std::cout << datos_nuevos.size();
}