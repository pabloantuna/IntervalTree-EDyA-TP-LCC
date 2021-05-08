#ifndef __INTERVALO_H__
#define __INTERVALO_H__

typedef struct {
  double extIzq;
  double extDer;
} Intervalo;

/**
 * Devuelve un intervalo formado por los extremos dados.
 */
Intervalo *intervalo_crear(double extIzq, double extDer);

/**
 * Destruye el intervalo dado
 */
void intervalo_destruir(Intervalo * intervalo);

/**
 * Indica si el intervalo dado es valido
 */
int intervalo_validar(Intervalo * intervalo);

/**
 * Indica si los dos intervalos dados se intersecan
 */
int intervalo_interseca(Intervalo * intervaloA, Intervalo * intervaloB);

/**
 * Imprime en pantalla el intervalo dado
 */
void intervalo_imprimir(Intervalo * intervalo);

/**
 * Indica si dos intervalos dados son iguales
 */
int intervalo_coinciden(Intervalo * intervaloA, Intervalo * intervaloB);

#endif                          /* __INTERVALO_H__ */
