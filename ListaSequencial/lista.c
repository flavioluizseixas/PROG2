#include <stdio.h>
#include <stdlib.h>

#include "dado.h"
#include "lista.h"

Lista *inicializar_lista(int numero_de_elementos) {
    Lista *lista = malloc(sizeof(Lista));
    lista->vetor_de_dados = malloc(sizeof(Dado) * numero_de_elementos);
    lista->primeira_pos = 0;
    lista->ultima_pos = 0;
    lista->numero_de_elementos = numero_de_elementos;
    
    return lista;
}

void liberar_lista(Lista *lista) {
    free(lista->vetor_de_dados);
    free(lista);
}

void visualizar_lista(Lista *lista) {
    int i = lista->primeira_pos;
    
    while(i != lista->ultima_pos) {
        printf("Índice %i. id: %i; Nome: %s\n", i, lista->vetor_de_dados[i].id, lista->vetor_de_dados[i].nome);
        i++;
        i = i % lista->numero_de_elementos;
    }

}

void adicionar_na_lista(Lista *lista, Dado dado) {
    lista->vetor_de_dados[lista->ultima_pos] = dado;
    
    lista->ultima_pos++;
    lista->ultima_pos = lista->ultima_pos % lista->numero_de_elementos;
}

Dado remover_da_pilha(Lista *lista) {
    if (lista->ultima_pos == 0)
        lista->ultima_pos = lista->numero_de_elementos;

    lista->ultima_pos--;
    return lista->vetor_de_dados[lista->ultima_pos];
}

Dado remover_da_fila(Lista *lista) {
    lista->primeira_pos++;
    lista->primeira_pos = lista->primeira_pos % lista->numero_de_elementos;

    return lista->vetor_de_dados[lista->primeira_pos];
}
