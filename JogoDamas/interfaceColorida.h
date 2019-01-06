#ifndef __INTERFACECOLORIDA_H__
#define __INTERFACECOLORIDA_H__

/**
 * Módulo interfaceColorida.h: provê constantes e funções para a impressão do tabuleiro
 * e outras informações em cores. Provê também uma função para limpar a tela.
 */
#include "tabuleiro.h"

/**
 * Constantes que definem as cores disponíveis no módulo.
 */
#define INTERFACE_COLORIDA_COR_PRETO        0
#define INTERFACE_COLORIDA_COR_VERMELHO     1
#define INTERFACE_COLORIDA_COR_VERDE        2
#define INTERFACE_COLORIDA_COR_AMARELO      3
#define INTERFACE_COLORIDA_COR_AZUL         4
#define INTERFACE_COLORIDA_COR_MAGENTA      5
#define INTERFACE_COLORIDA_COR_CIANO        6
#define INTERFACE_COLORIDA_COR_BRANCO       7

/**
 * Função que imprime o tabuleiro em cores.
 * 
 * Parâmetros:
 *  - tabuleiro: estrutura do tipo t_tabuleiro que contém a representação atual do
 * tabuleiro do jogo.
 * 
 * Retorno: nenhum.
 */
void interfaceColoridaImprimeTabuleiro(t_tabuleiro tabuleiro);

/**
 * Função que limpa a tela.
 * 
 * Parâmetros: nenhum.
 * 
 * Retorno: nenhum.
 */
void interfaceColoridaLimpaTela();

/**
 * Função que altera a cor da fonte para as próximas impressões de caracteres.
 * 
 * Parâmetros:
 *  - cor: uma das constantes numéricas que definem as cores disponíveis no módulo.
 * 
 * Retorno: nenhum.
 */
void interfaceColoridaMudaCorFonte(int cor);

/**
 * Função que altera a cor de fundo para as próximas impressões de caracteres.
 * 
 * Parâmetros:
 *  - cor: uma das constantes numéricas que definem as cores disponíveis no módulo.
 * 
 * Retorno: nenhum.
 */
void interfaceColoridaMudaCorFundo(int cor);

/**
 * Função que altera fonte para negrito para as próximas impressões de caracteres.
 * 
 * Parâmetros: nenhum.
 * 
 * Retorno: nenhum.
 */
void interfaceColoridaNegrito();

/*
 * Função que reseta as configurações de cor e fonte para os valores originais (no
 * início da execução do programa) para as próximas impressões de caracteres.
 * 
 * Parâmetros: nenhum.
 * 
 * Retorno: nenhum.
 */
void interfaceColoridaReseta();

#endif