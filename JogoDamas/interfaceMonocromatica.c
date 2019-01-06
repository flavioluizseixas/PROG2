#include <stdio.h>
#include "interfaceMonocromatica.h"

/**
 * Constantes que definem os caracteres usados para representar 
 * casas claras e escuras do tabuleiro.
 */
#define INTERFACE_MONOCROMATICA_CARACTERE_CASA_ESCURA   '#'
#define INTERFACE_MONOCROMATICA_CARACTERE_CASA_CLARA   ' '

void interfaceMonocromaticaImprimeTabuleiro(t_tabuleiro tabuleiro) {

    char * stringCentro;
    int i, j;

    /* 
     * Imprimir as coordenadas do eixo X do tabuleiro. Servem como guia
     * para o usuário. Colunas são identificadas por caracteres de 'a' a
     * 'h'.
     */
    printf(" ");
    for (i = 0; i < 8; i++){
        printf("   %c   ", 'a' + i);
    }
    printf("\n");

    /* 
     * Colocaremos uma espécie de moldura em volta do tabuleiro. Aqui,
     * colocamos a parte de cima. São 58 caracteres porque cada casa do
     * tabuleiro tem 7 caracteres de largura, enquanto a moldura tem 1
     * de cada lado.
     */
    for (i = 0; i < 58; i++) {
        
        printf("-");
    }
    printf("\n");

    /*
     * Iterar por todas as casas imprimindo o estado de cada uma.
     * Na tela, cada casa ocupa um bloco de 3x7 caracteres: casas
     * claras são representadas pelo caractere ' ' (espaço), enquanto
     * as escuras são representadas pelo caractere '#' (tralha). 
     * Se a casa ocupada, o caractere do meio é substituido por 'o' 
     * (peça preta normal), 'O' (dama preta), 'x' (peça branca normal)
     * ou 'X' (dama branca).
     */
    for (i = 0; i < 8; i++) {

        /*
         * Temos que trabalhar com a impressão das linhas na exata 
         * sequência em que elas apareceram na tela. Assim, temos
         * que começar imprimindo o topo de cada casa, seguido do 
         * centro e, finalmente, da base.
         */

        /*
         * Caractere de moldura.
         */
        printf("|");

        /*
         * Topo das casas.
         */
        for (j = 0; j < 8; j++) {

            if (tabuleiro.casas[i][j].cor == TABULEIRO_CASA_COR_CLARA) {

                printf("%c%c%c%c%c%c%c", INTERFACE_MONOCROMATICA_CARACTERE_CASA_CLARA, 
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_CLARA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_CLARA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_CLARA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_CLARA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_CLARA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_CLARA);
            }
            else {

                printf("%c%c%c%c%c%c%c", INTERFACE_MONOCROMATICA_CARACTERE_CASA_ESCURA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_ESCURA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_ESCURA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_ESCURA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_ESCURA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_ESCURA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_ESCURA);
            }
        }
        /*
         * Caractere de moldura e final da linha.
         */
        printf("|\n");

        /*
         * Caractere de moldura da próxima linha.
         */
        printf("|");

        /*
         * Linha do centro.
         */
        for (j = 0; j < 8; j++) {

            if (tabuleiro.casas[i][j].cor == TABULEIRO_CASA_COR_CLARA) {

                printf("%c%c%c%c%c%c%c", INTERFACE_MONOCROMATICA_CARACTERE_CASA_CLARA, 
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_CLARA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_CLARA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_CLARA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_CLARA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_CLARA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_CLARA);
            }
            else {

                /*
                 * Essa casa é escura e estamos imprimindo a linha do 
                 * meio. O caractere a ser impresso depende de se a casa
                 * está vazia e, se está cheia, de qual tipo de peça se
                 * encontra lá.
                 */
                if (tabuleiro.casas[i][j].ocupacao == NULL) {

                    stringCentro = "###";
                }
                else {

                    if (tabuleiro.casas[i][j].ocupacao->cor == PECA_BRANCA) {

                        if (tabuleiro.casas[i][j].ocupacao->tipo == PECA_NORMAL) {
                        
                            stringCentro = " x ";
                        }
                        else {

                            stringCentro = " X ";
                        }
                    }
                    else {

                        if (tabuleiro.casas[i][j].ocupacao->tipo == PECA_NORMAL) {

                            stringCentro = " o ";
                        }
                        else {

                            stringCentro = " O ";
                        }
                    }
                }
                printf("%c%c%s%c%c", INTERFACE_MONOCROMATICA_CARACTERE_CASA_ESCURA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_ESCURA,
                                stringCentro,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_ESCURA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_ESCURA);
            }
        }

        /*
         * Caractere de moldura, coordenada Y e final da linha.
         * A coordenada Y compreende números de 1 a 8.
         */
        printf("| %d\n", i + 1);

        /*
         * Caractere de moldura da próxima linha.
         */
        printf("|");

        /* 
         * Linha da base.
         */
        for (j = 0; j < 8; j++) {

            if (tabuleiro.casas[i][j].cor == TABULEIRO_CASA_COR_CLARA) {

                printf("%c%c%c%c%c%c%c", INTERFACE_MONOCROMATICA_CARACTERE_CASA_CLARA, 
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_CLARA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_CLARA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_CLARA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_CLARA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_CLARA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_CLARA);
            }
            else {

                printf("%c%c%c%c%c%c%c", INTERFACE_MONOCROMATICA_CARACTERE_CASA_ESCURA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_ESCURA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_ESCURA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_ESCURA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_ESCURA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_ESCURA,
                                INTERFACE_MONOCROMATICA_CARACTERE_CASA_ESCURA);
            }
        }

        /*
         * Caractere de moldura e final da linha.
         */
        printf("|\n");
    }

    /*
     * Base da moldura.
     */
    for (i = 0; i < 58; i++) {
        
        printf("-");
    }
    printf("\n");
}
