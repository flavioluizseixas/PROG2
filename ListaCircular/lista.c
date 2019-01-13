#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "dado.h"
#include "lista.h"

Lista *inicializar(Dado dado) {
    Lista *lista = malloc(sizeof(Item));
    lista->dado = dado;
    lista->ant = lista;
    lista->prox = lista;
    
    return lista;
};

void visualizar(Lista *item) {
    Item *itemInicial = item;
    do {
        Dado dado = item->dado;
        printf("Endereço %p, Anterior %p, Próximo %p -- id: %i; Nome %s\n", item, item->ant, item->prox, dado.id, dado.nome);
        item = item->prox;
    } while(memcmp(itemInicial, item, sizeof(Item)) != 0);
}

void adicionar(Lista *item, Dado dado) {
    Item *itemInicial = item;

    do {
        item = item->prox;
    } while(memcmp(itemInicial, item, sizeof(Item)) != 0);

    Item *novoItem = malloc(sizeof(Item));
    novoItem->dado = dado;
    novoItem->ant = item->ant;
    novoItem->prox = item;
    //printf("%p %p %p %s\n", novoItem, novoItem->ant, novoItem->prox, novoItem->dado.nome);
    
    item->ant->prox = novoItem;
    item->ant = novoItem;
}

void inserirDepoisDe(Lista *lista, Dado dado, Dado ref) {
    Item *item = buscar(lista, ref);
    //printf("Busca -- Endereço %p -- id: %i; Nome %s\n", item, dado.id, dado.nome);
    
    Item *novoItem = malloc(sizeof(Item));
    novoItem->dado = dado;
    novoItem->ant = item;
    novoItem->prox = item->prox;
    
    item->prox->ant = novoItem;
    item->prox = novoItem;
}

Lista *remover(Lista *lista, Dado ref) {
    Item *item = buscar(lista, ref);

    item->prox->ant = item->ant;
    item->ant->prox = item->prox;

    if(memcmp(lista, item, sizeof(Item)) == 0) {
        lista = item->prox;
    }

    free(item);

    return lista;
}

Item *buscar(Lista *item, Dado ref) {
    Item *itemInicial = item;

    do {
        if (comparar_dado(item->dado, ref)) {
            return item;
        }
        else {
            item = item->prox;
        }
    } while(memcmp(itemInicial, item, sizeof(Item)) != 0);

    return NULL;
}
