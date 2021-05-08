#include "./ITree/itree.h"
#include "./Intervalo/intervalo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define LONG_MAX_LINEA 100
#define SHORT_MAX_LINEA 15

void imprimir_menu() {
  printf("Comandos\n");
  printf("i [a,b]\t\tinserta el intervalo [a,b] en el arbol\n");
  printf("e [a,b]\t\telimina el intervalo [a,b] del arbol\n");
  printf
      ("? [a,b]\t\tinterseca el intervalo [a,b] con los intervalos del arbol\n");
  printf("dfs\t\timprime los intervalos del arbol usando dfs\n");
  printf("bfs\t\timprime los intervalos del arbol usando bfs\n");
  printf("salir\t\tsale del programa\n\n");
}

int main() {
  char comando[LONG_MAX_LINEA], opcion, izqAux[SHORT_MAX_LINEA],
      derAux[SHORT_MAX_LINEA], *restoIzq, *restoDer,
      final[SHORT_MAX_LINEA] = "";
  double extIzq, extDer;
  ITree arbol = itree_crear(), nodoInterseccion = NULL;
  Intervalo *intervalo;
  imprimir_menu();
  do {
    printf("Ingrese opcion\n");
    scanf("%[^\n]", comando);
    getchar();
    // sscanf si se ejecuta correctamente devuelve la cantidad de variables completadas
    // si falla el input devuelve EOF. Por lo tanto reviso si el resultado devuelto es 4
    if (sscanf(comando, "%c [%[^,],%[^]]%[^\n]", &opcion, izqAux, derAux, final)
        == 4) {
      // luego debo saber si lo ultimo que leo de mi comando es un "]"
      if (!strcmp(final, "]")) {
        extIzq = strtod(izqAux, &restoIzq);
        extDer = strtod(derAux, &restoDer);
        // debo ver si todo el contenido de mis strings auxiliares se pasa a double
        // es decir si no tengo un resto
        if (!strcmp(restoIzq, "") && !strcmp(restoDer, "")) {
          // en caso de que asi sea estoy en las opciones de insertar, 
          // eliminar, intersectar o un comando que no existe
          switch (opcion) {
          case 'i':
            intervalo = intervalo_crear(extIzq, extDer);
            arbol = itree_insertar(arbol, intervalo);
            intervalo_destruir(intervalo);
            break;

          case 'e':
            intervalo = intervalo_crear(extIzq, extDer);
            if (intervalo_validar(intervalo)) {
              arbol = itree_eliminar(arbol, intervalo);
              intervalo_destruir(intervalo);
            } else
              printf("El intervalo a eliminar no es valido\n");
            break;

          case '?':
            intervalo = intervalo_crear(extIzq, extDer);
            if (intervalo_validar(intervalo)) {
              nodoInterseccion = itree_intersectar(arbol, intervalo);
              if (nodoInterseccion) {
                printf("Si, [%.2lf,%.2lf]\n",
                       nodoInterseccion->intervalo->extIzq,
                       nodoInterseccion->intervalo->extDer);
              } else {
                printf("No\n");
              }
            } else
              printf("El intervalo a intersecar no es valido\n");
            intervalo_destruir(intervalo);
            break;

          default:
            printf("La opcion ingresada no es valida\n");
            break;
          }
        } else
          printf("Error de tipo, favor de utilizar numeros\n");
      } else
        printf
            ("Formato no compatible, favor de respetar el formato indicado\n");
    } else {
      if (!strcmp(comando, "dfs")) {
        itree_recorrer_dfs(arbol, &intervalo_imprimir);
      } else if (!strcmp(comando, "bfs")) {
        itree_recorrer_bfs(arbol, &intervalo_imprimir);
      } else if (!strcmp(comando, "salir")) {
        printf("Adios!\n");
      } else {
        printf("Opcion no valida\n");
      }

    }

  } while (strcmp(comando, "salir") != 0);

  itree_destruir(arbol);

}
