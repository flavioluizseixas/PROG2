#ifndef ITEM_H
#define ITEM_H

typedef struct {
    char *nome;
    int idade;
    float altura;
    float peso;
} Item;

void visualizar_item(Item item);

#endif /* ITEM_H */

