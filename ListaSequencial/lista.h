#ifndef LISTA_H
#define LISTA_H

#include "item.h"

typedef struct {
    Item *item;
    int primeira_pos;
    int ultima_pos;
    int numero_de_elementos;
} Lista;

void inicializar_lista(int numero_de_elementos);
void visualizar_lista();
void adicionar_pilha(Item item);
Item remover_pilha();
void adicionar_fila(Item item);
Item remover_fila();


#endif /* LISTA_H */

