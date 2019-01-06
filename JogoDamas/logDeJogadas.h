#ifndef __LOGDEJOGADAS_H__
#define __LOGDEJOGADAS_H__

#include "lista.h"

/**
 * Módulo lista.h: define estrutura da dados e funções para a manipulação
 * e armazenamento em arquivo de um log das jogadas efetuadas até aqui na
 * partida.
 */

/**
 * Definimos um tipo t_logDeJogadas apenas como um apelido para t_lista.
 * Um log de jogadas, portanto, é basicamente uma lista de strings. Cada
 * string é a descrição textual de uma jogada.
 */
typedef t_lista t_logDeJogadas;

/**
 * Função que inicializa um novo log de jogadas vazio.
 * 
 * Parâmetros: nenhum.
 * 
 * Retorno: uma lista vazia representando um log de jogadas vazio.
 */
t_logDeJogadas logDeJogadasInicializa();

/**
 * Função que adiciona uma nova jogada no log de jogadas.
 * 
 * Parâmetros: 
 *  - logDeJogadas: ponteiro para o log de jogadas.
 *  - novaJogada: string com a representação textual da jogada a ser
 * inserida no log.
 * 
 * Retorno: nenhum.
 */
void logDeJogadasAdiciona(t_logDeJogadas * logDeJogadas, char * novaJogada);

/**
 * Função que salva o log de jogadas atual em um arquivo texto.
 * 
 * Parâmetros:
 *  - logDeJogadas: ponteiro para o log de jogadas.
 *  - nomeDoArquivo: nome do arquivo no qual o log de jogadas será salvo.
 * 
 * Retorno: VERDADEIRO, em caso de sucesso, ou FALSO, em caso de falha na 
 * manipulação do arquivo.
 */
int logDeJogadasSalvaEmArquivo(t_logDeJogadas * logDeJogadas, char * nomeDoArquivo);

#endif
