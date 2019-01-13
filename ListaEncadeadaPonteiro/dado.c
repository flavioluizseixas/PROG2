#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "dado.h"

void visualizar_dado(Dado dado) {
    printf("Dado -- Nome: %s; Idade: %i\n", dado.nome, dado.idade);
}

int comparar_dado(Dado dado1, Dado dado2) {
    if (dado1.id == dado2.id) {
        return TRUE;
    }
    
    if (strcmp(dado1.nome, dado2.nome) == 0) {
        return TRUE;
    }

    return FALSE;
}