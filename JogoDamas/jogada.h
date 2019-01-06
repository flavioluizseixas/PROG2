#ifndef __JOGADA_H__
#define __JOGADA_H__

#include "tabuleiro.h"
#include "lista.h"
#include "util.h"

/**
 * Constantes que definem a vez da jogada atual (i.e, se é vez
 * das peças brancas jogarem ou se é vez das peças pretas jogarem).
 */
#define VEZ_BRANCAS     0
#define VEZ_PRETAS      1

/**
 * Módulo jogada.h: define estruturas de dados e funções para 
 * a manipulação de jogadas durante partida. Isso inclui a 
 * verificação de se uma jogada é válida, a leitura de uma 
 * jogada a partir do usuário e a execução de jogadas válidas.
 */

/*
 * Definição de tipo para armazenar coordenadas no tabuleiro.
 * Uma jogada será representada nesse módulo como uma lista de 
 * elementos desse tipo (ou seja, uma sequência de coordenadas
 * pelas quais a peça movida deverá passar, incluindo a casa
 * de origem).
 */
typedef struct {

    /*
     * Linha da coordenada.
     */
    int linha;

    /* 
     * Coluna da coordenada.
     */
    int coluna;
} t_coordenada;

/**
 * Enumeração que representa as diversas causas de falha na validação
 * de uma jogada, segundo as regras do jogo de damas. O primeiro item
 * representa uma jogada válida.
 */
typedef enum {

    JOGADA_INVALIDA_MOTIVO_VALIDA,  // Jogada é válida
    JOGADA_INVALIDA_MOTIVO_MOVIMENTO_NAO_DIAGONAL,  // Um dos movimentos especificados não é diagonal
    JOGADA_INVALIDA_MOTIVO_CASA_DESTINO_OCUPADA,    // A casa de destino de um dos movimentos está ocupada
    JOGADA_INVALIDA_MOTIVO_MULTIPLAS_PECAS_PULADAS, // Tentativa de pular mais de uma peça no mesmo movimento
    JOGADA_INVALIDA_MOTIVO_MESMA_COR_PULADA,    // Tentativa de pular peça da mesma cor
    JOGADA_INVALIDA_MOTIVO_MOVIMENTO_SEM_CAPTURA, // Movimento sem captura após outros com captura
    JOGADA_INVALIDA_MOTIVO_LEI_DA_MAIORIA,  // Jogada não respeita lei da maioria
    JOGADA_INVALIDA_MOTIVO_MULTIPLAS_CASAS_PULADAS,  // Peça normal tentou pular múltiplas casas vazias
    JOGADA_INVALIDA_MOTIVO_DIRECAO_PROIBIDA, // Tentativa de movimento em direção proibida
    JOGADA_INVALIDA_MOTIVO_MULTIPLOS_MOVIMENTOS_SEM_CAPTURA, // Tentativa de realizar segundo movimento sem captura no primeiro
    JOGADA_INVALIDA_MOTIVO_SEM_MOVIMENTO,    // Não há pelo menos duas coordenadas especificadas na jogada
    JOGADA_INVALIDA_MOTIVO_PECA_COR_ERRADA,  // Jogada tenta movimentar peça do adversário
    JOGADA_INVALIDA_MOTIVO_CASA_ORIGEM_VAZIA    // Casa de origem da jogada não contém peça
} t_jogadaInvalidaMotivo;

/**
 * Função que realiza a leitura de uma jogada digitada pelo usuário.
 * A função realiza a verificação de correção léxica e sintática da jogada,
 * e retorna a jogada lida tanto no formato de uma string, quanto no 
 * formato de uma lista de coordenadas a serem percorridas por uma peça.
 * 
 * Parâmetros: 
 *  - jogadaString[parâmetro de saída]: string que será preenchida pela
 * jogada digitada pelo usuário. Note que essa string pode ser preenchida
 * parcialmente, caso haja algum erro na especificação da jogada. Além disso,
 * a função assume que o chamador já tenha alocado uma string grande o suficiente
 * para a jogada. Uma string de 39 caracteres deve ser grande o suficiente para
 * qualquer jogada válida, já que: 1) cada coordenada ocupa dois caracteres; 
 * 2) coordenadas são separadas por um espaço; e 3) jogadas com múltiplos
 * movimentos precisam ter capturas de peças e há no máximo 12 peças adversárias
 * no tabuleiro.
 * 
 * Retorno: uma lista de elementos do tipo t_coordenada indicando as coordenadas
 * de todas as casas por onde a peça movida passa, incluindo a casa de origem da
 * peça (primeira posição da lista). Caso haja algum problema léxico ou sintático
 * na especificação da jogada, é retornada uma lista vazia.
 */
t_lista jogadaLe(char * jogadaString);

/**
 * Função que libera a memória associada a uma lista que representa uma jogada
 * lida a partir do usuário (vide função jogadaLe()). A função não só desaloca
 * a memória dos nós da lista, como também desaloca a memória alocada para as
 * estruturas t_coordenada contiadas em cada nó da lista.
 * 
 * Parâmetros:
 *  - jogada: ponteiro para a lista que representa a jogada a ser desalocada.
 * 
 * Retorno: nenhum.
 */
void jogadaListaLiberaMemoria(t_lista * jogada);

/**
 * Função que verifica se uma jogada é válida de acordo com as regras do jogo
 * de damas e, em caso afirmativo, a executa.
 * 
 * Parâmetros:
 *  - jogada: ponteiro para uma lista de coordenadas percorridas pela peça 
 * movimentada representando a jogada a ser efetuada.
 *  - tabuleiro: ponteiro para uma estrutura do tipo t_tabuleiro, contendo o
 * estado atual do tabuleiro. Se a jogada é válida, tabuleiro é modificado para
 * representar o estado após a execução da jogada. Peças capturadas são removidas
 * da lista de peças adequada.
 *  - vez: VEZ_BRANCAS ou VEZ_PRETAS (vide constantes definidas acima), indicando
 * qual jogador está jogando agora.
 * 
 * Retorno: valor numérico do tipo t_jogadaInvalidaMotivo reportando motivo da jogada
 * ter sido considerada inválida. Em caso de sucesso (i.e., jogada válida), 
 * JOGADA_INVALIDA_MOTIVO_VALIDA é retornado.
 */
t_jogadaInvalidaMotivo jogadaValidaExecuta(t_lista * jogada, t_tabuleiro * tabuleiro, int vez);

/**
 * Função que avalia estado atual do tabuleiro e, considerando o jogador da vez, 
 * avalia quantas peças ainda possuem movimentos válidos. Mesmo que um jogador 
 * ainda tenha peças em jogo, estas podem estar bloqueadas, fazendo com que não
 * haja jogadas válidas disponíveis. Útil como uma das condições para verificação
 * de se o jogo já terminou.
 * 
 * Parâmetros:
 *  - tabuleiro: ponteiro para estrutura do tipo t_tabuleiro representando o 
 * estado atual do tabuleiro. Estado não é modificado por essa função.
 *  - vez: VEZ_BRANCAS ou VEZ_PRETAS (vide constantes definidas acima), indicando
 * qual jogador está jogando agora.
 * 
 * Retorno: número de peças do jogador da vez que possuem ao menos um movimento
 * válido possível no momento.
 */
int jogadaPecasComMovimento(t_tabuleiro * tabuleiro, int vez);

/**
 * Função que avalia estado atual do tabuleiro e, considerando o jogador da vez, 
 * verifica qual é o número máximo de capturas que podem ser obtidas por uma jogada
 * no momento. Função útil para verificar se uma jogada especificada pelo jogador
 * atende à chamada Lei da Maioria (i.e., se a jogada maximiza o número de peças
 * adversárias capturadas).
 * 
 * Parâmetros:
 *  - tabuleiro: ponteiro para estrutura do tipo t_tabuleiro representando o 
 * estado atual do tabuleiro. Estado não é modificado por essa função.
 *  - vez: VEZ_BRANCAS ou VEZ_PRETAS (vide constantes definidas acima), indicando
 * qual jogador está jogando agora.
 *  - jogadaComMaisCapturas[parâmetro de saída]: string que armazena uma das jogadas
 * encontradas que maximizam o número de peças capturadas. A função assume que o 
 * chamador já tenha alocado uma string grande o suficiente
 * para a jogada. Uma string de 39 caracteres deve ser grande o suficiente para
 * qualquer jogada válida, já que: 1) cada coordenada ocupa dois caracteres; 
 * 2) coordenadas são separadas por um espaço; e 3) jogadas com múltiplos
 * movimentos precisam ter capturas de peças e há no máximo 12 peças adversárias
 * no tabuleiro. Se não houver jogadas com capturas, o chamador deve ignorar o 
 * valor de saída desse parâmetro.
 * 
 * Retorno: número inteiro indicando o número de capturas máximo encontrado. Um
 * valor de 0 indica que não há jogadas possíveis que envolvam capturas das peças
 * do adversário.
 */
int jogadaEncontraJogadaComMaisCapturas(t_tabuleiro * tabuleiro, int vez, char * jogadaComMaisCapturas);

/**
 * Função que traduz as constantes definidas na enumeração t_jogadaInvalidaMotivo
 * para representações textuais correspondentes. Útil para explicar ao usuário
 * o motivo de sua jogada ter sido considerada inválida.
 * 
 * Parâmetros:
 *  - motivo: constante numérica dentre os valores da enumeração t_jogadaInvalidaMotivo.
 *  - motivoString[parâmetro de saída]: descrição textual do motivo. A função assume que 
 * a string já foi previamente alocada pelo chamador. A maior descrição atualmente possui
 * 85 caracteres (contando o terminador). Assim, qualquer string de 85 ou mais caracteres
 * deve ser suficiente para essa função.
 * 
 * Retorno: nenhum. Resultado da função é armazenado no parâmetro de saída motivoString.
 */
void jogadaInvalidaMotivoParaString(t_jogadaInvalidaMotivo motivo, char * motivoString);

#endif
