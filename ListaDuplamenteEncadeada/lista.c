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
    int i = 0;
    while (item->prox != NULL) {
        Dado dado = item->dado;
        printf("Lista -- Endereço %p -- id: %i; Nome %s\n", item, dado.id, dado.nome);
        item = item->prox;
        i++;
    }
}

void adicionar(Lista *lista, Dado dado) {
    Item *item = lista;
        
    while (item->prox != NULL) {
        item = item->prox;
    }
    Item *novoItem = malloc(sizeof(*item));
    novoItem->ant = item;
    novoItem->prox = NULL;
    
    printf("item adicionado em %p %s\n", item, dado.nome);
    item->dado = dado;
    item->prox = novoItem;
}

int remover(Lista *lista, Dado dado) {
    Item *item = buscar(lista, dado);
    
    if (item->prox == NULL) {
        printf("Item não encontrado para remoção\n");
        return FALSE;
    }

    item->prox->ant = item->ant;

    if(item->ant != NULL) {
        item->ant->prox = item->prox;
    }
    else {
        *lista = *(item->prox);
    }
    
    free(item);
    
    return TRUE;
}

Item *buscar(Lista *item, Dado dado) {
    while (item->prox != NULL) {
        if (comparar_dado(item->dado, dado)) {
            return item;
        }
        else {
            item = item->prox;
        }
    }

    return item;
}
