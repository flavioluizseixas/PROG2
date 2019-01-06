#ifndef __LISTA_H__
#define __LISTA_H__

/**
 * Módulo lista.h: definição de estruturas de dados e funções que 
 * implementam listas encadeadas. A lista implementada por esse módulo
 * é genérica, no sentido de que pode armazenar qualquer tipo de 
 * informação. Assim, essa mesma implementação de lista encadeada é
 * usada no programa em vários contextos diferentes, armazenando 
 * vários tipos distintos de dados.
 */

/** 
 * Definição de uma estrutura que representa um nó da lista
 * encadeada.
 */
typedef struct t_noLista {

    /**
     * Ponteiro para o dado a ser armazenado nesse nó da lista.
     * Usamos um tipo (void *) (ponteiro para void), como um coringa
     * permitindo que a lista armazene qualquer tipo de dado. Isso
     * permite armazenar ponteiros para qualquer outro tipo dentro
     * do programa.
     */
    void * dado;

    /**
     * Ponteiro para o próximo nó da lista.
     */
    struct t_noLista * proximo;
} t_noLista;

/**
 * Definição de uma estrutura que representa a lista encadeada.
 * Essa estrutura armazena um ponteiro para o início da lista,
 * além de um contador de elementos e um outro ponteiro para
 * dar suporte a iteração na lista (mais detalhes nas funções
 * listaProximo() e listaPrimeiro()).
 */
typedef struct {

    /**
     * Ponteiro para o início da lista.
     */
    t_noLista * primeiro;

    /**
     * Número de elementos atualmente na lista. Guardamos esse
     * valor para simplicar consultas ao número de elementos 
     * da lista.
     */
    int numeroDeElementos;

    /**
     * Ponteiro que dá suporte às funções de iteração sobre a lista
     * (funções listaPrimeiro() e listaProximo()). Em particular,
     * esse ponteiro aponta para o elemento atual da iteração.
     */
    t_noLista * ponteiro;
} t_lista;

/**
 * Função que verifica se a lista está vazia.
 * 
 * Parâmetros:
 *  - lista: uma lista encadeada.
 * 
 * Retorno: VERDADEIRO, se a lista está vazia, ou FALSO, se a lista
 * possui elementos.
 */
int listaVazia(t_lista lista);

/**
 * Função que retorna o número de elementos atualmente na lista.
 * 
 * Parâmetros:
 *  - lista: uma lista encadeada.
 * 
 * Retorno: número de elementos atualmente na lista.
 */
int listaNumeroDeElementos(t_lista lista);

/**
 * Função que inicializa uma nova lista vazia.
 * 
 * Parâmetros: nenhum.
 * 
 * Retorno: uma nova lista vazia.
 */
t_lista listaInicializa();

/**
 * Função que adiciona um novo elemento à lista.
 * 
 * Parâmetros:
 *  - lista: ponteiro para uma lista encadeada.
 *  - dado: ponteiro para o dado a ser inserido na lista.
 * 
 * Retorno: nenhum.
 */
void listaAdiciona(t_lista * lista, void * dado);

/**
 * Função que remove um elemento da lista.
 * 
 * Parâmetros:
 *  - lista: ponteiro para uma lista encadeada.
 *  - dado: ponteiro para o dado a ser removido da lista.
 * 
 * Retorno: nenhum.
 */
void listaRemove(t_lista * lista, void * dado);

/**
 * Função que libera a memória associada a uma lista. Repare
 * que essa função libera apenas a memória alocada para os nós
 * da lista (do tipo t_noLista), não liberando memória alocada
 * ao dado em si.
 * 
 * Parâmetros:
 *  - lista: ponteiro para uma lista encadeada.
 * 
 * Retorno: nenhum.
 */
void listaLiberaMemoria(t_lista * lista);

/**
 * Função que retorna o primeiro nó da lista e atualiza o 
 * ponteiro de iteração da lista para apontar para esse primeiro
 * nó.
 * 
 * Parâmetros:
 *  - lista: ponteiro para uma lista encadeada.
 * 
 * Retorno: ponteiro para os dados do primeiro elemento da lista.
 */
void * listaPrimeiro(t_lista * lista);

/**
 * Função que retorna que avança o ponteiro de iteração da lista 
 * para apontar para o próximo elemento e retorna esse elemento.
 * 
 * Parâmetros:
 *  - lista: ponteiro para uma lista encadeada.
 * 
 * Retorno: ponteiro para os dados do próximo elemento da lista.
 */
void * listaProximo(t_lista * lista);

#endif