#include <stdio.h>
#include <stdlib.h>

#include "tabuleiro.h"
#include "util.h"

int tabuleiroTimeSemPecas(t_tabuleiro * tabuleiro) {

    /**
     * Basicamente, verificamos se ao menos uma das duas listas 
     * que armazenam as peças ainda em jogo de cada lado estão
     * vazias.
     */
    if (listaVazia(tabuleiro->listaPecasBrancas) == VERDADEIRO) return(VERDADEIRO);
    if (listaVazia(tabuleiro->listaPecasPretas) == VERDADEIRO) return(VERDADEIRO);

    /**
     * Se chegamos até aqui, ambas as listas ainda contêm ao 
     * menos uma peça. Logo, retornamos FALSO.
     */
    return(FALSO);
}

int tabuleiroNumeroDePecasEmJogo(t_tabuleiro * tabuleiro) {

    /**
     * Usamos a função de contagem do número de elementos de uma 
     * lista (módulo lista.h) para simplificar a implementação.
     */
    return(listaNumeroDeElementos(tabuleiro->listaPecasBrancas) + listaNumeroDeElementos(tabuleiro->listaPecasPretas));
}

void tabuleiroInicializaCasas(t_tabuleiro * tabuleiro) {

    int i, j, proximaCor;

    /*
     * Iteramos por todas as casas configurando as cores. Adotamos 
     * a convenção de que a posicao [0][0] da matriz corresponde 
     * ao canto superior esquerdo do tabuleiro e que essa casa é clara.
     */
    for (i = 0; i < 8; i++) {

        /* 
         * A primeira linha (0) começa por uma casa clara, a segunda
         * (1) por uma escura e assim por diante. Mais genericamente,
         * linhas pares tem a primeira casa clara e ímpares escura.
         */
        if (i % 2 == 0) {

            /*
             * Linha é par.
             */
            proximaCor = TABULEIRO_CASA_COR_CLARA;
        }
        else {

            /* 
             * Linha é ímpar.
             */
            proximaCor = TABULEIRO_CASA_COR_ESCURA;
        }


        for (j = 0; j < 8; j++) {

            /* 
             * Atribuição da cor ao tabuleiro. Cor correta já está
             * na variável proximaCor.
             */
            tabuleiro->casas[i][j].cor = proximaCor;

            /* 
             * Atualizar variável proximaCor para que a próxima 
             * casa dessa linha (se alguma) seja colorida de maneira 
             * correta.
             */
            if (proximaCor == TABULEIRO_CASA_COR_CLARA)
                proximaCor = TABULEIRO_CASA_COR_ESCURA;
            else 
                proximaCor = TABULEIRO_CASA_COR_CLARA;

            /*
             * Também inicializamos a ocupação das casas para NULL, 
             * indicando uma casa vazia.
             */
            tabuleiro->casas[i][j].ocupacao = NULL;
        }
    }
}

t_tabuleiro tabuleiroInicializa() {

    int i, j;
    t_tabuleiro tabuleiro;  // Novo tabuleiro a ser criado.
    t_peca * novaPeca;      // Ponteiro para auxiliar na criação de novas peças.

    /**
     * Inicializar as listas de peças em jogo (ainda vazias).
     */
    tabuleiro.listaPecasBrancas = listaInicializa();
    tabuleiro.listaPecasPretas = listaInicializa();

    /*
     * Inicializar cores das casas.
     */
    tabuleiroInicializaCasas(& tabuleiro);

    /*
     * Iterar por todas as casas configurando a ocupacao inicial.
     */
    for (i = 0; i < 8; i++) {

        for (j = 0; j < 8; j++) {

            /*
             * Preenchimento da casa: apenas casas escuras são
             * preenchidas.
             */
            if (tabuleiro.casas[i][j].cor == TABULEIRO_CASA_COR_ESCURA) {

                /*
                * Linhas 0 a 2 (inclusive) sao preenchidas com peças pretas
                * nas casas escuras. Linhas 5 a 7 (inclusive) com peças brancas
                * nas casas escuras. Todas as demais linhas contém apenas peças
                * vazias.
                */        
                if (i > 2 && i < 5) {

                    /**
                     * Estamos em uma das linhas medianas. Nada a fazer aqui.
                     */
                    continue ;
                }
                else {

                    /**
                     * Estamos em uma das linhas iniciais ou finais. Temos que
                     * criar uma nova peça.
                     */
                    novaPeca = (t_peca *) malloc(sizeof(t_peca));
                    if (novaPeca == NULL) {

                        printf("Falha ao alocar memoria!\n");
                        exit(1);
                    }
                    novaPeca->linha = i;
                    novaPeca->coluna = j;

                    if (i > 4) {

                        /**
                         * Linhas finais: peça branca.
                         */
                        novaPeca->cor = PECA_BRANCA;
                        novaPeca->tipo = PECA_NORMAL;

                        /**
                         * Adicionar à lista de peças brancas ainda em jogo.
                         */
                        listaAdiciona(& (tabuleiro.listaPecasBrancas), (void *) novaPeca);
                    }
                    else {

                        /**
                         * Linhas finais: peça branca.
                         */
                        novaPeca->cor = PECA_PRETA;
                        novaPeca->tipo = PECA_NORMAL;

                        /**
                         * Adicionar à lista de peças brancas ainda em jogo.
                         */
                        listaAdiciona(& (tabuleiro.listaPecasPretas), (void *) novaPeca);
                    }

                    /**
                     * Colocar a peça recém-criada no tabuleiro.
                     */
                    tabuleiro.casas[i][j].ocupacao = novaPeca;
                }
            }
        }
    }    

    /**
     * Tabuleiro preenchido é retornado.
     */
    return(tabuleiro);
}

