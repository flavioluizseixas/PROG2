#include <stdio.h>
#include <stdlib.h>

#include "item.h"
#include "lista.h"

Lista lista;

void inicializar_lista(int numero_de_elementos) {
    lista.item = malloc(sizeof(Item) * numero_de_elementos);
    lista.primeira_pos = 0;
    lista.ultima_pos = 0;
    lista.numero_de_elementos = numero_de_elementos;
}

void visualizar_lista() {
    for(int i = lista.primeira_pos; i < lista.ultima_pos; i++) {
        printf("%i. Nome: %s; Idade: %i\n", i, lista.item[i].nome, lista.item[i].idade);
    }
}

void adicionar_pilha(Item item) {
    lista.item[lista.ultima_pos] = item;
    lista.ultima_pos++;
}

Item remover_pilha() {
    lista.ultima_pos--;
    return lista.item[lista.ultima_pos];
}

void adicionar_fila(Item item) {
    lista.item[lista.ultima_pos] = item;
    lista.ultima_pos++;
}

Item remover_fila() {
    lista.primeira_pos++;
    return lista.item[lista.primeira_pos];
}
