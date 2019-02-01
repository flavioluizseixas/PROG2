#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

int main(void) {

    Lista *lista = inicializar_lista(20);
    
    Dado dado;
    dado.id = 1;
    dado.nome = "Flavio";
    dado.altura = 1.82;
    dado.idade = 40;
    dado.peso = 80;
    adicionar_na_lista(lista, dado);

    dado.id = 2;
    dado.nome = "Luiz";
    dado.altura = 1.82;
    dado.idade = 40;
    dado.peso = 80;
    adicionar_na_lista(lista, dado);
    
    dado.id = 3;
    dado.nome = "Seixas";
    dado.altura = 1.42;
    dado.idade = 46;
    dado.peso = 87;
    adicionar_na_lista(lista, dado);
    
    visualizar_lista(lista);
    
    Dado dado_removido;
    printf("\nRemovendo item da pilha\n");
    dado_removido = remover_da_pilha(lista);
    visualizar_lista(lista);

    printf("\nRemovendo item da pilha\n");
    dado_removido = remover_da_pilha(lista);
    visualizar_lista(lista);

    printf("\nRemovendo item da pilha\n");
    dado_removido = remover_da_pilha(lista);
    visualizar_lista(lista);
    
    printf("\n-----------------------\n");
    
    dado.id = 1;
    dado.nome = "Flavio";
    dado.altura = 1.82;
    dado.idade = 40;
    dado.peso = 80;
    adicionar_na_lista(lista, dado);

    dado.id = 2;
    dado.nome = "Luiz";
    dado.altura = 1.82;
    dado.idade = 40;
    dado.peso = 80;
    adicionar_na_lista(lista, dado);
    
    dado.id = 3;
    dado.nome = "Seixas";
    dado.altura = 1.42;
    dado.idade = 46;
    dado.peso = 87;
    adicionar_na_lista(lista, dado);
    
    visualizar_lista(lista);
        
    printf("\nRemovendo item da fila\n");
    dado_removido = remover_da_fila(lista);
    visualizar_lista(lista);

    printf("\nRemovendo item da fila\n");
    dado_removido = remover_da_fila(lista);
    visualizar_lista(lista);

    printf("\nRemovendo item da fila\n");
    dado_removido = remover_da_fila(lista);
    visualizar_lista(lista);

    return 0;
}