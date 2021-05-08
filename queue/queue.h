#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct _QNode {
  void *dato;
  struct _QNode *sig;
  struct _QNode *ant;
} QNode;

typedef struct _Queue {
  QNode *primero;
  QNode *ultimo;
} _Queue;

typedef _Queue *Queue;

/**
 * Devuelve una cola vacia.
 */
Queue cola_crear();

/**
 * Inserta un elemento dado al final de la cola dada
 */
void cola_encolar(Queue cola, void *dato);

/**
 * Elimina el elemento que se encuentra al inicio de la cola dada 
 */
void cola_desencolar(Queue cola);

/**
 * Indica si la cola es vacia
 */
int cola_es_vacia(Queue cola);

/**
 * Destruye una cola dada
 */
void cola_destruir(Queue cola);

/**
 * Devuelve el primer elemento de la cola dada y lo elimina de la misma
 */
void *cola_pop(Queue cola);

#endif                          /* __QUEUE_H__ */
