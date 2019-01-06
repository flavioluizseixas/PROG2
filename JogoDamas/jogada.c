#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jogada.h"

void jogadaListaLiberaMemoria(t_lista * jogada) {

    t_coordenada * ponteiro;    // Ponteiro para cada coordenada encontrada na lista.

    /**
     * Iteramos pela lista, obtendo os ponteiros para as
     * coordenadas e liberando a memória associada.
     */
    ponteiro = listaPrimeiro(jogada);
    while(ponteiro != NULL) {

        free(ponteiro);
        ponteiro = listaProximo(jogada);
    }

    /**
     * Ao final, temos que liberar a memória associada 
     * aos nós da lista.
     */
    listaLiberaMemoria(jogada);
}

t_lista jogadaLe(char * jogadaString) {

    char proximoCaractere;  // Guarda caracteres lidos do teclado.
    int linha, coluna;      // Valores numéricos de linha/coluna das coordenadas lidas.
    int i;                  // Índice do último caractere inserido em jogadaString.
    t_lista jogada;         // Lista de coordenadas a ser gerada como resultado da função.
    t_coordenada * novaCoordenada;  // Ponteiro para manipular novas coordenadas inseridas na lista.

    /**
     * Inicializamos uma lista vazia.
     */
    jogada = listaInicializa();

    /**
     * Inicializamos i = 0 para começarmos a colocar caracteres no 
     * início de jogadaString.
     */
    i = 0;

    /**
     * Vamos iterar até lermos um caractere de quebra de linha do teclado. 
     * Condição será testada dentro da repetição.
     */
    while(1) {

        /**
         * Ler próximo caractere do teclado.
         */
        proximoCaractere = getchar();

        /**
         * Concatenar ao final de jogadaString.
         */
        jogadaString[i++] = proximoCaractere;

        /**
         * Se encontramos uma quebra de linha, a leitura da jogada acabou.
         */
        if (proximoCaractere == '\n') break ;

        /**
         * Se encontramos um espaço aqui, vamos ignorá-lo e passar para 
         * o próximo caractere.
         */
        if (proximoCaractere == ' ') continue ;

        /**
         * Nesse momento, estamos em busca do início da especificação de uma
         * coordenada de casa. Tais coordenadas sempre começam por um caractere
         * entre '1' e '8' (inclusive).
         */
        if (proximoCaractere >= '1' && proximoCaractere <= '8') {

            /**
             * Encontramos algo que parece ser a especificação de um número
             * de linha de uma coordenada. Vamos traduzir o caractere para 
             * um inteiro. Aqui, nos valemos de uma propriedade da tabela
             * ASCII que coloca os caracteres relativos a algarismos decimais
             * em ordem. Assim, podemos simplesmente subtrair o valor ASCII
             * do caractere lido do valor do caractere '1'.
             */
            linha = (int) (proximoCaractere - '1');

            /**
             * Leitura do próximo caractere e concatenação com a jogadaString.
             */
            proximoCaractere = getchar();
            jogadaString[i++] = proximoCaractere;

            /**
             * Próximo caractere tem que ser a especificação de uma coluna. Isso
             * é feito através de um caractere entre 'a' e 'h' (inclusive).
             */
            if (proximoCaractere >= 'a' && proximoCaractere <= 'h') {

                /**
                 * Especificação válida de coluna. Novamente, usamos o truque dos
                 * valores ASCII dos caracteres esperados para calcular o índice 
                 * numérico da coluna.
                 */
                coluna = (int) (proximoCaractere - 'a');

                /**
                 * Criamos uma nova estrutura do tipo t_coordenada, preenchemos
                 * os valores adequados e inserimos na lista jogada.
                 */
                novaCoordenada = (t_coordenada *) malloc(sizeof(t_coordenada));
                if (novaCoordenada == NULL) {

                    printf("Falha ao alocar memoria!\n");
                    exit(1);
                }
                novaCoordenada->linha = linha;
                novaCoordenada->coluna = coluna;
                listaAdiciona(& jogada, novaCoordenada);

                /**
                 * Logo após a especificação de uma coordenada, esperamos ou um 
                 * espaço (para separar a próxima coordenada da jogada) ou uma
                 * quebra de linha (para delimitar o final da jogada). Aqui, lemos
                 * o próximo caractere e testamos se ele se encaixa em um dos dois 
                 * casos.
                 */
                proximoCaractere = getchar();
                jogadaString[i++] = proximoCaractere;

                if (proximoCaractere == ' ') continue ;     // Talvez haja outras coordenadas.
                if (proximoCaractere == '\n') break ;       // Fim da especificação da jogada.
            }
        }
        /*
         * Se chegamos até aqui, encontramos algum caractere inesperado na especificação
         * da jogada. Vamos liberar a memória associada à jogada e sair da repetição.
         */
        jogadaListaLiberaMemoria(& jogada);
        break ;

    }

    /**
     * Precisamos colocar o caractere terminador no final da string. Como sempre
     * concatenamos os caracteres lidos antes de testá-los na repetição anterior,
     * a string deve ter um caractere de quebra de linha na posição i - 1. Vamos
     * colocar o terminador nessa posição para suprimi-lo.
     */
    jogadaString[i - 1] = '\0';
    return(jogada);
}

/**
 * Função auxiliar à função jogadaEncontraJogadaComMaisCapturas(). Em particular, 
 * essa função implementa a lógica para o caso da movimentação de uma peça normal
 * (i.e., que não é dama).
 * 
 * Essa função realiza a busca de jogadas através de uma recursão. Internamente,
 * a função pode alterar o estado do parâmetro tabuleiro, simulando a execução
 * das jogadas avaliadas. Por esse motivo, o parâmetro tabuleiro é passado por 
 * valor (ao invés de usar um ponteiro). Assim, qualquer modificação feita aqui
 * não terá efeito no tabuleiro real do jogo.
 * 
 * Cada chamada recursiva dessa função corresponde a uma nova movimentação da peça
 * dentro do âmbito de uma mesma jogada. A função então avalia as próximas possibilidades
 * de movimentação para dar continuidade à jogada, faz as alterações adequadas na cópia
 * do tabuleiro e se chama recursivamente para cada possível movimentação.
 * 
 * Parâmetros:
 *  - tabuleiro: cópia do tabuleiro do jogo. Quando essa função é chamada recursivamente,
 * esse tabuleiro corresponde a tabuleiro atual do jogo modificado por outros movimentos
 * que tenham sido realizados na jogada sendo analisada.
 *  - origemLinha: coordenada (linha) da peça que está sendo movida na jogada analisada.
 *  - origemLinha: coordenada (coluna) da peça que está sendo movida na jogada analisada.
 *  - vez: cor da peça que está sendo movida.
 *  - jogadaComMaisCapturas[parâmetro de entrada e saída]: descrição textual dos movimentos
 * já feitos na jogada atual até o momento dessa chamada. Ao final dessa chamada, contém
 * a descrição textual da jogada com mais capturas encontrada a partir daqui.
 * 
 * Retorno: número de capturas da jogada com mais capturas encontrada.
 */
int jogadaEncontraJogadaComMaisCapturasParaPecaNormal(t_tabuleiro tabuleiro, int origemLinha, int origemColuna, int vez, char * jogadaComMaisCapturas) {

    /**
     * A variável declarada a seguir é um vetor de 4 posições de uma simples
     * estrutura composta de dois campos: um número de linha e um número de coluna.
     * A ideia é usarmos esse vetor para armazenar as possíveis direções de movimentação
     * de uma peça (frente-esquerda, frente-direita, trás-esquerda e trás-direita).
     * Essas direções são representadas como deslocamentos nas linhas e colunas. Por 
     * exemplo, um valor de 1 no campo linha significa mover a peça na direção crescente
     * dos índices de linha. Um valor de -1 representa mover a peça no sentido oposto.
     * 
     * Note que já iniciamos o vetor com os valores que representam as quatro direções
     * possíveis.
     */
    struct {
        int linha;
        int coluna;
    } direcoes[4] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    int i;      // Índice para percorrer o vetor direcoes.
    int casaAlvoLinha, casaAlvoColuna;  // Índices de linha e coluna de uma casa candidata em uma movimentação.
    char proximaJogada[39];             // String para armazenar a jogada sendo avalida.
    int nCapturasJogadaComMaisCapturas, nCapturasProximaJogada; // Número de capturas (maior já encontrado e da jogada atualmente avalida).
    t_peca * pecaMovida, * pecaCapturada;   // Ponteiros para a peça atuamente sendo movida e para uma peça eventualmente capturada.
    int comprimentoString;      // Variável auxiliar para preenchimento da string que descreve a jogada atualmente avaliada.
    t_corPeca adversario;   // Cor das peças do adversário. Ajuda a decidir se há uma peça a ser capturada em certa jogada.

    /**
     * Decidimos a cor das peças do adversário com base na vez.
     */
    if (vez == VEZ_BRANCAS) adversario = PECA_PRETA;
    else adversario = PECA_BRANCA;

    /**
     * Todas as jogadas que vamos analisar nessa execução da função começam pelos
     * mesmos movimentos: os que foram informados no parâmetro jogadaComMaisCapturas.
     * A esses podem ser acrescidos outros nessa chamada e em chamadas recursivas 
     * posteriores. Para isso, geramos uma cópia da string jogadaComMaisCapturas em
     * proximaJogada. Também guardamos o comprimento atual dessas strings em 
     * comprimentoString para sabermos mais tarde onde começar a incluir as coordenadas
     * para o próximo movimento.
     */
    strcpy(proximaJogada, jogadaComMaisCapturas);
    comprimentoString = strlen(jogadaComMaisCapturas);

    /**
     * Inicialmente, zeramos a variável nCapturasJogadaComMaisCapturas para podermos
     * contar quantas capturas conseguimos realizar desse ponto em diante da jogada.
     */
    nCapturasJogadaComMaisCapturas = 0;

    /**
     * Guardamos uma referência para a peça sendo movida nessa jogada. Essa peça é
     * identificada pelas coordenadas origemLinha e origemColuna.
     */
    pecaMovida = tabuleiro.casas[origemLinha][origemColuna].ocupacao;

    /**
     * Qualquer que seja o movimento realizado, ele retirará a peçaMovida da casa
     * atual. Assim, esvaziamos a casa aqui.
     */
    tabuleiro.casas[origemLinha][origemColuna].ocupacao = NULL;

    /**
     * Iteramos pelas 4 direções possíveis de movimentação da peça.
     */
    for (i = 0; i < 4; i++) {

        /**
         * Para a i-ésima direção, computamos a casa alvo como sendo o somatório
         * das coordenadas de origem da peça movida com os valores dos campos linha
         * e coluna da direção.
         */
        casaAlvoLinha = origemLinha + direcoes[i].linha;
        casaAlvoColuna = origemColuna + direcoes[i].coluna;

        /**
         * Verificação: a casa alvo ainda está dentro dos limites do tabuleiro? Se 
         * não, movimentação não é viável.
         */
        if (casaAlvoLinha < 0 || casaAlvoLinha > 7) continue ;
        if (casaAlvoColuna < 0 || casaAlvoColuna > 7) continue ;

        /**
         * A casa alvo está vazia? Se sim, não há peça a ser capturada o que quer
         * dizer que uma movimentação nessa direção não trará mais capturas.
         */
        if (tabuleiro.casas[casaAlvoLinha][casaAlvoColuna].ocupacao == NULL) continue ;

        /**
         * A casa alvo contém uma peça do adversário? Se não, também não podemos 
         * capturar.
         */
        if (tabuleiro.casas[casaAlvoLinha][casaAlvoColuna].ocupacao->cor == adversario) {

            /**
             * Se chegamos aqui, temos uma peça que talvez possa ser capturada nessa
             * direção. Para a captura ser viável, ainda precisamos verificar outras
             * condições relativas à casa posterior na mesma diagonal. Para facilitar
             * vamos atualizar as coordenadas da casa alvo para essa casa posterior.
             */
            casaAlvoLinha = casaAlvoLinha + direcoes[i].linha;
            casaAlvoColuna = casaAlvoColuna + direcoes[i].coluna;

            /**
             * Nova casa alvo ainda está dentro do tabuleiro?
             */
            if (casaAlvoLinha < 0 || casaAlvoLinha > 7) continue ;
            if (casaAlvoColuna < 0 || casaAlvoColuna > 7) continue ;

            /**
             * Casa alvo precisa estar vazia, já que após a captura peça movida será
             * colocada lá.
             */
            if (tabuleiro.casas[casaAlvoLinha][casaAlvoColuna].ocupacao == NULL) {

                /**
                 * Se chegamos aqui, a movimentação nessa direção de fato cria uma 
                 * captura válida. Assim, o que precisamos avaliar e qual seria a 
                 * sequência de movimentos depois dessa captura que maximiza o 
                 * número de capturas posteriores. Aqui entra a recursão. Mas antes
                 * de realizar a chamada recursiva, precisamos preparar os parâmetros.
                 * Em particular, começamos alterando o tabuleiro para conter a movimentação
                 * que acabamos de encontrar: a peça capturada é removida e a peça 
                 * movimentada vai para a casa alvo.
                 */
                pecaCapturada = tabuleiro.casas[casaAlvoLinha - direcoes[i].linha][casaAlvoColuna - direcoes[i].coluna].ocupacao;
                tabuleiro.casas[casaAlvoLinha - direcoes[i].linha][casaAlvoColuna - direcoes[i].coluna].ocupacao = NULL;
                tabuleiro.casas[casaAlvoLinha][casaAlvoColuna].ocupacao = pecaMovida; 

                /**
                 * Também adicionamos a coordenada da casa alvo na string proximaJogada.
                 */
                proximaJogada[comprimentoString] = ' ';
                proximaJogada[comprimentoString + 1] = casaAlvoLinha + '1';
                proximaJogada[comprimentoString + 2] = casaAlvoColuna + 'a';
                proximaJogada[comprimentoString + 3] = '\0';

                /**
                 * Aqui, fazemos a chamada recursiva. O maior número de capturas da jogada analisada
                 * será a captura da movimentação que acabamos de fazer, somada ao maior 
                 * número de capturas encontrado pela chamada recursiva.
                 */
                nCapturasProximaJogada = 1 + jogadaEncontraJogadaComMaisCapturasParaPecaNormal(tabuleiro, casaAlvoLinha, casaAlvoColuna, vez, proximaJogada);

                /**
                 * Encontramos um número de capturas maior do que conhecíamos até então?
                 * Se sim, atualizamos as variáveis relacionadas ao maior número de 
                 * capturas.
                 */
                if (nCapturasProximaJogada > nCapturasJogadaComMaisCapturas) {

                    strcpy(jogadaComMaisCapturas, proximaJogada);
                    nCapturasJogadaComMaisCapturas = nCapturasProximaJogada;
                }

                /**
                 * Na próxima iteração, avaliaremos outra direção para a movimentação da 
                 * peça. Assim, precisamos voltar o tabuleiro ao estado original (como
                 * recebido por essa chamada da função). Para isso, basta retirar a 
                 * peça movida da casa alvo e recolocar a peça capturada no seu lugar
                 * de origem.
                 */                
                tabuleiro.casas[casaAlvoLinha][casaAlvoColuna].ocupacao = NULL;
                tabuleiro.casas[casaAlvoLinha - direcoes[i].linha][casaAlvoColuna - direcoes[i].coluna].ocupacao = pecaCapturada;
            }
        }
    }

    /**
     * Retornamos finalmente o número de capturas da jogada com maior número de capturas
     * encontrada a partir do estado original dessa chamada.
     */
    return(nCapturasJogadaComMaisCapturas);
}

/**
 * Função auxiliar à função jogadaEncontraJogadaComMaisCapturas(). Em particular, 
 * essa função implementa a lógica para o caso da movimentação de uma dama.
 * 
 * Essa função realiza a busca de jogadas através de uma recursão. Internamente,
 * a função pode alterar o estado do parâmetro tabuleiro, simulando a execução
 * das jogadas avaliadas. Por esse motivo, o parâmetro tabuleiro é passado por 
 * valor (ao invés de usar um ponteiro). Assim, qualquer modificação feita aqui
 * não terá efeito no tabuleiro real do jogo.
 * 
 * Cada chamada recursiva dessa função corresponde a uma nova movimentação da dama
 * dentro do âmbito de uma mesma jogada. A função então avalia as próximas possibilidades
 * de movimentação para dar continuidade à jogada, faz as alterações adequadas na cópia
 * do tabuleiro e se chama recursivamente para cada possível movimentação.
 * 
 * Parâmetros:
 *  - tabuleiro: cópia do tabuleiro do jogo. Quando essa função é chamada recursivamente,
 * esse tabuleiro corresponde a tabuleiro atual do jogo modificado por outros movimentos
 * que tenham sido realizados na jogada sendo analisada.
 *  - origemLinha: coordenada (linha) da peça que está sendo movida na jogada analisada.
 *  - origemLinha: coordenada (coluna) da peça que está sendo movida na jogada analisada.
 *  - vez: cor da peça que está sendo movida.
 *  - jogadaComMaisCapturas[parâmetro de entrada e saída]: descrição textual dos movimentos
 * já feitos na jogada atual até o momento dessa chamada. Ao final dessa chamada, contém
 * a descrição textual da jogada com mais capturas encontrada a partir daqui.
 * 
 * Retorno: número de capturas da jogada com mais capturas encontrada.
 */
int jogadaEncontraJogadaComMaisCapturasParaDama(t_tabuleiro tabuleiro, int origemLinha, int origemColuna, int vez, char * jogadaComMaisCapturas) {

    /**
     * A variável declarada a seguir é um vetor de 4 posições de uma simples
     * estrutura composta de dois campos: um número de linha e um número de coluna.
     * A ideia é usarmos esse vetor para armazenar as possíveis direções de movimentação
     * de uma peça (frente-esquerda, frente-direita, trás-esquerda e trás-direita).
     * Essas direções são representadas como deslocamentos nas linhas e colunas. Por 
     * exemplo, um valor de 1 no campo linha significa mover a peça na direção crescente
     * dos índices de linha. Um valor de -1 representa mover a peça no sentido oposto.
     * 
     * Note que já iniciamos o vetor com os valores que representam as quatro direções
     * possíveis.
     */
    struct {
        int linha;
        int coluna;
    } direcoes[4] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    int i, j;   // Índice para percorrer o vetor direcoes e outro para avaliar o quão longe a dama pode ir na diagonal.
    int casaAlvoLinha, casaAlvoColuna;  // Índices de linha e coluna de uma casa candidata em uma movimentação.
    char proximaJogada[39];     // String para armazenar a jogada sendo avalida.
    int nCapturasJogadaComMaisCapturas, nCapturasProximaJogada; // Número de capturas (maior já encontrado e da jogada atualmente avalida).
    t_peca * pecaMovida, * pecaCapturada;   // Ponteiros para a peça atuamente sendo movida e para uma peça eventualmente capturada.
    int comprimentoString;  // Variável auxiliar para preenchimento da string que descreve a jogada atualmente avaliada.
    t_corPeca adversario;   // Cor das peças do adversário. Ajuda a decidir se há uma peça a ser capturada em certa jogada.

    /**
     * Decidimos a cor das peças do adversário com base na vez.
     */
    if (vez == VEZ_BRANCAS) adversario = PECA_PRETA;
    else adversario = PECA_BRANCA;

    /**
     * Todas as jogadas que vamos analisar nessa execução da função começam pelos
     * mesmos movimentos: os que foram informados no parâmetro jogadaComMaisCapturas.
     * A esses podem ser acrescidos outros nessa chamada e em chamadas recursivas 
     * posteriores. Para isso, geramos uma cópia da string jogadaComMaisCapturas em
     * proximaJogada. Também guardamos o comprimento atual dessas strings em 
     * comprimentoString para sabermos mais tarde onde começar a incluir as coordenadas
     * para o próximo movimento.
     */
    strcpy(proximaJogada, jogadaComMaisCapturas);
    comprimentoString = strlen(jogadaComMaisCapturas);

    /**
     * Inicialmente, zeramos a variável nCapturasJogadaComMaisCapturas para podermos
     * contar quantas capturas conseguimos realizar desse ponto em diante da jogada.
     */    
    nCapturasJogadaComMaisCapturas = 0;

    /**
     * Guardamos uma referência para a peça sendo movida nessa jogada. Essa peça é
     * identificada pelas coordenadas origemLinha e origemColuna.
     */    
    pecaMovida = tabuleiro.casas[origemLinha][origemColuna].ocupacao;

    /**
     * Qualquer que seja o movimento realizado, ele retirará a peçaMovida da casa
     * atual. Assim, esvaziamos a casa aqui.
     */    
    tabuleiro.casas[origemLinha][origemColuna].ocupacao = NULL;

    /**
     * Iteramos pelas 4 direções possíveis de movimentação da peça.
     */
    for (i = 0; i < 4; i++) {

        /*
         * Procuramos pela próxima peça na diagonal. Uma diagonal tem
         * no máximo 8 casas possíveis, sendo que a primeira já corresponde
         * à casa atual da peça movida. Por isso os limites da repetição.
         */
        pecaCapturada = NULL;
        for (j = 1; j < 8; j++) {

            /**
             * Calculamos a casa alvo com base na direção percorrida e 
             * no deslocamento dentro da diagonal (j).
             */
            casaAlvoLinha = origemLinha + j * direcoes[i].linha;
            casaAlvoColuna = origemColuna + j * direcoes[i].coluna;

            /**
             * Casa alvo está dentro do tabuleiro? Se não, podemos parar
             * de processar essa direção. Fazemos isso atribuindo o valor
             * 8 (limite máximo dessa repetição) à variável j. Isso indicará
             * mais a frente no código que não encontramos nenhuma peça a 
             * ser capturada nessa direção.
             */
            if (casaAlvoLinha < 0 || casaAlvoLinha > 7) {
                
                j = 8;
                break ;
            }
            if (casaAlvoColuna < 0 || casaAlvoColuna > 7) {
                
                j = 8;
                break ;
            }

            /**
             * Casa alvo está ocupada? 
             */
            if (tabuleiro.casas[casaAlvoLinha][casaAlvoColuna].ocupacao != NULL) {

                /**
                 * Sim. Mas é com uma peça do adversário?
                 */
                if (tabuleiro.casas[casaAlvoLinha][casaAlvoColuna].ocupacao->cor == adversario) {

                        /**
                         * Sim. Vamos marcar essa peça para captura e removê-la da casa.
                         */
                        pecaCapturada = tabuleiro.casas[casaAlvoLinha][casaAlvoColuna].ocupacao;
                        tabuleiro.casas[casaAlvoLinha][casaAlvoColuna].ocupacao = NULL;

                        /* 
                         * Avançamos j para a próxima casa na diagonal, depois da peça capturada.
                         * Isso demarcará onde começaremos a buscar por uma casa de destino para
                         * a peça movida nesse movimento.
                         */
                        j = j + 1;
                }
                else {

                    /**
                     * Não. A peça encontrada é da mesma cor da peça movida. Isso significa que
                     * não há captura possível nessa direção. Novamente, vamos usar j = 8 para
                     * sinalizar isso.
                     */
                    j = 8;
                }

                /**
                 * Se encontramos uma casa ocupada, seja por uma peça do adversário ou não,
                 * essa repetição já cumpriu sua tarefa. Vamos sair.
                 */
                break ;
            }
        }

        /* 
         * Iterar por todas as casas vazias consecutivas após a 
         * peça removida capturada, avaliando potenciais casas de destino para 
         * a peça movida.
         */
        for (; j < 8; j++) {

            /**
             * Calcular uma nova casa alvo.
             */
            casaAlvoLinha = origemLinha + j * direcoes[i].linha;
            casaAlvoColuna = origemColuna + j * direcoes[i].coluna;

            /**
             * Testar se casa alvo está dentro dos limites do tabuleiro.
             */
            if (casaAlvoLinha < 0 || casaAlvoLinha > 7) break ;
            if (casaAlvoColuna < 0 || casaAlvoColuna > 7) break ;

            /**
             * Casa alvo está ocupada: se sim, não é possível mover a peça movida
             * para ela ou para qualquer outra além. Terminamos a repetição aqui.
             */
            if (tabuleiro.casas[casaAlvoLinha][casaAlvoColuna].ocupacao != NULL) break ;

            /**
             * Se chegamos até aqui, casa alvo está vazia. Assim, trata-se de uma 
             * potencial casa de destino para a peça movida. Vamos avaliar essa 
             * possibilidade. Começamos colocando a peça movida na casa alvo.
             */
            tabuleiro.casas[casaAlvoLinha][casaAlvoColuna].ocupacao = pecaMovida; 

            /**
             * Atualizamos a representação da jogada como string com essa movimentação.
             */
            proximaJogada[comprimentoString] = ' ';
            proximaJogada[comprimentoString + 1] = casaAlvoLinha + '1';
            proximaJogada[comprimentoString + 2] = casaAlvoColuna + 'a';
            proximaJogada[comprimentoString + 3] = '\0';

            /**
             * Com os parâmetros atualizados, chamamos a função recursivamente para 
             * avaliar o número máximo de capturas que conseguimos realizar daqui para
             * frente. Assim, o número máximo de capturas para essa movimentação é 
             * o somatórimo da captura dessa movimentação com o o número máximo de 
             * capturas que conseguimos realizar daqui para frente.
             */
            nCapturasProximaJogada = 1 + jogadaEncontraJogadaComMaisCapturasParaDama(tabuleiro, casaAlvoLinha, casaAlvoColuna, vez, proximaJogada);

            /**
             * Valor é maior do que o das possibilidades avaliadas anteriormente?
             */
            if (nCapturasProximaJogada > nCapturasJogadaComMaisCapturas) {

                /**
                 * Sim. Atualizamos as variáveis relacionadas a esse máximo.
                 */
                strcpy(jogadaComMaisCapturas, proximaJogada);
                nCapturasJogadaComMaisCapturas = nCapturasProximaJogada;
            }
            
            /**
             * Vamos retirar a peça movida da casa alvo para que a próxima 
             * iteração dessa repetição possa avaliar outra casa alvo.
             */
            tabuleiro.casas[casaAlvoLinha][casaAlvoColuna].ocupacao = NULL;
        }

        /**
         * Nesse ponto, já avaliamos todas as possibilidades de movimentação da 
         * dama nessa direção. Precisamos restaurar o tabuleiro para as condições
         * originais (da chamada atual da função) para que as próximas iterações
         * dessa repetição possam avaliar as outras direções. Para isso, vamos
         * verificar se, de fato, capturamos alguma peça. Se sim, restauramos
         * a peça capturada a sua posição original.
         */
        if (pecaCapturada != NULL) {

            /*
             * Restaurar peça capturada à sua posição original.
             */
            tabuleiro.casas[pecaCapturada->linha][pecaCapturada->coluna].ocupacao = pecaCapturada;
        }
    }

    /**
     * Finalmente, retornamos o número máximo de capturas encontrado desse ponto
     * em diante da jogada.
     */
    return(nCapturasJogadaComMaisCapturas);
}

int jogadaEncontraJogadaComMaisCapturas(t_tabuleiro * tabuleiro, int vez, char * jogadaComMaisCapturas) {

    char proximaJogada[39];     // Próxima jogada avaliada.
    int nCapturasJogadaComMaisCapturas, nCapturasProximaJogada; // Número de capturas da jogada com mais capturas e da jogada atualmente analisada.
    t_peca * ponteiro;  // Ponteiro para iterar pelas peças disponíveis.
    t_lista * lista;    // Ponteiro para a lista de peças disponíveis considerando a cor da vez.

    /**
     * Com base na cor da vez, guardamos um ponteiro para a lista de peças 
     * disponíveis.
     */
    if (vez == VEZ_BRANCAS) lista = & (tabuleiro->listaPecasBrancas);
    else lista = & (tabuleiro->listaPecasPretas);

    /**
     * Começamos a percorrer a lista de peças disponíveis, a partir da primeira.
     */
    ponteiro = listaPrimeiro(lista);

    /**
     * Também inicializamos o número máximo de capturas encontrado para -1, de forma
     * que ele seja atualizado a medida que novas jogadas com mais capturas forem 
     * encontradas.
     */
    nCapturasJogadaComMaisCapturas = -1;

    /**
     * A repetição termina quando não há mais peças a serem analisadas.
     */
    while(ponteiro) {

        /**
         * Iniciamos a string que descreve a jogada com as coordenadas da
         * peça que escolhemos para (tentar) mover.
         */
        proximaJogada[0] = ponteiro->linha + '1';
        proximaJogada[1] = ponteiro->coluna + 'a';
        proximaJogada[2] = '\0';

        /**
         * Delegamos encontrar o maior número de capturas possível com essa peça a 
         * funções mais especializadas. Em particular, fazemos a distinção entre
         * peças normais e damas.
         */
        if (ponteiro->tipo == PECA_NORMAL) {

            nCapturasProximaJogada = jogadaEncontraJogadaComMaisCapturasParaPecaNormal(* tabuleiro, ponteiro->linha, ponteiro->coluna, vez, proximaJogada);
        }
        else {

            nCapturasProximaJogada = jogadaEncontraJogadaComMaisCapturasParaDama(* tabuleiro, ponteiro->linha, ponteiro->coluna, vez, proximaJogada);
        }

        /**
         * Se o número máximo de capturas encontradas com essa peça é maior do que
         * o máximo que conhecíamos antes, atualizamos as informações relativas a
         * esse máximo.
         */
        if (nCapturasProximaJogada > nCapturasJogadaComMaisCapturas) {

            nCapturasJogadaComMaisCapturas = nCapturasProximaJogada;
            strcpy(jogadaComMaisCapturas, proximaJogada);
        }

        /**
         * Próxima peça da lista será avaliada na próxima iteração da repetição.
         */
        ponteiro = listaProximo(lista);
    }

    /**
     * Retornamos o número máximo de capturas encontrado.
     */
    return(nCapturasJogadaComMaisCapturas);
}

/**
 * Função auxiliar à função jogadaValidaExecutaDama, especializada para avaliar movimentos
 * que envolvem captura de peças. Função verifica o movimento está de acordo
 * com as regras e, adicionalmente, se de fato o movimento resulta em uma 
 * captura de peça adversária. Ao final da execução, função retorna uma constante
 * do tipo t_jogadaInvalidaMotivo indicando o motivo da falha do movimento ou 
 * sucesso. Além disso, em caso de sucesso a função retorna um ponteiro para
 * a peça capturada.
 * 
 * Parâmetros:
 *  - de: ponteiro para uma estrutura do tipo t_coordenada indicando a coordenada
 * de origem da peça movida.
 *  - para: ponteiro para uma estrutura do tipo t_coordenada indicando a coordenada
 * de destino da peça movida.
 *  - tabuleiro: ponteiro para uma estrutura do tipo t_tabuleiro indicando o estado
 * atual do tabuleiro (possivelmente já alterado por outros movimentos da jogada
 * sendo avaliada).
 *  - vez: VEZ_BRANCAS ou VEZ_PRETAS, indicando de qual jogador é a vez da jogada
 * atual.
 *  - pecaCapturada[parâmetro de saída]: ponteiro para um ponteiro de uma estrutura
 * do tipo t_peca. Ao final da função, se movimento resultou em captura, esse 
 * parâmetro aponta para a peça capturada.
 * 
 * Retorno: constante do tipo t_jogadaInvalidaMotivo indicando sucesso no movimento
 * ou o motivo para o movimento ser inválido.
 */
t_jogadaInvalidaMotivo jogadaValidaExecutaDamaCaptura(t_coordenada * de, t_coordenada * para, t_tabuleiro * tabuleiro, int vez, t_peca ** pecaCapturada) {

    int diferencaLinha, diferencaColuna;    // Número de casas (em linhas e colunas) entre casa de origem e destino da jogada.
    int pecasCapturadas;                    // Número de peças capturadas nesse movimento.
    int i;                                  // Índice para iterar pelas casas da diagonal usada no movimento.
    int proximaCasaLinha, proximaCasaColuna;    // Próxima casa percorrida na diagonal do movimento.
    t_peca * _pecaCapturada;                // Ponteiro (local a função) para a peça capturada (se alguma).

    /**
     * Começamos calculando o número de linhas e colunas percorridas pelo movimento.
     * Como se trata de uma dama, não faz diferença a direção do movimento, então
     * calculamos esses valores em valor absoluto.
     */
    diferencaLinha = de->linha - para->linha;
    if (diferencaLinha < 0) diferencaLinha = -diferencaLinha;
    diferencaColuna = de->coluna - para->coluna;
    if (diferencaColuna < 0) diferencaColuna = -diferencaColuna;

    /**
     * Inicializamos o ponteiro da peça capturada para NULL, já que, a princípio,
     * não sabemos se haverá captura.
     */
    _pecaCapturada = NULL;

    /*
     * Essa movimentação é válida se:
     * 1) Foi feita na diagonal (isto é, diferencaLinha é igual a diferençaColuna).
     */
    if (diferencaColuna != diferencaLinha) return(JOGADA_INVALIDA_MOTIVO_MOVIMENTO_NAO_DIAGONAL);

    /*
     * 2) Se casa de destino está vazia.
     */
    if (tabuleiro->casas[para->linha][para->coluna].ocupacao != NULL) return(JOGADA_INVALIDA_MOTIVO_CASA_DESTINO_OCUPADA);

    /*
     * 4) Se havia exatamente uma peça adversária nas casas puladas. Para testar
     * essa condição, iteramos pelas casas intermediárias.
     */
    pecasCapturadas = 0;
    for (i = 1; i < diferencaColuna; i++) {

        /**
         * Calculamos os índices (linha e coluna) da próxima casa intermediária.
         */
        proximaCasaLinha = de->linha + i * (para->linha - de->linha) / diferencaLinha;
        proximaCasaColuna = de->coluna + i * (para->coluna - de->coluna) / diferencaColuna;

        /**
         * Se a casa estava vazia, podemos ignorá-la.
         */
        if (tabuleiro->casas[proximaCasaLinha][proximaCasaColuna].ocupacao == NULL) continue ;

        /**
         * Casa não está vazia. Se já havíamos capturado uma peça antes, então essa é
         * a segunda, o que vai contra as regras (cada movimento pode capturar apenas
         * uma peça).
         */
        if (pecasCapturadas > 0) return(JOGADA_INVALIDA_MOTIVO_MULTIPLAS_PECAS_PULADAS);

        /**
         * Se chegamos aqui, então essa seria a primeira peça capturada nesse movimento.
         */
        _pecaCapturada = tabuleiro->casas[proximaCasaLinha][proximaCasaColuna].ocupacao;

        /**
         * Como um último teste relativo a essa casa, precisamos verificar se a peça capturada
         * é da cor do adversário. Caso contrário, movimento é inválido.
         */
        if (vez == VEZ_BRANCAS) {

            if (_pecaCapturada->cor == PECA_BRANCA) return(JOGADA_INVALIDA_MOTIVO_MESMA_COR_PULADA);
        }
        else {

            if (_pecaCapturada->cor == PECA_PRETA) return(JOGADA_INVALIDA_MOTIVO_MESMA_COR_PULADA);
        }

        /**
         * Se chegamos até aqui, captura é válida. Vamos armazenar essa informação na
         * variável pecasCapturadas para evitarmos capturas duplas no futuro.
         */
        pecasCapturadas = pecasCapturadas + 1;

        /**
         * Além disso, vamos remover a peça capturada do tabuleiro.
         */
        tabuleiro->casas[proximaCasaLinha][proximaCasaColuna].ocupacao = NULL;
    }

    /**
     * Ao final da repetição, ainda precisamos verificar se de fato houve captura.
     * Se não, isso é um erro.
     */
    if (pecasCapturadas == 0) return(JOGADA_INVALIDA_MOTIVO_MOVIMENTO_SEM_CAPTURA);

    /**
     * Por fim, atribuímos o ponteiro da peça capturada para o parâmetro de saída
     * e retornamos sucesso.
     */
    * pecaCapturada = _pecaCapturada;
    return(JOGADA_INVALIDA_MOTIVO_VALIDA);
}

/**
 * Função auxiliar à função jogadaValidaExecuta(). Em particular, essa função é 
 * especializada para o caso de movimentações com uma dama. A função itera pelos
 * vários movimentos que compõem a jogada especificada, verificando se os mesmos
 * estão de acordo com as regras do jogo.
 * 
 * Parâmetros:
 *  - jogada: ponteiro para uma lista de elementos do tipo t_coordenada. Cada
 * elemento identifica a coordenada de uma das casas percorridas pela dama 
 * durante a jogada.
 *  - tabuleiro: ponteiro para uma estrutura do tipo t_tabuleiro que representa o 
 * estado atual do tabuleiro.
 *  - vez: VEZ_BRANCAS ou VEZ_PRETAS indicando a vez atual.
 *  - nCapturasMelhorJogada: indica o número máximo de capturas possíveis nesse
 * momento (para verificação da lei da maioria).
 * 
 * Retorno: constante do tipo t_jogadaInvalidaMotivo indicando sucesso no movimento
 * ou o motivo para o movimento ser inválido.
 */
t_jogadaInvalidaMotivo jogadaValidaExecutaDama(t_lista * jogada, t_tabuleiro * tabuleiro, int vez, int nCapturasMelhorJogada) {

    int diferencaLinha, diferencaColuna;
    int pecasCapturadas;
    int proximaCasaLinha, proximaCasaColuna;
    t_coordenada * de, * para;
    int i;
    t_peca * pecasRetiradas[16], * pecaCapturada;   // pecasRetiradas guarda todas as peças que foram retiradas do tabuleiro durante a jogada.
    int nPecasRetiradas;
    t_tabuleiro novoTabuleiro;      // Usamos uma cópia do tabuleiro original para evitar fazer modificações erradas no tabuleiro do jogo.
    t_jogadaInvalidaMotivo motivo;
    t_lista * lista;

    /* 
     * Temos que verificar se cada
     * uma das coordenadas posteriores é possível de acordo
     * com a cor da peça jogada, a coordenada anterior e se há 
     * ou não peças sendo capturadas no caminho.
     * 
     * A primeira movimentação pode ser de dois tipos: com 
     * captura de outra peça ou sem captura de outra peça. Por isso, 
     * tratamos essa movimentação em separado.
     * 
     * Começamos calculando o número de linhas e colunas percorridas pelo movimento.
     * Como se trata de uma dama, não faz diferença a direção do movimento, então
     * calculamos esses valores em valor absoluto.
     */
    de = listaPrimeiro(jogada);
    para = listaProximo(jogada);
    diferencaLinha = de->linha - para->linha;
    if (diferencaLinha < 0) diferencaLinha = -diferencaLinha;
    diferencaColuna = de->coluna - para->coluna;
    if (diferencaColuna < 0) diferencaColuna = -diferencaColuna;

    /*
     * Com ou sem captura, movimentação tem que ser feita na 
     * diagonal (isto é, diferencaLinha é igual a diferençaColuna).
     */
    if (diferencaColuna != diferencaLinha) return(JOGADA_INVALIDA_MOTIVO_MOVIMENTO_NAO_DIAGONAL);

    /*
     * Com ou sem captura, casa de destino deve estar vazia.
     */
    if (tabuleiro->casas[para->linha][para->coluna].ocupacao != NULL) return(JOGADA_INVALIDA_MOTIVO_CASA_DESTINO_OCUPADA);

    /*
     * Aqui, distinguimos entre um movimento com captura (permitindo 
     * outros movimentos) e um sem captura (necessariamente único).
     * Como é possível que alguns dos movimentos contenham captura de
     * peças, vamos criar uma cópia do tabuleiro. Começamos pelo
     * primeiro movimento.
     */
    novoTabuleiro = * tabuleiro;
    nPecasRetiradas = 0;
    pecasCapturadas = 0;
    for (i = 1; i < diferencaColuna; i++) {

        /**
         * Cálculo das coordenadas da próxima casa na diagonal do movimento.
         */
        proximaCasaLinha = de->linha + i * (para->linha - de->linha) / diferencaLinha;
        proximaCasaColuna = de->coluna + i * (para->coluna - de->coluna) / diferencaColuna;

        if (tabuleiro->casas[proximaCasaLinha][proximaCasaColuna].ocupacao == NULL) continue ;

        /*
         * Mais de uma peça capturada em um mesmo movimento. Movimento
         * inválido.
         */
        if (pecasCapturadas > 0) return(JOGADA_INVALIDA_MOTIVO_MULTIPLAS_PECAS_PULADAS);

        /*
         * Peça capturada era do adversário?
         */
        pecaCapturada = tabuleiro->casas[proximaCasaLinha][proximaCasaColuna].ocupacao; 
        if (vez == VEZ_BRANCAS) {

            if (pecaCapturada->cor == PECA_BRANCA) return(JOGADA_INVALIDA_MOTIVO_MESMA_COR_PULADA);
        }
        else {

            if (pecaCapturada->cor == PECA_PRETA) return(JOGADA_INVALIDA_MOTIVO_MESMA_COR_PULADA);
        }

        /**
         * Atualizar número de peças capturadas para evitar capturas duplas no 
         * mesmo movimento.
         */
        pecasCapturadas = pecasCapturadas + 1;

        /**
         * Armazenar a peça capturada em um vetor para processamento posterior.
         */
        pecasRetiradas[nPecasRetiradas++] = pecaCapturada;

        /**
         * Deixar casa da peça capturada vazia.
         */
        novoTabuleiro.casas[proximaCasaLinha][proximaCasaColuna].ocupacao = NULL;
    }

    if (pecasCapturadas == 0) {

        /*
         * Movimento sem captura. É válido, desde que não haja outros e 
         * que não haja jogadas possíveis com captura de peças.
         */
        if (listaProximo(jogada) == NULL && nCapturasMelhorJogada == 0) return(JOGADA_INVALIDA_MOTIVO_VALIDA);   
        else return(JOGADA_INVALIDA_MOTIVO_LEI_DA_MAIORIA);
    }
    else {

        /* 
         * Usamos o parâmetro do número de capturas máximo para
         * contar o número de capturas da jogada analisada.
         * Ao final da execução dessa função, esse valor tem que ser 0.
         */
        nCapturasMelhorJogada = nCapturasMelhorJogada - 1;
    }
    
    /* 
     * Se chegamos até aqui, primeiro movimento da jogada estava ok e
     * foi um movimento de captura, permitindo outros.
     * Passamos à verificação dos demais.
     */
    de = para;
    para = listaProximo(jogada);
    while(para != NULL) {

        motivo = jogadaValidaExecutaDamaCaptura(de, para, & novoTabuleiro, vez, & pecaCapturada);
        if (motivo != JOGADA_INVALIDA_MOTIVO_VALIDA) return(motivo);

        nCapturasMelhorJogada = nCapturasMelhorJogada - 1;

        /*
         * Adicionar à lista de peçar retiradas para controle posterior.
         */
        pecasRetiradas[nPecasRetiradas++] = pecaCapturada;

        /*
         * Avançar análise para próximo movimento da jogada.
         */
        de = para;
        para = listaProximo(jogada);
    }

    /* 
     * Verificar se Lei da Maioria está sendo atendida. Número de capturas
     * realizadas deve ser igual ao número máximo de capturas possível.
     * Isso é equivalente ao parâmetro nCapturasMelhorJogada ser zero nesse
     * ponto.
     */
    if (nCapturasMelhorJogada > 0) return(JOGADA_INVALIDA_MOTIVO_LEI_DA_MAIORIA);

    /* 
     * Atualizar tabuleiro original com o estado após jogada. A parte mais
     * complexa é remover cada uma das peças removidas da lista de peças
     * ainda em jogo.
     */

    if (vez == VEZ_PRETAS) lista = & (tabuleiro->listaPecasBrancas);
    else lista = & (tabuleiro->listaPecasPretas);

    * tabuleiro = novoTabuleiro;
    for (i = 0; i < nPecasRetiradas; i++) {

        listaRemove(lista, pecasRetiradas[i]);
    }

    /**
     * Finalmente, podemos retornar sucesso.
     */

    return(JOGADA_INVALIDA_MOTIVO_VALIDA);
}

/**
 * Função auxiliar à função jogadaValidaExecutaPeca, especializada para avaliar movimentos
 * que envolvem captura de peças. Função verifica o movimento está de acordo
 * com as regras e, adicionalmente, se de fato o movimento resulta em uma 
 * captura de peça adversária. Ao final da execução, função retorna uma constante
 * do tipo t_jogadaInvalidaMotivo indicando o motivo da falha do movimento ou 
 * sucesso. Além disso, em caso de sucesso a função retorna um ponteiro para
 * a peça capturada.
 * 
 * Parâmetros:
 *  - de: ponteiro para uma estrutura do tipo t_coordenada indicando a coordenada
 * de origem da peça movida.
 *  - para: ponteiro para uma estrutura do tipo t_coordenada indicando a coordenada
 * de destino da peça movida.
 *  - tabuleiro: ponteiro para uma estrutura do tipo t_tabuleiro indicando o estado
 * atual do tabuleiro (possivelmente já alterado por outros movimentos da jogada
 * sendo avaliada).
 *  - vez: VEZ_BRANCAS ou VEZ_PRETAS, indicando de qual jogador é a vez da jogada
 * atual.
 *  - pecaCapturada[parâmetro de saída]: ponteiro para um ponteiro de uma estrutura
 * do tipo t_peca. Ao final da função, se movimento resultou em captura, esse 
 * parâmetro aponta para a peça capturada.
 * 
 * Retorno: constante do tipo t_jogadaInvalidaMotivo indicando sucesso no movimento
 * ou o motivo para o movimento ser inválido.
 */
t_jogadaInvalidaMotivo jogadaValidaExecutaPecaCaptura(t_coordenada * de, t_coordenada * para, t_tabuleiro * tabuleiro, int vez, t_peca ** pecaCapturada) {

    int diferencaLinha, diferencaColuna;
    int proximaCasaLinha, proximaCasaColuna;
    t_peca * pecaRetirada;

    /**
     * Começamos calculando o número de linhas e colunas percorridas pelo movimento.
     * Calculamos esses valores em valor absoluto.
     */
    diferencaLinha = de->linha - para->linha;
    if (diferencaLinha < 0) diferencaLinha = -diferencaLinha;
    diferencaColuna = de->coluna - para->coluna;
    if (diferencaColuna < 0) diferencaColuna = -diferencaColuna;

    /*
     * Essa movimentação é válida se:
     * 1) Foi feita na diagonal (isto é, diferencaLinha é igual a diferençaColuna).
     */
    if (diferencaColuna != diferencaLinha) return(JOGADA_INVALIDA_MOTIVO_MOVIMENTO_NAO_DIAGONAL);

    /*
     * 2) Se casa de destino está vazia.
     */
    if (tabuleiro->casas[para->linha][para->coluna].ocupacao != NULL) return(JOGADA_INVALIDA_MOTIVO_CASA_DESTINO_OCUPADA);

    /*
     * 3) Se pulou exatamente uma casa (ao menos uma, porque se trata de movimento
     * com captura).
     */
    if (diferencaColuna > 2) return(JOGADA_INVALIDA_MOTIVO_MULTIPLAS_CASAS_PULADAS);
    if (diferencaColuna < 2) return(JOGADA_INVALIDA_MOTIVO_MOVIMENTO_SEM_CAPTURA);

    /*
     * 4) Se havia exatamente uma peça adversária na casa pulada. Começamos
     * a avaliar isso calculando as coordenadas da casa pulada como as médias
     * (para linha e coluna) das coordenadas de origem e destino.
     */
    proximaCasaLinha = (de->linha + para->linha) / 2;
    proximaCasaColuna = (de->coluna + para->coluna) / 2;

    /**
     * Agora inspecionamos a peça localizada na casa pulada.
     */
    pecaRetirada = tabuleiro->casas[proximaCasaLinha][proximaCasaColuna].ocupacao;

    /**
     * Se a casa estava vazia, o movimento é inválido.
     */
    if (pecaRetirada == NULL) return(JOGADA_INVALIDA_MOTIVO_MULTIPLAS_CASAS_PULADAS);

    /**
     * Se havia uma peça, ainda precisamos garantir que a peça era do adversário.
     */
    if (vez == VEZ_BRANCAS) {

        if (pecaRetirada->cor == PECA_BRANCA) return(JOGADA_INVALIDA_MOTIVO_MESMA_COR_PULADA);
    }
    else {

        if (pecaRetirada->cor == PECA_PRETA) return(JOGADA_INVALIDA_MOTIVO_MESMA_COR_PULADA);
    }

    /* 
     * Se chegamos aqui, movimento é válido. Retirar peça da matriz do tabuleiro.
     */
    tabuleiro->casas[proximaCasaLinha][proximaCasaColuna].ocupacao = NULL;

    /**
     * Atribuir ponteiro da peça capturada ao parâmetro de saída.
     */
    * pecaCapturada = pecaRetirada;
    
    /**
     * Retornar sucesso.
     */
    return(JOGADA_INVALIDA_MOTIVO_VALIDA);
}

/**
 * Função auxiliar à função jogadaValidaExecuta(). Em particular, essa função é 
 * especializada para o caso de movimentações com uma peça normal. A função itera pelos
 * vários movimentos que compõem a jogada especificada, verificando se os mesmos
 * estão de acordo com as regras do jogo.
 * 
 * Parâmetros:
 *  - jogada: ponteiro para uma lista de elementos do tipo t_coordenada. Cada
 * elemento identifica a coordenada de uma das casas percorridas pela dama 
 * durante a jogada.
 *  - tabuleiro: ponteiro para uma estrutura do tipo t_tabuleiro que representa o 
 * estado atual do tabuleiro.
 *  - vez: VEZ_BRANCAS ou VEZ_PRETAS indicando a vez atual.
 *  - nCapturasMelhorJogada: indica o número máximo de capturas possíveis nesse
 * momento (para verificação da lei da maioria).
 * 
 * Retorno: constante do tipo t_jogadaInvalidaMotivo indicando sucesso no movimento
 * ou o motivo para o movimento ser inválido.
 */
t_jogadaInvalidaMotivo jogadaValidaExecutaPecaNormal(t_lista * jogada, t_tabuleiro * tabuleiro, int vez, int nCapturasMelhorJogada) {

    int diferencaLinha, diferencaColuna;
    t_coordenada * de, * para;
    t_tabuleiro novoTabuleiro;
    t_peca * pecasRetiradas[16], * pecaCapturada;
    int nPecasRetiradas;
    int i;
    t_jogadaInvalidaMotivo motivo;

    /* 
     * Temos que verificar se cada
     * uma das coordenadas posteriores é possível de acordo
     * com a cor da peça jogada, a coordenada anterior e se 
     * há ou não peças sendo capturadas no caminho.
     * 
     * A primeira movimentação pode ser de dois tipos: com 
     * captura de outra peça ou sem captura de outra peça. Por isso,
     * tratamos essa movimentação em separado.
     * 
     * Começamos obtendo as duas primeiras coordenadas da jogada,
     * que indicam a casa de origem e a casa de destino do primeiro 
     * movimento.
     */
    de = listaPrimeiro(jogada);
    para = listaProximo(jogada);

    /**
     * Agora calculamos o número de linhas e colunas percorridas pelo movimento.
     * Calculamos esses valores em valor absoluto.
     */
    diferencaLinha = de->linha - para->linha;
    if (diferencaLinha < 0) diferencaLinha = -diferencaLinha;
    diferencaColuna = de->coluna - para->coluna;
    if (diferencaColuna < 0) diferencaColuna = -diferencaColuna;

    /**
     * A diferença é de apenas uma casa?
     */
    if (diferencaLinha == 1 && diferencaColuna == 1) {

        /* 
         * Movimentação sem captura de peça adversária. Nesse caso,
         * jogada é válida se:
         * 1) Casa de destino é vazia.
         */
        if (tabuleiro->casas[para->linha][para->coluna].ocupacao != NULL) return(JOGADA_INVALIDA_MOTIVO_CASA_DESTINO_OCUPADA);

        /*
         * 2) Se peça pode ir na direção especificada com base na sua cor.
         */
        if (vez == VEZ_BRANCAS && de->linha - para->linha < 0) return(JOGADA_INVALIDA_MOTIVO_DIRECAO_PROIBIDA);
        if (vez == VEZ_PRETAS && de->linha - para->linha > 0) return(JOGADA_INVALIDA_MOTIVO_DIRECAO_PROIBIDA);

        /*
         * 3) Não há outra movimentação posterior especificada.
         */
        if (listaProximo(jogada) != NULL) return(JOGADA_INVALIDA_MOTIVO_MULTIPLOS_MOVIMENTOS_SEM_CAPTURA);

        /*
         * 4) Não há outras jogadas com captura de peça possíveis.
         */
        if (nCapturasMelhorJogada > 0) return(JOGADA_INVALIDA_MOTIVO_LEI_DA_MAIORIA);

        /* 
         * Neste ponto, jogada com certeza é válida.
         */
        return(JOGADA_INVALIDA_MOTIVO_VALIDA);
    }

    /*
     * Se chegamos até aqui, primeiro movimento é uma captura de peça. Todos os demais
     * movimentos (se houver) também precisam ser de captura de peça. Assim,
     * faremos o mesmo tratamento para todas as movimentações. Além disso, criamos
     * uma cópia do tabuleiro para testar as alterações antes de modificar o tabuleiro
     * original, porque não temos certeza ainda de que a jogada é totalmente válida. 
     */
    novoTabuleiro = * tabuleiro;

    /**
     * Vamos guardar o número de peças capturadas ao longo da jogada para testar ao
     * fim se lei da maioria está sendo respeitada.
     */
    nPecasRetiradas = 0;

    /**
     * Obtemos as duas primeiras coordenadas da jogada,
     * que indicam a casa de origem e a casa de destino do primeiro 
     * movimento.
     */
    de = listaPrimeiro(jogada);
    para = listaProximo(jogada);

    /**
     * Continuamos iterando pelas coordenadas, até o final da lista.
     */
    while(para != NULL) {

        /**
         * Para simplificar a lógica dessa função, delegamos a avaliação 
         * da validade desse próximo movimento para uma função auxiliar.
         * Se ela retornar que o movimento é inválido, toda a jogada é
         * inválida.
         */
        motivo = jogadaValidaExecutaPecaCaptura(de, para, & novoTabuleiro, vez, & pecaCapturada);
        if (motivo != JOGADA_INVALIDA_MOTIVO_VALIDA) return(motivo);

        /*
         * Movimento é válido. Adicionar peça capturada à lista de peçar 
         * retiradas para controle posterior.
         */
        pecasRetiradas[nPecasRetiradas++] = pecaCapturada;

        /*
         * Manter o controle de quantas capturas faltam para alcançar o número
         * máximo de capturas possíveis. Isso permitirá avaliar a Lei da Maioria.
         */
        nCapturasMelhorJogada = nCapturasMelhorJogada - 1;
        
        /*
         * Avançar para próxima movimentação.
         */
        de = para;
        para = listaProximo(jogada);
    }

    /* 
     * Avaliar se a Lei da Maioria foi atendida pela jogada.
     */
    if (nCapturasMelhorJogada > 0) return(JOGADA_INVALIDA_MOTIVO_LEI_DA_MAIORIA);

    /* 
     * Atualizar tabuleiro original com o estado após jogada. A parte mais
     * complexa é remover cada uma das peças removidas da lista de peças
     * ainda em jogo.
     */
    * tabuleiro = novoTabuleiro;
    for (i = 0; i < nPecasRetiradas; i++) {

        if (vez == VEZ_PRETAS)
            listaRemove(& (tabuleiro->listaPecasBrancas), pecasRetiradas[i]);
        else
            listaRemove(& (tabuleiro->listaPecasPretas), pecasRetiradas[i]);
    }

    /**
     * Finalmente, podemos retornar sucesso.
     */
    return(JOGADA_INVALIDA_MOTIVO_VALIDA);
}

t_jogadaInvalidaMotivo jogadaValidaExecuta(t_lista * jogada, t_tabuleiro * tabuleiro, int vez) {

    t_peca * peca;
    t_coordenada * de, * para;
    char melhorJogada[39];
    int nCapturasMelhorJogada;
    t_jogadaInvalidaMotivo motivo;

    /*
     * Antes de começar a verificar a jogada em si,
     * computamos o número máximo de capturas possíveis 
     * para a atual jogada. Esse valor será usado para
     * verificar se a Lei da Maioria está sendo respeitada.
     */
    nCapturasMelhorJogada = jogadaEncontraJogadaComMaisCapturas(tabuleiro, vez, melhorJogada);

    /*
     * Primeira verificação: jogada precisa conter ao 
     * menos duas coordenadas.
     */
    de = listaPrimeiro(jogada);
    para = listaProximo(jogada);
    if (de == NULL) return(JOGADA_INVALIDA_MOTIVO_SEM_MOVIMENTO);
    if (para == NULL) return(JOGADA_INVALIDA_MOTIVO_SEM_MOVIMENTO);

    /*
     * Segunda verificação: primeira coordenada deve
     * conter peça da cor correspondente ao jogador
     * da vez.
     */
    peca = tabuleiro->casas[de->linha][de->coluna].ocupacao;
    if (peca == NULL) return(JOGADA_INVALIDA_MOTIVO_CASA_ORIGEM_VAZIA);
    if (vez == VEZ_BRANCAS && peca->cor == PECA_PRETA) return(JOGADA_INVALIDA_MOTIVO_PECA_COR_ERRADA);
    if (vez == VEZ_PRETAS && peca->cor == PECA_BRANCA) return(JOGADA_INVALIDA_MOTIVO_PECA_COR_ERRADA);

    /*
     * Deste ponto em diante, as demais verificações dependem
     * bastante do tipo de peça (dama ou não). Assim, para
     * simplificar, vamos delegar as verificações a duas 
     * funções específicas.
     */
    if (peca->tipo == PECA_NORMAL) {

        /*
         * Peça normal.
         */
        motivo = jogadaValidaExecutaPecaNormal(jogada, tabuleiro, vez, nCapturasMelhorJogada); 
        if (motivo != JOGADA_INVALIDA_MOTIVO_VALIDA) return(motivo);
    }
    else {

        /*
         * Dama.
         */
        motivo = jogadaValidaExecutaDama(jogada, tabuleiro, vez, nCapturasMelhorJogada);
        if (motivo != JOGADA_INVALIDA_MOTIVO_VALIDA) return(motivo);
    }

    /*
     * Se chegamos até aqui, a jogada é completamente válida e potenciais
     * capturas já foram atualizadas no tabuleiro. Última ação necessária
     * é atualizar posição da peça movida. Começamos achando as coordenadas
     * finais.
     */
    de = listaPrimeiro(jogada);
    para = listaProximo(jogada);
    while(para != NULL) {

        de = para;
        para = listaProximo(jogada);
    }

    /*
     * Neste ponto, variável 'de' aponta para a última coordenada da jogada.
     * Também precisamos da primeira. Vamos guardar a última em 'para' e 
     * a primeira em 'de'.
     */
    para = de;
    de = listaPrimeiro(jogada);

    /* 
     * Trocar posição da peça.
     */
    tabuleiro->casas[para->linha][para->coluna].ocupacao = tabuleiro->casas[de->linha][de->coluna].ocupacao;
    tabuleiro->casas[de->linha][de->coluna].ocupacao = NULL;
    tabuleiro->casas[para->linha][para->coluna].ocupacao->linha = para->linha;
    tabuleiro->casas[para->linha][para->coluna].ocupacao->coluna = para->coluna;

    /* 
     * Por fim, checamos se a peça parou na última linha do adversário.
     * Neste caso, peça é promovida a dama (se já não é).
     */
    if (vez == VEZ_BRANCAS && para->linha == 0) tabuleiro->casas[para->linha][para->coluna].ocupacao->tipo = PECA_DAMA;
    if (vez == VEZ_PRETAS && para->linha == 7) tabuleiro->casas[para->linha][para->coluna].ocupacao->tipo = PECA_DAMA;

    return(JOGADA_INVALIDA_MOTIVO_VALIDA);
}

int jogadaPecasComMovimento(t_tabuleiro * tabuleiro, int vez) {

    t_peca * peca;  // Ponteiro para iterar pelas peças do jogador.
    int nPecasComMovimento = 0; // Contador do número de peças com movimentos válidos.
    /**
     * A variável declarada a seguir é um vetor de 4 posições de uma simples
     * estrutura composta de dois campos: um número de linha e um número de coluna.
     * A ideia é usarmos esse vetor para armazenar as possíveis direções de movimentação
     * de uma peça (frente-esquerda, frente-direita, trás-esquerda e trás-direita).
     * Essas direções são representadas como deslocamentos nas linhas e colunas. Por 
     * exemplo, um valor de 1 no campo linha significa mover a peça na direção crescente
     * dos índices de linha. Um valor de -1 representa mover a peça no sentido oposto.
     * 
     * Note que já iniciamos o vetor com os valores que representam as quatro direções
     * possíveis.
     */
    struct {
        int linha;
        int coluna;
    } direcoes[4] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    int i;
    int casaAlvoLinha, casaAlvoColuna;
    t_corPeca adversario;
    t_lista * lista;    // Ponteiro para lista, apontará para a lista de peças da cor da vez.

    /**
     * Configurar cor da peça adversária e ponteiro para a lista de peças
     * de acordo com o valor do parâmetro vez.
     */
    if (vez == VEZ_BRANCAS) {
        
        lista = & (tabuleiro->listaPecasBrancas);
        adversario = PECA_PRETA;
    }
    else {
        
        lista = & (tabuleiro->listaPecasPretas);
        adversario = PECA_BRANCA;
    }

    /**
     * Vamos iterar pelas peças ainda em jogo do jogador da vez.
     * Começamos pegando a primeira da lista.
     */
    peca = listaPrimeiro(lista);

    /**
     * Iteramos até que não haja mais peças na lista.
     */
    while(peca) {

        /*
         * Para cada peça, avaliamos movimentos nas 4 direções
         * possíveis.
         */
        for (i = 0; i < 4; i++) {

            /**
             * Calculamos a casa alvo como a primeira casa adjacente
             * na diagonal definida pela i-ésima direção.
             */
            casaAlvoLinha = peca->linha + direcoes[i].linha;
            casaAlvoColuna = peca->coluna + direcoes[i].coluna;

            /**
             * Casa alvo ainda está dentro do tabuleiro?
             */
            if (casaAlvoLinha < 0 || casaAlvoLinha > 7) continue ;
            if (casaAlvoColuna < 0 || casaAlvoColuna > 7) continue ;

            /**
             * Casa alvo está vazia?
             */
            if (tabuleiro->casas[casaAlvoLinha][casaAlvoColuna].ocupacao == NULL) {

                /**
                 * Sim. Precisamos ainda verificar se essa peça pode 
                 * se mover nessa direção, dado que não é um movimento
                 * de captura. Isso é verdade se a peça é uma dama OU
                 * se é uma peça branca e a direção é no sentido decrescente
                 * das linhas OU se a peça é preta e o movimento é no sentido
                 * crescente das linhas.
                 */
                if ((vez == VEZ_BRANCAS && direcoes[i].linha == -1) ||
                    (vez == VEZ_PRETAS && direcoes[i].linha == 1) ||
                    peca->tipo == PECA_DAMA) {

                    nPecasComMovimento = nPecasComMovimento + 1;
                    break ;
                }
            }
            else {

                /**
                 * A casa adjacente está ocupada. Ainda é possível um movimento 
                 * de captura, desde que a peça que ocupa a casa seja do adversário.
                 */
                if (tabuleiro->casas[casaAlvoLinha][casaAlvoColuna].ocupacao->cor == adversario) {

                    /**
                     * Sim, a peça é do adversário. Vamos especificar uma nova casa alvo,
                     * como sendo a próxima casa na diagonal.
                     */
                    casaAlvoLinha = casaAlvoLinha + direcoes[i].linha;
                    casaAlvoColuna = casaAlvoColuna + direcoes[i].coluna;

                    /**
                     * Nova casa alvo ainda está dentro do tabuleiro?
                     */
                    if (casaAlvoLinha < 0 || casaAlvoLinha > 7) continue ;
                    if (casaAlvoColuna < 0 || casaAlvoColuna > 7) continue ;

                    /**
                     * E está vazia?
                     */
                    if (tabuleiro->casas[casaAlvoLinha][casaAlvoColuna].ocupacao == NULL) {

                        nPecasComMovimento = nPecasComMovimento + 1;
                        break ;
                    }
                }
            }
        }

        /**
         * Próxima peça na lista.
         */
        peca = listaProximo(lista);
    }

    return(nPecasComMovimento);
}

void jogadaInvalidaMotivoParaString(t_jogadaInvalidaMotivo motivo, char * motivoString) {

    switch(motivo) {

        case JOGADA_INVALIDA_MOTIVO_VALIDA:
              // Jogada é válida
            sprintf(motivoString, "Jogada totalmente valida.");
            break ;
        case JOGADA_INVALIDA_MOTIVO_MOVIMENTO_NAO_DIAGONAL:
              // Um dos movimentos especificados não é diagonal
            sprintf(motivoString, "Um dos movimentos especificados nao e diagonal.");
            break ;
        case JOGADA_INVALIDA_MOTIVO_CASA_DESTINO_OCUPADA:
                // A casa de destino de um dos movimentos está ocupada
            sprintf(motivoString, "Casa de destino de um dos movimentos esta ocupada.");
            break ;
        case JOGADA_INVALIDA_MOTIVO_MULTIPLAS_PECAS_PULADAS:
             // Tentativa de pular mais de uma peça no mesmo movimento
            sprintf(motivoString, "Um dos movimentos tenta pular multiplas pecas.");
            break ;
        case JOGADA_INVALIDA_MOTIVO_MESMA_COR_PULADA:
                // Tentativa de pular peça da mesma cor
            sprintf(motivoString, "Um dos movimentos tenta pular peca de mesma cor.");
            break ;
        case JOGADA_INVALIDA_MOTIVO_MOVIMENTO_SEM_CAPTURA:
             // Movimento sem captura após outros com captura
            sprintf(motivoString, "Apos movimentos com captura, ha um movimento que nao captura pecas.");
            break ;
        case JOGADA_INVALIDA_MOTIVO_LEI_DA_MAIORIA:
              // Jogada não respeita lei da maioria
            sprintf(motivoString, "Jogada nao respeita Lei da Maioria (i.e., nao captura o numero maximo de pecas).");
            break ;
        case JOGADA_INVALIDA_MOTIVO_MULTIPLAS_CASAS_PULADAS:
              // Peça normal tentou pular múltiplas casas vazias
            sprintf(motivoString, "Tentativa de pular multiplas casas vazias com peca normal.");
            break ;
        case JOGADA_INVALIDA_MOTIVO_DIRECAO_PROIBIDA:
             // Tentativa de movimento em direção proibida
            sprintf(motivoString, "Tentativa de pular para tras sem captura com peca normal.");
            break ;
        case JOGADA_INVALIDA_MOTIVO_MULTIPLOS_MOVIMENTOS_SEM_CAPTURA:
             // Tentativa de realizar segundo movimento sem captura no primeiro
            sprintf(motivoString, "Tentativa de realizar segundo movimento sem captura.");
            break ;
        case JOGADA_INVALIDA_MOTIVO_SEM_MOVIMENTO:
                // Não há pelo menos duas coordenadas especificadas na jogada
            sprintf(motivoString, "Nenhum movimento especificado na jogada (ao menos duas coordenadas sao necessarias).");
            break ;
        case JOGADA_INVALIDA_MOTIVO_PECA_COR_ERRADA:
              // Jogada tenta movimentar peça do adversário
            sprintf(motivoString, "Tentativa de movimentar peca do adversario.");
            break ;
        case JOGADA_INVALIDA_MOTIVO_CASA_ORIGEM_VAZIA:
               // Casa de origem da jogada não contém peça
            sprintf(motivoString, "Casa de origem da jogada nao contem peca.");
            break ;
    }

}

