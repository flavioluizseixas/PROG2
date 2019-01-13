#ifndef DADO_H
#define DADO_H

typedef struct {
    int id;             // identificador único
    char *nome;         // sizeof 8 bytes
    int idade;          // sizeof 4 bytes
    float altura;       // sizeof 4 bytes
    float peso;         // sizeof 4 bytes
} Dado;

typedef enum {FALSE = 0, TRUE} boolean;

int comparar_dado(Dado dado1, Dado dado2);

#endif /* DADO_H */

