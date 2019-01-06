#ifndef __PARAMETROS_H__
#define __PARAMETROS_H__

/**
 * Módulo parametros.h: provê estruturas de dados e funções
 * para a interpretação dos argumentos de linha de comando
 * do programa.
 */
#include "util.h"

/* 
 * Estrutura que armazena configurações do jogo com base 
 * nos parâmetros lidos da linha de comando.
 */
typedef struct {

    /*
     * String que contém caminho do arquivo a partir 
     * do qual estado do jogo deve ser restaurado. Se
     * opção de restauração não for especificada, esse
     * valor deve ser NULL.
     */
    char * restauraEstado;

    /*
     * Interface colorida será habilitada ou não? VERDADEIRO
     * ou FALSO, conforme definido em util.h.
     */
    int interfaceColorida;
} t_configuracao;

/**
 * Função que realiza a interpretação dos argumentos de linha
 * de comando e armazena o resultado em um t_configuracao.
 * Parâmetros:
 *  - argc: número de argumentos passados na linha de comando.
 *  - argv: vetor de strings contendo os argumentos de linha 
 * de comando.
 * Retorno:
 *  - Configuração resultante na forma de uma estrutura do
 * tipo t_configuracao.
 */
t_configuracao parametrosLeitura(int argc, char * argv[]);

#endif
