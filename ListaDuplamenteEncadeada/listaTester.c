#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

int main(int argc, char** argv) {

    Lista *lista = inicializar();

    Dado dado;
    dado.id = 1;
    dado.nome = "Flavio";
    dado.altura = 1.82;
    dado.idade = 40;
    dado.peso = 80;
    adicionar(lista, dado);

    dado.id = 2;
    dado.nome = "Luiz";
    dado.altura = 1.66;
    dado.idade = 30;
    dado.peso = 20;
    adicionar(lista, dado);

    dado.id = 3;
    dado.nome = "Seixas";
    dado.altura = 1.56;
    dado.idade = 20;
    dado.peso = 50;
    adicionar(lista, dado);
    
    visualizar(lista);

    Dado ref;
    ref.nome = "Flavio";
    lista = remover(lista, ref);

    printf("\nApós remoção de %s:\n", ref.nome);
    visualizar(lista);
    
    return 0;
}

