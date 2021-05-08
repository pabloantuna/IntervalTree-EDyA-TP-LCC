#include "itree.h"
#include <stdlib.h>
#include <stdio.h>

ITree itree_crear() {
  return NULL;
}

ITree itree_nuevo_nodo(Intervalo * intervalo) {
  ITree nodo = malloc(sizeof(INodo));
  nodo->izq = NULL;
  nodo->der = NULL;
  // Creamos un nuevo intervalo
  nodo->intervalo = intervalo_crear(intervalo->extIzq, intervalo->extDer);
  nodo->maxExt = intervalo->extDer;
  nodo->altura = 0;

  return nodo;
}

void itree_destruir(ITree tree) {
  if (tree != NULL) {
    itree_destruir(tree->izq);
    itree_destruir(tree->der);
    itree_destruir_nodo(tree);
  }
}

void itree_destruir_nodo(INodo * tree) {
  if (tree != NULL) {
    intervalo_destruir(tree->intervalo);
    free(tree);
  }
}

ITree itree_insertar(ITree tree, Intervalo * intervalo) {
  if (intervalo_validar(intervalo)) {
    if (tree == NULL)
      tree = itree_nuevo_nodo(intervalo);
    else {
      if (!intervalo_coinciden(tree->intervalo, intervalo)) {
        if (inserto_izquierda(intervalo, tree))
          tree->izq = itree_insertar(tree->izq, intervalo);
        else
          tree->der = itree_insertar(tree->der, intervalo);

        tree->altura = itree_nueva_altura(tree);
        tree->maxExt = itree_nuevo_extremo_maximo(tree);

        if ((intervalo)->extDer > tree->maxExt)
          tree->maxExt = (intervalo)->extDer;

        tree = itree_balancear(tree);

      } else
        printf("El intervalo ingresado ya se encuentra en el arbol\n");
    }
  } else
    printf("El intervalo ingresado no es valido\n");

  return tree;
}

int inserto_izquierda(Intervalo * intervalo, ITree tree) {
  return intervalo->extIzq < tree->intervalo->extIzq
      || (intervalo->extIzq == tree->intervalo->extIzq
          && intervalo->extDer < tree->intervalo->extDer);
}

int itree_altura(ITree tree) {
  if (!tree)
    return -1;
  return tree->altura;
}

int itree_nueva_altura(ITree tree) {
  if (!tree)
    return -1;
  if (itree_altura(tree->izq) > itree_altura(tree->der))
    return itree_altura(tree->izq) + 1;
  else
    return itree_altura(tree->der) + 1;
}

double itree_nuevo_extremo_maximo(ITree tree) {
  double maximo = 0;
  if (tree) {
    maximo = tree->intervalo->extDer;
    if (tree->izq) {
      if (maximo < tree->izq->maxExt)
        maximo = tree->izq->maxExt;
    }
    if (tree->der) {
      if (maximo < tree->der->maxExt)
        maximo = tree->der->maxExt;
    }
  }
  return maximo;
}

int itree_balance_factor(ITree tree) {
  return itree_altura(tree->izq) - itree_altura(tree->der);
}


ITree itree_intersectar(ITree tree, Intervalo * intervalo) {
  if (tree && tree->maxExt >= intervalo->extIzq) {
    if (intervalo_interseca(tree->intervalo, intervalo)) {
      return tree;
    } else {
      ITree aux =
          tree->intervalo->extIzq > intervalo->extDer ? tree->izq : tree->der;
      if (aux && aux->maxExt >= intervalo->extIzq)
        return itree_intersectar(aux, intervalo);
      else
        return NULL;
    }
  }
  return NULL;
}

ITree itree_rotar_derecha(ITree tree) {
  ITree aux = tree->izq;
  tree->izq = aux->der;
  aux->der = tree;

  //Altura

  tree->altura = itree_nueva_altura(tree);
  aux->altura = itree_nueva_altura(aux);

  //maxExt

  tree->maxExt = itree_nuevo_extremo_maximo(tree);
  aux->maxExt = itree_nuevo_extremo_maximo(aux);

  return aux;
}

ITree itree_rotar_izquierda(ITree tree) {
  ITree aux = tree->der;
  tree->der = aux->izq;
  aux->izq = tree;

  //Altura

  tree->altura = itree_nueva_altura(tree);
  aux->altura = itree_nueva_altura(aux);

  //maxExt

  tree->maxExt = itree_nuevo_extremo_maximo(tree);
  aux->maxExt = itree_nuevo_extremo_maximo(aux);

  return aux;
}

ITree itree_balancear(ITree tree) {
  if (tree) {
    int balanceFactor = itree_balance_factor(tree);
    // Caso izquierda
    if (balanceFactor == 2) {
      // Caso izquierda-derecha
      if (itree_balance_factor(tree->izq) < 0)
        tree->izq = itree_rotar_izquierda(tree->izq);
      // Rotacion en ambos casos
      tree = itree_rotar_derecha(tree);

    }
    // Caso derecha
    if (balanceFactor == -2) {
      // Caso derecha-izquierda
      if (itree_balance_factor(tree->der) > 0)
        tree->der = itree_rotar_derecha(tree->der);
      // Rotacion en ambos casos
      tree = itree_rotar_izquierda(tree);
    }
  }

  return tree;
}

ITree itree_obtener_minimo(ITree tree) {
  ITree aux = tree;
  if (aux) {
    if (!aux->izq) {
      return aux;
    }
  }
  return itree_obtener_minimo(aux->izq);
}


ITree itree_eliminar(ITree tree, Intervalo * intervalo) {
  if (tree) {
    //si encontre el nodo
    if (intervalo_coinciden(tree->intervalo, intervalo)) {
      // si es una hoja
      if (!tree->der && !tree->izq) {
        itree_destruir_nodo(tree);
        tree = NULL;
      } else {
        // tiene un solo hijo
        if (!tree->der || !tree->izq) {
          ITree nodoAux = tree->izq ? tree->izq : tree->der;
          itree_destruir_nodo(tree);
          tree = nodoAux;
        }
        // tiene ambos hijos
        else {
          ITree nodoAux = itree_obtener_minimo(tree->der);

          // copio los valores del intervalo minimo de mi hijo derecho
          tree->intervalo->extIzq = nodoAux->intervalo->extIzq;
          tree->intervalo->extDer = nodoAux->intervalo->extDer;

          // elimino el intervalo minimo ya que ahora no pertenece a mi hijo derecho
          tree->der = itree_eliminar(tree->der, nodoAux->intervalo);
        }

        tree->altura = itree_nueva_altura(tree);
        tree->maxExt = itree_nuevo_extremo_maximo(tree);

      }
    } else {
      if (inserto_izquierda(intervalo, tree)) {
        tree->izq = itree_eliminar(tree->izq, intervalo);
      } else {
        tree->der = itree_eliminar(tree->der, intervalo);
      }
    }
  } else {
    printf("El elemento a eliminar no se encuentra en el arbol\n");
  }

  return itree_balancear(tree);
}

void itree_recorrer_dfs(ITree tree, FuncionVisitante visit) {
  if (tree) {
    itree_recorrer_dfs(tree->izq, visit);
    visit(tree->intervalo);
    itree_recorrer_dfs(tree->der, visit);
  }
}

void itree_recorrer_bfs(ITree tree, FuncionVisitante visit) {
  if (tree) {
    Queue cola = cola_crear();
    ITree elemento;
    cola_encolar(cola, tree);
    while (!cola_es_vacia(cola)) {
      elemento = (ITree) cola_pop(cola);
      visit(elemento->intervalo);
      if (elemento->izq) {
        cola_encolar(cola, (void *) elemento->izq);
      }
      if (elemento->der) {
        cola_encolar(cola, (void *) elemento->der);
      }
    }
    cola_destruir(cola);
  }
}
