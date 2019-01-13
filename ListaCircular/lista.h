#ifndef LISTA_H
#define LISTA_H

#include "dado.h"

typedef struct item {
    Dado dado;
    struct item *ant;
    struct item *prox;
} Item;

typedef Item Lista;

Lista *inicializar(Dado dado);
void visualizar(Lista *lista);
void adicionar(Lista *item, Dado dado);
void inserirDepoisDe(Lista *item, Dado dado, Dado referencia);
Item *buscar(Lista *lista, Dado dado);
Lista *remover(Lista *lista, Dado dado);

#endif

