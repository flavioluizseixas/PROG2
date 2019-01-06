#ifndef __ESTADO_H__
#define __ESTADO_H__

#include "tabuleiro.h"
#include "logDeJogadas.h"

/**
 * Módulo estado.h: define funções que permitem salvar o estado atual do jogo
 * em um arquivo e restaurar o estado a partir de um arquivo.
 */

/*
 * Formato do arquivo é:
 *  <# de peças em jogo> {1 byte}
 *  <Peça 1: linha> {1 byte}
 *  <Peça 1: coluna> {1 byte}
 *  <Peça 1: tipo> {1 byte}
 *  <Peça 1: cor> {1 byte}
 *  <Peça 2: linha> {1 byte}
 *  <Peça 2: coluna> {1 byte}
 *  <Peça 2: tipo> {1 byte}
 *  <Peça 2: cor> {1 byte}
 *  ...
 *  <Peça n: linha> {1 byte}
 *  <Peça n: coluna> {1 byte}
 *  <Peça n: tipo> {1 byte}
 *  <Peça n: cor> {1 byte}
 *  <Descrição textual da primeira jogada> {string de tamanho variável, terminada em '\0'}
 *  <Descrição textual da segunda jogada> {string de tamanho variável, terminada em '\0'}
 *  ...
 *  <Descrição textual da m-ésima jogada> {string de tamanho variável, terminada em '\0'}
 */

/**
 * Função que salva o estado do jogo atual em um arquivo. Esse estado inclui o estado 
 * do tabuleiro e também o log de todas as jogadas realizadas até aqui.
 * 
 * Parâmetros:
 *  - tabuleiro: ponteiro para uma estrutura do tipo t_tabuleiro guardando a representação
 * atual do tabuleiro do jogo.
 *  - logDeJogadas: ponteiro para uma estrutura do tipo t_logDeJogadas, contendo o log de 
 * todas as jogadas realizadas na partida até agora.
 *  - nomeDoArquivo: string contendo o nome do arquivo no qual o estado deve ser salvo.
 *
 * Retorno: VERDADEIRO, em caso de sucesso, ou FALSO, caso algum problema tenha ocorrido
 * na manipulação do arquivo.
 */
int estadoSalvaEmArquivo(t_tabuleiro * tabuleiro, t_logDeJogadas * logDeJogadas, char * nomeDoArquivo);

/**
 * Função que restaura o estado do jogo (incluindo o log de jogadas) a partir de um arquivo
 * especificado.
 * 
 * Parâmetros:
 *  - tabuleiro: ponteiro para uma estrutura do tipo t_tabuleiro guardando a representação
 * atual do tabuleiro do jogo. A função inicializa um novo tabuleiro, então o ponteiro 
 * passado não deve apontar para um tabuleiro já inicializado.
 *  - logDeJogadas: ponteiro para uma estrutura do tipo t_logDeJogadas, contendo o log de 
 * todas as jogadas realizadas na partida até agora. A função inicializa um novo log de 
 * jogadas, então o ponteiro não deve apontar para um log já inicializado.
 *  - vez[parâmetro de saída]: ao final da execução, guarda o jogador que tem a vez para
 * a próxima jogada (VEZ_BRANCAS ou VEZ_PRETAS).
 *  - nomeDoArquivo: string contendo o nome do arquivo do qual o estado deve ser lido.
 * 
 * Retorno: VERDADEIRO, em caso de sucesso, ou FALSO, caso algum problema tenha ocorrido
 * na manipulação do arquivo.
 */
int estadoRestauraDeArquivo(t_tabuleiro * tabuleiro, t_logDeJogadas * logDeJogadas, int * vez, char * nomeDoArquivo);

#endif
