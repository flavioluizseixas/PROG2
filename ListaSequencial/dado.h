#ifndef DADO_H
#define DADO_H

typedef struct {
    int id;             // identificador único
    char *nome;         // sizeof 8 bytes
    int idade;          // sizeof 4 bytes
    float altura;       // sizeof 4 bytes
    float peso;         // sizeof 4 bytes
} Dado;

#endif /* DADO_H */

