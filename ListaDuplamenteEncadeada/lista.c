#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "dado.h"
#include "lista.h"

Lista *inicializar() {
    Lista *lista = malloc(sizeof(Item));
    lista->ant = NULL;
    lista->prox = NULL;
    
    return lista;
};

void visualizar(Lista *item) {
    while (item->prox != NULL) {
        Dado dado = item->dado;
        printf("Endereço %p, Anterior %p, Próximo %p -- id: %i; Nome %s\n", item, item->ant, item->prox, dado.id, dado.nome);
        item = item->prox;
    }
}

void adicionar(Lista *lista, Dado dado) {
    Item *item = lista;
        
    while (item->prox != NULL) {
        item = item->prox;
    }
    Item *novoItem = malloc(sizeof(Item));
    novoItem->ant = item;
    novoItem->prox = NULL;

    item->dado = dado;
    item->prox = novoItem;
}

Lista *remover(Lista *lista, Dado ref) {
    Item *item = buscar(lista, ref);
    
    if (item->prox == NULL) {
        printf("Item não encontrado para remoção\n");
        return NULL;
    }

    item->prox->ant = item->ant;

    if(item->ant != NULL) {
        item->ant->prox = item->prox;
    }
    else {
        lista = item->prox;
    }
    
    free(item);
    
    return lista;
}

Item *buscar(Lista *item, Dado ref) {
    while (item->prox != NULL) {
        if (comparar_dado(item->dado, ref)) {
            return item;
        }
        else {
            item = item->prox;
        }
    }

    return item;
}
