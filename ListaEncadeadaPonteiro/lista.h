#ifndef LISTA_H
#define LISTA_H

#include "dado.h"

typedef struct item {
    Dado dado;
    struct item *prox;
} Item;

typedef Item Lista;

void inicializar(Lista *lista);
void visualizar(Lista lista);
void adicionar(Lista *lista, Dado dado);
Item buscar(Lista lista, Dado dado);
int remover(Lista *lista, Dado dado);

#endif

