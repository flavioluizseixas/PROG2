#ifndef LISTA_H
#define LISTA_H

#include "dado.h"

typedef struct {
    Dado *vetor_de_dados;
    int primeira_pos;
    int ultima_pos;
    int numero_de_elementos;
} Lista;

Lista *inicializar(int numero_de_elementos);
void visualizar(Lista *lista);

void adicionar_pilha(Lista *lista, Dado dado);
Dado remover_pilha(Lista *lista);

void adicionar_fila(Lista *lista, Dado dado);
Dado remover_fila(Lista *lista);

#endif /* LISTA_H */

