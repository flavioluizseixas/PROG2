#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

int main(int argc, char** argv) {

    inicializar_lista(20);
    
    Item item;
    item.nome = "Flavio";
    item.altura = 1.82;
    item.idade = 40;
    item.peso = 80;
    adicionar_pilha(item);

    item.nome = "Luiz";
    item.altura = 1.66;
    item.idade = 30;
    item.peso = 20;
    adicionar_pilha(item);
    
    item.nome = "Seixas";
    item.altura = 1.66;
    item.idade = 30;
    item.peso = 20;
    adicionar_pilha(item);
    visualizar_lista();
    
    printf("\nRemovendo item da pilha\n");
    item = remover_pilha();
    visualizar_lista();

    printf("\nRemovendo item da pilha\n");
    item = remover_pilha();
    visualizar_lista();

    printf("\nRemovendo item da pilha\n");
    item = remover_pilha();
    visualizar_lista();
    
    printf("\n-----------------------\n");
    
    item.nome = "Flavio";
    item.altura = 1.82;
    item.idade = 40;
    item.peso = 80;
    adicionar_fila(item);

    item.nome = "Luiz";
    item.altura = 1.66;
    item.idade = 30;
    item.peso = 20;
    adicionar_fila(item);
    
    item.nome = "Seixas";
    item.altura = 1.66;
    item.idade = 30;
    item.peso = 20;
    adicionar_fila(item);
    visualizar_lista();
    
    printf("\nRemovendo item da fila\n");
    item = remover_fila();
    visualizar_lista();

    printf("\nRemovendo item da fila\n");
    item = remover_fila();
    visualizar_lista();

    printf("\nRemovendo item da fila\n");
    item = remover_fila();
    visualizar_lista();

    return 0;
}

