#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

int main(int argc, char** argv) {

    Lista lista;
    inicializar(&lista);
    printf("%p\n", &lista);
    
    Dado dado;
    dado.id = 1;
    dado.nome = "Flavio";
    dado.altura = 1.82;
    dado.idade = 40;
    dado.peso = 80;
    adicionar(&lista, dado);

    dado.id = 2;
    dado.nome = "Luiz";
    dado.altura = 1.66;
    dado.idade = 30;
    dado.peso = 20;
    adicionar(&lista, dado);

    visualizar(lista);

    Dado dado_pesquisado;
    //dado_pesquisado.id = 2;
    dado_pesquisado.nome = "Flavio";
    
    Item item = buscar(lista, dado_pesquisado);
    printf("Item encontrado: %i %s", item.dado.id, item.dado.nome);
    
    return 0;
}

