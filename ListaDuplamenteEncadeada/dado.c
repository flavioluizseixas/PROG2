#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "dado.h"

int comparar_dado(Dado dado1, Dado dado2) {
    if (dado1.id == dado2.id) {
        return TRUE;
    }
    
    if (strcmp(dado1.nome, dado2.nome) == 0) {
        return TRUE;
    }

    return FALSE;
}