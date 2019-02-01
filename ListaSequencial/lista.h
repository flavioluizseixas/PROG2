#ifndef LISTA_H
#define LISTA_H

#include "dado.h"

typedef struct {
    Dado *vetor_de_dados;
    int primeira_pos;
    int ultima_pos;
    int numero_de_elementos;
} Lista;

Lista *inicializar_lista(int numero_de_elementos);
void liberar_lista(Lista *lista);

void visualizar_lista(Lista *lista);

void adicionar_na_lista(Lista *lista, Dado dado);
Dado remover_da_pilha(Lista *lista);
Dado remover_da_fila(Lista *lista);

#endif

