#ifndef __TABULEIRO_H__
#define __TABULEIRO_H__

#include "lista.h"

/**
 * Módulo tabuleiro.h. Define estruturas de dados para 
 * representação do tabuleiro e funções para manipulá-las.
 */


/**
 * Constantes que definem as cores de uma peça.
 */
typedef enum {

    PECA_BRANCA,
    PECA_PRETA
} t_corPeca;

/** 
 * Constantes que definem o tipo de uma peça: dama ou não.
 */
typedef enum {

    PECA_NORMAL,
    PECA_DAMA
} t_tipoPeca;

/** 
 * Estrutura que representa uma peça no tabuleiro.
 */
typedef struct {

    /**
     * Número da linha do tabuleiro na qual peça está
     * localizada.
     */
    int linha;

    /**
     * Número da coluna do tabuleiro na qual peça está
     * localizada.
     */
    int coluna;

    /**
     * Informação do tipo da peça (dama ou não).
     */
    t_tipoPeca tipo;

    /**
     * Informação da cor da peça: branca ou preta.
     */
    t_corPeca cor;
} t_peca;

/*
 * Constantes que definem a cor de uma casa: escura
 * ou clara.
 */
typedef enum {

    TABULEIRO_CASA_COR_CLARA,
    TABULEIRO_CASA_COR_ESCURA
} t_tabuleiroCasaCor;

/*
 * Definição do tipo tabuleiro. Contém uma matriz 8x8 
 * de casas e listas de peças brancas e pretas ainda 
 * em jogo.
 */
typedef struct {

    struct {

        /*
         * Cor da casa do tabuleiro.
         */
        t_tabuleiroCasaCor cor;

        /*
         * Ocupacao atual da casa. Ponteiro para um 
         * dos nós de uma das listas de peças ou NULL se 
         * a casa está vazia.
         */
        t_peca * ocupacao;

    } casas[8][8];

    /**
     * Lista das peças brancas ainda em jogo.
     */
    t_lista listaPecasBrancas;

    /**
     * Lista da peças pretas ainda em jogo.
     */
    t_lista listaPecasPretas;
} t_tabuleiro;

/**
 * Função que verifica se um dos dois times está sem peças
 * em jogo (ou seja, se perdeu o jogo).
 * 
 * Parâmetros:
 *  - tabuleiro: ponteiro para uma estrutura do tipo tabuleiro.
 * 
 * Retorno: VERDADEIRO, caso um dos dois times esteja sem peças,
 * FALSO, caso contrário.
 */
int tabuleiroTimeSemPecas(t_tabuleiro * tabuleiro);

/**
 * Função que retorna o número total de peças ainda em jogo (
 * considerando ambos os lados).
 * 
 * Parâmetros:
 *  - tabuleiro: ponteiro para uma estrutura do tipo tabuleiro.
 * 
 * Retorno: soma do número de peças ainda em jogo para as brancas
 * e para as pretas.
 */
int tabuleiroNumeroDePecasEmJogo(t_tabuleiro * tabuleiro);

/**
 * Função que inicializa as casas de um tabuleiro. As cores 
 * das casas são configuradas para os valores apropriados e
 * a ocupação de cada casa é iniciada para NULL.
 * 
 * Parâmetros:
 *  - tabuleiro: ponteiro para uma estrutura do tipo tabuleiro.
 * 
 * Retorno: nenhum.
 */
void tabuleiroInicializaCasas(t_tabuleiro * tabuleiro);

/**
 * Função que cria um novo tabuleiro, já inicializado. Isso inclui
 * tanto as cores das casas, quanto suas ocupações com as peças
 * pretas e brancas em suas casas iniciais. Listas de peças em jogo
 * para ambos os lados também são inicializadas de acordo.
 * 
 * Parâmetros: nenhum.
 * 
 * Retorno: estrutura do tipo t_tabuleiro complemente inicializada
 * para o início da partida.
 */
t_tabuleiro tabuleiroInicializa();

#endif