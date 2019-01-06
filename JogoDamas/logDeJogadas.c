#include "logDeJogadas.h"
#include "jogada.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_logDeJogadas logDeJogadasInicializa() {

    /**
     * A função é basicamente um apelido para a função de
     * inicialização de listas do módulo lista.h.
     */
    return(listaInicializa());
}

void logDeJogadasAdiciona(t_logDeJogadas * logDeJogadas, char * novaJogada) {

    char * copiaNovaJogada;

    /**
     * Criamos uma cópia da string para evitar que alterações na string
     * do chamador alterem o conteúdo da jogada guardada no log.
     */
    copiaNovaJogada = (char *) malloc(strlen(novaJogada) + 1);
    if (copiaNovaJogada == NULL) {

        printf("Falha ao alocar memoria!\n");
        exit(1);
    }
    strcpy(copiaNovaJogada, novaJogada);

    /**
     * Adicionamos a string recém-criada no log.
     */
    listaAdiciona(logDeJogadas, copiaNovaJogada);
}

int logDeJogadasSalvaEmArquivo(t_logDeJogadas * logDeJogadas, char * nomeDoArquivo) {

    FILE * arquivo;     // Ponteiro para o arquivo a ser manipulado.
    int vez;            // Vez de cada jogada no log.
    char * vezString;   // Variável auxiliar para ajudar na impressão da cor das peças com a vez.
    char * ponteiro;    // Ponteiro para iterar pelas jogadas do log.

    /**
     * Abrimos o arquivo para escrita ("w").
     */
    arquivo = fopen(nomeDoArquivo, "w");
    if (arquivo == NULL) {

        return(FALSO);
    }

    /**
     * Inicializamos a vez com as brancas, de acordo com as regras do
     * jogo.
     */
    vez = VEZ_BRANCAS;

    /**
     * Começamos a iterar pelas jogadas do log, a partir da primeira.
     */
    ponteiro = listaPrimeiro(logDeJogadas);
    while(ponteiro) {

        /**
         * Configurar a variável vezString de acordo com a variável vez.
         */
        if (vez == VEZ_BRANCAS) vezString = "brancas";
        else vezString = "pretas";

        /**
         * Escrevemos no arquivo texto a descrição textual da jogada.
         */
        fprintf(arquivo, "Movimento das pecas %s -> %s\n", vezString, ponteiro);

        /**
         * Continuamos a iteração com a próxima jogada do log.
         */
        ponteiro = listaProximo(logDeJogadas);

        /**
         * Alternamos o valor da variável vez.
         */
        if (vez == VEZ_BRANCAS) vez = VEZ_PRETAS;
        else vez = VEZ_BRANCAS;
    }

    /**
     * Fechamos o arquivo.
     */
    fclose(arquivo);

    return(VERDADEIRO);
}