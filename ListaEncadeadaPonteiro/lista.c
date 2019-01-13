#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "dado.h"
#include "lista.h"

Lista *inicializar() {
    Lista *lista = malloc(sizeof(Item));
    lista->prox = NULL;
    
    return lista;
};

void visualizar(Lista *item) {
    int i = 0;
    while (item->prox != NULL) {
        Dado dado = item->dado;
        printf("Endereço %p, Próximo %p -- id: %i; Nome %s\n", item, item->prox, dado.id, dado.nome);
        item = item->prox;
        i++;
    }
}

void adicionar(Lista *lista, Dado dado) {
    Item *item = lista;
        
    while (item->prox != NULL) {
        item = item->prox;
    }
    Item *novoItem = malloc(sizeof(Item));
    novoItem->prox = NULL;
    
    item->dado = dado;
    item->prox = novoItem;
}

Item *buscar(Lista *lista, Dado dado) {
    Item *item = lista;

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
