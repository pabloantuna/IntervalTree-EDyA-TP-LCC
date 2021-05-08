#ifndef __ITREE_H__
#define __ITREE_H__

#include "../Intervalo/intervalo.h"
#include "../queue/queue.h"

typedef struct _INodo {
  Intervalo *intervalo;
  double maxExt;
  int altura;
  struct _INodo *izq;
  struct _INodo *der;
} INodo;

typedef INodo *ITree;

typedef void (*FuncionVisitante) (Intervalo * intervalo);

/**
 * Devuelve un arbol vacío.
 */
ITree itree_crear();

/**
 * Devuelve un nuevo nodo con el valor de intervalo dado
 */
ITree itree_nuevo_nodo(Intervalo * intervalo);

/**
 * Devuelve la altura asignada al arbol dado
 */
int itree_altura(ITree tree);

/**
 * Calcula y devuelve la altura que debe tener el arbol dado
 */
int itree_nueva_altura(ITree tree);

/**
 * Calcula y devuelve el extremo maximo que debe tener el arbol dado
 */
double itree_nuevo_extremo_maximo(ITree tree);

/**
 * Indica si el intervalo dado debe ir a la izquierda del arbol dado
 */
int inserto_izquierda(Intervalo * intervalo, ITree tree);

/**
 * Destruye el arbol dado
 */
void itree_destruir(ITree tree);

/**
 * Destruye unicamente el nodo dado
 */
void itree_destruir_nodo(INodo * tree);

/**
 * Inserta un intervalo dado en el arbol indicado
 */
ITree itree_insertar(ITree tree, Intervalo * intervalo);

/**
 * Elimina un intervalo dado en el arbol indicado
 */
ITree itree_eliminar(ITree tree, Intervalo * intervalo);

/**
 * Interseca un intervalo dado con el arbol indicado
 */
ITree itree_intersectar(ITree tree, Intervalo * intervalo);

/**
 * Recorre un arbol dado con DFS y 
 * aplica la funcion visitante al intervalo de cada nodo
 */
void itree_recorrer_dfs(ITree tree, FuncionVisitante visit);

/**
 * Recorre un arbol dado con BFS y 
 * aplica la funcion visitante al intervalo de cada nodo
 */
void itree_recorrer_bfs(ITree tree, FuncionVisitante visit);

/**
 * Balancea el arbol dado
 */
ITree itree_balancear(ITree tree);

/**
 * Aplica la rotacion a derecha al arbol dado
 */
ITree itree_rotar_derecha(ITree tree);

/**
 * Aplica la rotacion a derecha al arbol dado
 */
ITree itree_rotar_izquierda(ITree tree);

/**
 * Devuelve el factor de balance del arbol dado
 */
int itree_balance_factor(ITree tree);

#endif                          /* __ITREE_H__ */
