#include <stdio.h>
#include <stdlib.h>

#include "dado.h"
#include "lista.h"

Lista lista;

Lista *inicializar(int numero_de_elementos) {
    Lista *lista = malloc(sizeof(Lista));
    lista->vetor_de_dados = malloc(sizeof(Dado) * numero_de_elementos);
    lista->primeira_pos = 0;
    lista->ultima_pos = 0;
    lista->numero_de_elementos = numero_de_elementos;
    
    return lista;
}

void visualizar(Lista *lista) {
    for(int i = lista->primeira_pos; i < lista->ultima_pos; i++) {
        printf("%i. id: %i; Nome: %s\n", i, lista->vetor_de_dados[i].id, lista->vetor_de_dados[i].nome);
    }
}

void adicionar(Lista *lista, Dado dado) {
    lista->vetor_de_dados[lista->ultima_pos] = dado;
    lista->ultima_pos++;
}

Dado remover_pilha(Lista *lista) {
    lista->ultima_pos--;
    return lista->vetor_de_dados[lista->ultima_pos];
}

Dado remover_fila(Lista *lista) {
    lista->primeira_pos++;
    return lista->vetor_de_dados[lista->primeira_pos];
}
