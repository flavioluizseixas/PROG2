#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

int main(int argc, char** argv) {

    Lista *lista = inicializar(20);
    
    Dado dado;
    dado.id = 1;
    dado.nome = "Flavio";
    dado.altura = 1.82;
    dado.idade = 40;
    dado.peso = 80;
    adicionar(lista, dado);

    dado.id = 2;
    dado.nome = "Luiz";
    dado.altura = 1.82;
    dado.idade = 40;
    dado.peso = 80;
    adicionar(lista, dado);
    
    dado.id = 3;
    dado.nome = "Seixas";
    dado.altura = 1.42;
    dado.idade = 46;
    dado.peso = 87;
    adicionar(lista, dado);
    
    visualizar(lista);
    
    Dado dado_removido;
    printf("\nRemovendo item da pilha\n");
    dado_removido = remover_pilha(lista);
    visualizar(lista);

    printf("\nRemovendo item da pilha\n");
    dado_removido = remover_pilha(lista);
    visualizar(lista);

    printf("\nRemovendo item da pilha\n");
    dado_removido = remover_pilha(lista);
    visualizar(lista);
    
    printf("\n-----------------------\n");
    
    dado.id = 1;
    dado.nome = "Flavio";
    dado.altura = 1.82;
    dado.idade = 40;
    dado.peso = 80;
    adicionar(lista, dado);

    dado.id = 2;
    dado.nome = "Luiz";
    dado.altura = 1.82;
    dado.idade = 40;
    dado.peso = 80;
    adicionar(lista, dado);
    
    dado.id = 3;
    dado.nome = "Seixas";
    dado.altura = 1.42;
    dado.idade = 46;
    dado.peso = 87;
    adicionar(lista, dado);
    
    visualizar(lista);
        
    printf("\nRemovendo item da fila\n");
    dado_removido = remover_fila(lista);
    visualizar(lista);

    printf("\nRemovendo item da fila\n");
    dado_removido = remover_fila(lista);
    visualizar(lista);

    printf("\nRemovendo item da fila\n");
    dado_removido = remover_fila(lista);
    visualizar(lista);

    return 0;
}

