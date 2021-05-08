#include "intervalo.h"
#include <stdlib.h>
#include <stdio.h>

Intervalo *intervalo_crear(double extIzq, double extDer) {
  Intervalo *nuevo = malloc(sizeof(Intervalo));
  nuevo->extIzq = extIzq;
  nuevo->extDer = extDer;

  return nuevo;
}

void intervalo_destruir(Intervalo * intervalo) {
  free(intervalo);
}

int intervalo_validar(Intervalo * intervalo) {
  return intervalo->extIzq <= intervalo->extDer;
}

int intervalo_interseca(Intervalo * intervaloA, Intervalo * intervaloB) {
  return !(intervaloA->extDer < intervaloB->extIzq
           || intervaloA->extIzq > intervaloB->extDer);
}

void intervalo_imprimir(Intervalo * intervalo) {
  printf("INTERVALO: [%lf,%lf]\n", intervalo->extIzq,
         intervalo->extDer);
}

int intervalo_coinciden(Intervalo * intervaloA, Intervalo * intervaloB) {
  return intervaloA->extIzq == intervaloB->extIzq
      && intervaloA->extDer == intervaloB->extDer;
}
