#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

int main(int argc, char** argv) {

    Dado dado;
    dado.id = 1;
    dado.nome = "Flavio";
    dado.altura = 1.82;
    dado.idade = 40;
    dado.peso = 80;
    Lista *lista = inicializar(dado);

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

    dado.id = 4;
    dado.nome = "Jose";
    dado.altura = 1.52;
    dado.idade = 24;
    dado.peso = 60;

    Dado ref;

    ref.id = 1;
    inserirDepoisDe(lista, dado, ref);
    printf("\n\nAdicionando depois de id = %i:\n", ref.id);
    visualizar(lista);

    lista = remover(lista, ref);
    printf("\n\nRemovendo id = %i:\n", ref.id);
    visualizar(lista);
    
    
    ref.id = 2;
    inserirDepoisDe(lista, dado, ref);
    printf("\n\nAdicionando depois de id = %i:\n", ref.id);
    visualizar(lista);

    lista = remover(lista, ref);
    printf("\n\nRemovendo id = %i:\n", ref.id);
    visualizar(lista);
    
    
    ref.id = 3;
    inserirDepoisDe(lista, dado, ref);
    printf("\n\nAdicionando depois de id = %i:\n", ref.id);
    visualizar(lista);

    lista = remover(lista, ref);
    printf("\n\nRemovendo id = %i:\n", ref.id);
    visualizar(lista);
    
    return 0;
}

