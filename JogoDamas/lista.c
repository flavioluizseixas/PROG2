#include "lista.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>

int listaVazia(t_lista lista) {

    /**
     * Como a lista mantém a propriedade do número de elementos,
     * podemos simplesmente compará-lo a zero para testar se a 
     * lista é vazia.
     */
    if (lista.numeroDeElementos == 0) return(VERDADEIRO);
    else return(FALSO);
}

int listaNumeroDeElementos(t_lista lista) {

    /**
     * Como a lista mantém a propriedade do número de elementos,
     * podemos simplesmente retorná-lo.
     */
    return(lista.numeroDeElementos);
}

t_lista listaInicializa() {

    t_lista lista; // Lista local, usada para configurar valores iniciais.

    /**
     * Configuramos todos os ponteiros para NULL e o número de elementos
     * para 0.
     */
    lista.primeiro = NULL;
    lista.ponteiro = NULL;
    lista.numeroDeElementos = 0;

    /**
     * Retornamos a lista preenchida.
     */
    return(lista);
}

void listaAdiciona(t_lista * lista, void * dado) {

    t_noLista * ponteiro, * novoNo;

    /**
     * Começamos alocando memória para um novo nó e preenchendo-o
     * com o ponteiro para o dado a ser inserido. Além disso,
     * como esse nó será inserido no final da fila, configuramos
     * o ponteiro para o próximo para apontar para NULL.
     */
    novoNo = (t_noLista *) malloc(sizeof(t_noLista));
    if (novoNo == NULL) {

        printf("Falha ao alocar memoria!\n");
        exit(1);
    }
    novoNo->dado = dado;
    novoNo->proximo = NULL;

    /**
     * Há dois casos:
     * 1) A lista está vazia: esse caso é trivial; podemos simplesmente
     * fazer o ponteiro primeiro da lista apontar para o novo nó.
     */
    if (lista->primeiro == NULL) {

        lista->primeiro = novoNo;
    }
    else {

        /**
         * 2) A lista já contém outros elementos. Iteramos pelos elementos
         * em busca do último.
         */
        ponteiro = lista->primeiro;
        while(ponteiro->proximo != NULL) {

            ponteiro = ponteiro->proximo;
        }

        /**
         * Nesse ponto, ponteiro aponta para o último elemento atualmente
         * na lista. Assim, basta apontarmos sua propriedade proximo para 
         * o novo nó da lista.
         */
        ponteiro->proximo = novoNo;
    }

    /**
     * Acabamos de inserir um novo nó na lista. Incrementamos o contador
     * de elementos na lista.
     */
    lista->numeroDeElementos++;
}

void listaRemove(t_lista * lista, void * dado) {

    t_noLista * ponteiro, * noRemovido;

    /** 
     * Se a lista está vazia, não há o que remover. Simplesmente
     * retornamos.
     */
    if (lista->primeiro == NULL) return;

    /**
     * Dois casos:
     * 
     * 1) dado está no primeiro nó da lista.
     */
    if (dado == lista->primeiro->dado) {

        /**
         * Nesse caso, basta mudar o ponteiro do primeiro elemento
         * da lista para apontar para o segundo. Também guardamos
         * em um ponteiro local da função o endereço do nó removido
         * para processamento posterior.
         */
        noRemovido = lista->primeiro;
        lista->primeiro = lista->primeiro->proximo;
    }
    else {

        /**
         * 2) Dado está em algum outro ponto da lista. Precisamos 
         * iterar pelos elementos buscando o dado. Nessa busca,
         * precisamos manter sempre um ponteiro para o nó anterior
         * ao do elemento buscado.
         */
        ponteiro = lista->primeiro;
        while (ponteiro->proximo->dado != dado) {

            ponteiro = ponteiro->proximo;
        }

        /**
         * Nó a ser removido está apontado por ponteiro->proximo.
         */
        noRemovido = ponteiro->proximo;

        /**
         * Para removê-lo, fazemos ponteiro->proximo apontar para 
         * noRemovido->proximo.
         */
        ponteiro->proximo = noRemovido->proximo;
    }

    /**
     * Liberamos a memória do nó removido.
     */
    free(noRemovido);

    /**
     * Decrementamos o número de elementos da lista.
     */
    lista->numeroDeElementos--;

    /**
     * Para evitar qualquer tipo de inconsistência, anulamos o 
     * ponteiro de iteração da lista.
     */
    lista->ponteiro = NULL;
}

void listaLiberaMemoria(t_lista * lista) {

    t_noLista * ponteiro;

    /**
     * Varremos a lista elemento a elemento.
     */
    while(lista->primeiro) {

        /**
         * Guardamos o endereço do primeiro nó da lista em um 
         * ponteiro local.
         */
        ponteiro = lista->primeiro;

        /**
         * Avançamos o ponteiro para o início da lista para o 
         * próximo nó.
         */
        lista->primeiro = lista->primeiro->proximo;

        /**
         * Liberamos a memória associada ao antigo primeiro nó 
         * da lista.
         */
        free(ponteiro);
    }

    /** 
     * Lista agora está vazia. Portanto zeramos tanto o contador
     * de elementos, quanto o ponteiro para iteração.
     */
    lista->numeroDeElementos = 0;
    lista->ponteiro = NULL;
}

void * listaPrimeiro(t_lista * lista) {

    /**
     * Inicializamos o ponteiro de iteração para apontar para o 
     * primeiro nó da lista.
     */
    lista->ponteiro = lista->primeiro;

    /**
     * Se esse primeiro nó não é nulo, retornamos um ponteiro 
     * para os dados. Caso contrário, retornamos NULL.
     */
    if (lista->ponteiro != NULL)
        return(lista->ponteiro->dado);
    else 
        return(NULL);
}

void * listaProximo(t_lista * lista) {

    /**
     * Se o ponteiro de iteração da lista é nulo, então o próximo
     * nó na iteração não está definido.
     */
    if (lista->ponteiro == NULL)
        return(NULL);

    /**
     * Caso contrário, avançamos o ponteiro de iteração para o 
     * próximo nó.
     */
    lista->ponteiro = lista->ponteiro->proximo;

    /**
     * Se esse nó não é nulo, retornamos um ponteiro 
     * para os dados. Caso contrário, retornamos NULL.
     */
    if (lista->ponteiro != NULL)
        return(lista->ponteiro->dado);
    else 
        return(NULL);
}