#include <stdlib.h>
#include "queue.h"

Queue cola_crear() {
  Queue cola = malloc(sizeof(_Queue));
  cola->primero = NULL;
  cola->ultimo = NULL;

  return cola;
}

void cola_encolar(Queue cola, void *dato) {
  QNode *nuevoNodo = malloc(sizeof(QNode));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;
  nuevoNodo->ant = cola->ultimo;
  if (cola->ultimo != NULL)
    cola->ultimo->sig = nuevoNodo;
  if (cola->primero == NULL)
    cola->primero = nuevoNodo;
  cola->ultimo = nuevoNodo;
}

void cola_desencolar(Queue cola) {
  if (cola) {
    if (cola->primero) {
      if (cola->primero == cola->ultimo) {
        free(cola->primero);
        cola->primero = NULL;
        cola->ultimo = NULL;
      } else {
        QNode *aux = cola->primero;
        cola->primero = aux->sig;
        cola->primero->ant = NULL;
        free(aux);
      }
    }
  }
}

int cola_es_vacia(Queue cola) {
  return cola->primero == NULL;
}

void cola_destruir(Queue cola) {
  if (cola) {
    while (cola->primero) {
      cola_desencolar(cola);
    }

    free(cola);
  }
}

void *cola_pop(Queue cola) {
  void *elemento = NULL;
  if (cola) {
    if (cola->primero) {
      elemento = cola->primero->dato;
      cola_desencolar(cola);
    }
  }

  return elemento;
}
