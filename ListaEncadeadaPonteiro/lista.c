#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "dado.h"
#include "lista.h"

void inicializar(Lista *lista) {
    lista->prox = NULL;
};

void visualizar(Lista lista) {
    int i = 0;
    Item item = lista;
    while (item.prox != NULL) {
        Dado dado = item.dado;
        printf("Lista -- Posição %i -- Nome: %s; Idade %i\n", i, dado.nome, dado.idade);
        item = *item.prox;
        i++;
    }
}

void adicionar(Lista *lista, Dado dado) {
    Item *item = lista;
    //printf("sizeof(dado):%i, sizeof(nome):%i, sizeof(idade):%i, sizeof(altura):%i, sizeof(peso):%i, , sizeof(imc):%i \n", sizeof(item->dado), sizeof(item->dado.nome), sizeof(item->dado.idade), sizeof(item->dado.altura), sizeof(item->dado.peso), sizeof(item->dado.imc));
    //printf("sizeof(item):%i\n", sizeof(*item));
        
    while (item->prox != NULL) {
        item = item->prox;
    }
    Item *novoItem = (Item *)malloc(sizeof(*item));
    novoItem->prox = NULL;
    item->dado = dado;
    item->prox = novoItem;
}

Item buscar(Lista lista, Dado dado) {
    Item item = lista;

    while (item.prox != NULL) {
        if (comparar_dado(item.dado, dado)) {
            return item;
        }
        else {
            item = *item.prox;
        }
    }

    return item;
}
