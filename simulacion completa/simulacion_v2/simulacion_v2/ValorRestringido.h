#pragma once

class ValorRestringido {
private:
  uint valor;
  uint valor_minimo;
  uint valor_maximo;
public:
  ValorRestringido(uint valor_inicial, uint valor_minimo, uint valor_maximo)
    : valor(valor_inicial), valor_minimo(valor_minimo), valor_maximo(valor_maximo) {
  }

  aumentar(uint cantidad) {
    if (valor + cantidad > valor_maximo) {
      valor = valor_maximo;
    } else {
      valor += cantidad;
    }
  }

  disminuir(uint cantidad) {
    if (valor - cantidad < valor_minimo) {
      valor = valor_minimo;
    } else {
      valor -= cantidad;
    }
  }

  uint get_valor() {
    return valor;
  }

  String obtenerS() {
    return String(valor);
  }
};