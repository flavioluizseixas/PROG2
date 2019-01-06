#include "estado.h"
#include "tabuleiro.h"
#include "util.h"
#include "jogada.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int estadoSalvaEmArquivo(t_tabuleiro * tabuleiro, t_logDeJogadas * logDeJogadas, char * nomeDoArquivo) {

    FILE * arquivo;         // Ponteiro para o arquivo a ser manipulado.
    char * ponteiroJogadas; // Ponteiro para iterar pelas jogadas do log.
    t_peca * ponteiroPecas; // Ponteiro para iterar pelas listas de peças ainda em jogo.
    int numeroDePecasEmJogo;    // Número total de peças ainda em jogo (dos dois lados).
    unsigned char byte;         // Variável auxiliar que armazena valores a serem escritos no arquivo.

    /**
     * Tentativa de abertura do arquivo. Arquivo é aberto para escrita ("w")
     * e em modo binário ("b").
     */
    arquivo = fopen(nomeDoArquivo, "wb");
    if (arquivo == NULL) {

        return(FALSO);
    }

    /**
     * Primeiro campo do arquivo é o número total de peças ainda em jogo,
     * contando ambos os lados. Obtemos essa informação da função específica
     * implementada no módulo tabuleiro.h. Note que o retorno da função é 
     * do tipo int. No entanto, há, no máximo, 12 + 12 = 24 peças no tabuleiro
     * em dado momento. Assim, podemos armazenar esse valor em um único byte.
     * Para isso, fazemos a atribuição do retorno da função para a variável byte
     * que é do tipo unsigned char (basicamente, um byte interpretado sem sinal).
     * Para evitarmos warnings do compilador, incluimos um cast explícito.
     */
    numeroDePecasEmJogo = tabuleiroNumeroDePecasEmJogo(tabuleiro);
    byte = (unsigned char) numeroDePecasEmJogo;

    /**
     * Escrita do byte no arquivo. Sempre verificamos se o número de 
     * bytes escritos de fato no arquivo (retorno da função fwrite)
     * está de acordo com o solicitado. Em caso negativo, retornamos
     * FALSO para sinalizar uma falha.
     */
    if (fwrite((void *) (& byte), 1, 1, arquivo) != 1) return(FALSO);

    /**
     * Em seguida, o arquivo deve conter uma sequência de peças,
     * correspondendo às peças ainda em jogo das duas cores. Repare
     * que a cor é uma das informações da peça, então a ordem em que
     * elas são listadas no arquivo não faz diferença. Aqui, começamos
     * pelas peças brancas.
     */
    ponteiroPecas = listaPrimeiro(& (tabuleiro->listaPecasBrancas));
    while(ponteiroPecas){

        /**
         * Para cada peça da lista, escrevemos no arquivo, na ordem, as
         * informações de linha, coluna, tipo e cor. Embora todos esses
         * campos sejam declarados na estrutura t_peca como inteiros,
         * nenhum deles assume valores altos (em particular, maiores que 
         * 255). Assim, podemos guardar cada um como um simples byte.
         * Novamente, usamos a variável byte e um cast explícito para isso.
         */
        byte = (unsigned char) ponteiroPecas->linha;
        if (fwrite((void *) (& byte), 1, 1, arquivo) != 1) return(FALSO);
        byte = (unsigned char) ponteiroPecas->coluna;
        if (fwrite((void *) (& byte), 1, 1, arquivo) != 1) return(FALSO);
        byte = (unsigned char) ponteiroPecas->tipo;
        if (fwrite((void *) (& byte), 1, 1, arquivo) != 1) return(FALSO);
        byte = (unsigned char) ponteiroPecas->cor;
        if (fwrite((void *) (& byte), 1, 1, arquivo) != 1) return(FALSO);

        /**
         * Passar para a próxima peça da lista.
         */
        ponteiroPecas = listaProximo(& (tabuleiro->listaPecasBrancas));
    }

    /**
     * Agora realizamos exatamente o mesmo processo com as peças pretas.
     */
    ponteiroPecas = listaPrimeiro(& (tabuleiro->listaPecasPretas));
    while(ponteiroPecas){

        byte = (unsigned char) ponteiroPecas->linha;
        if (fwrite((void *) (& byte), 1, 1, arquivo) != 1) return(FALSO);
        byte = (unsigned char) ponteiroPecas->coluna;
        if (fwrite((void *) (& byte), 1, 1, arquivo) != 1) return(FALSO);
        byte = (unsigned char) ponteiroPecas->tipo;
        if (fwrite((void *) (& byte), 1, 1, arquivo) != 1) return(FALSO);
        byte = (unsigned char) ponteiroPecas->cor;
        if (fwrite((void *) (& byte), 1, 1, arquivo) != 1) return(FALSO);

        ponteiroPecas = listaProximo(& (tabuleiro->listaPecasPretas));
    }

    /**
     * O último bloco de informações do arquivo é o log de jogadas.
     * Simplesmente escrevemos as descrições textuais das jogadas no 
     * arquivo, sempre terminadas pelo caractere '\0'.
     * Para isso, iteramos pela lista de jogadas.
     */
    ponteiroJogadas = listaPrimeiro(logDeJogadas);
    while(ponteiroJogadas) {

        /**
         * O detalhe aqui é o número de bytes a serem escritos: usamos
         * strlen() + 1 porque a função strlen() retorna o número de 
         * caracteres da string, excetuando o terminador '\0'. No entanto,
         * para o formato do arquivo é importante a existência do terminador 
         * para demarcar o fim de uma jogada. Assim, incrementamos a saída
         * da strlen em uma unidade.
         */
        if (fwrite((void *) ponteiroJogadas, 1, strlen(ponteiroJogadas) + 1, arquivo) != strlen(ponteiroJogadas) + 1) return(FALSO);

        /**
         * Passamos para a próxima jogada.
         */
        ponteiroJogadas = listaProximo(logDeJogadas);
    }

    /**
     * Finalmente, fechamos o arquivo.
     */
    fclose(arquivo);

    /**
     * Se chegamos até aqui, a operação foi bem-sucedida.
     */
    return(VERDADEIRO);
}


int estadoRestauraDeArquivo(t_tabuleiro * tabuleiro, t_logDeJogadas * logDeJogadas, int * vez, char * nomeDoArquivo) {

    FILE * arquivo;     // Ponteiro para o arquivo manipulado.
    int numeroDePecasEmJogo;    // Número total de peças em jogo, segundo o arquivo.
    unsigned char byte; // Variável que guarda um byte lido do arquivo.
    char ch;            // Variável que guarda um caractere lido do arquivo.
    int i;              // Índice de repetição para ler as peças.
    t_peca * novaPeca;  // Ponteiro para criação e preenchimento de nova peça.
    char novaJogada[39];    // String para armazenar uma nova jogada lida do arquivo.

    /**
     * Tentativa de abertura do arquivo. Modo leitura ("r") binária ("b").
     */
    arquivo = fopen(nomeDoArquivo, "rb");
    if (arquivo == NULL) {

        return(FALSO);
    }

    /*
     * Inicializar estruturas do tabuleiro, incluindo as listas de peças
     * em jogo para cada uma das cores.
     */
    tabuleiroInicializaCasas(tabuleiro);
    tabuleiro->listaPecasBrancas = listaInicializa();
    tabuleiro->listaPecasPretas = listaInicializa();

    /**
     * Primeiro byte do arquivo indica o número total de peças em 
     * jogo. Cada chamada a função fread é acompanhada de um teste
     * para verificar se o número de bytes lidos casa com o número
     * de bytes solicitado.
     */
    if (fread((void *) & byte, 1, 1, arquivo) != 1) return(FALSO);
    numeroDePecasEmJogo = (int) byte;

    /**
     * Iteramos pelo número de peças, lendo os dados do arquivo e 
     * criando novas peças a inserindo na lista.
     */
    for (i = 0; i < numeroDePecasEmJogo; i++) {

        /**
         * Tentar alocar memória para a nova peça.
         */
        novaPeca = (t_peca *) malloc(sizeof(t_peca));
        if (novaPeca == NULL) {

            printf("Falha ao alocar memoria!\n");
            exit(1);
        }

        /**
         * Lemos os próximos 4 bytes do arquivo, que representam as 
         * informações da nova peça.
         */
        if (fread((void *) & byte, 1, 1, arquivo) != 1) return(FALSO);
        novaPeca->linha = (int) byte;
        if (fread((void *) & byte, 1, 1, arquivo) != 1) return(FALSO);
        novaPeca->coluna = (int) byte;
        if (fread((void *) & byte, 1, 1, arquivo) != 1) return(FALSO);
        novaPeca->tipo = (int) byte;
        if (fread((void *) & byte, 1, 1, arquivo) != 1) return(FALSO);
        novaPeca->cor = (int) byte;

        /**
         * A princípio, as peças podem estar listadas no arquivo em
         * qualquer ordem. Assim, decidimos em qual lista inserir a
         * nova peça com base no atributo cor.
         */
        if (novaPeca->cor == PECA_BRANCA)
            listaAdiciona(& (tabuleiro->listaPecasBrancas), novaPeca);
        else
            listaAdiciona(& (tabuleiro->listaPecasPretas), novaPeca);

        /**
         * Além de inserir na lista adequada, peça tem que ser posicionada
         * na casa certa no tabuleiro. Fazemos isso com base nos atributos
         * linha e coluna.
         */
        tabuleiro->casas[novaPeca->linha][novaPeca->coluna].ocupacao = novaPeca;
    }

    /**
     * Prosseguimos com a leitura da sequência de jogadas para preenchimento
     * do log. Além de preencher o log, precisamos marcar de quem é a vez de
     * fazer a próxima jogada. Pela regra, a primeira jogada é das brancas.
     * Assim, inicializamos o parâmetro vez para VEZ_BRANCAS e alternamos a
     * partir daí.
     */
    * vez = VEZ_BRANCAS;
    
    /**
     * A variável i armazena a posição do próximo byte na string que armazena
     * a jogada.
     */
    i = 0;

    /**
     * Inicializamos um novo log de jogadas.
     */
    * logDeJogadas = logDeJogadasInicializa();
    
    /**
     * A partir daqui, lemos o arquivo byte a byte, até o fim do arquivo
     * (i.e.), até que o caractere lido seja EOF).
     */
    ch = fgetc(arquivo);
    while(ch != EOF) {

        /**
         * Concatenamos o caractere lido na string da jogada.
         */
        novaJogada[i++] = ch;

        /**
         * Caractere é um terminador?
         */
        if (ch == '\0') {

            /**
             * Se sim, a jogada atual terminou. Adicionamos ao
             * log.
             */
            logDeJogadasAdiciona(logDeJogadas, novaJogada);

            /**
             * Zeramos a variável i para começar a preencher do
             * início a string da próxima jogada.
             */
            i = 0;

            /**
             * Também alternamos a vez.
             */
            if (* vez == VEZ_BRANCAS) * vez = VEZ_PRETAS;
            else * vez = VEZ_BRANCAS;
        }

        /**
         * Lemos o próximo caractere do arquivo.
         */
        ch = fgetc(arquivo);
    }

    /**
     * Fechamos o arquivo.
     */
    fclose(arquivo);

    /**
     * Última verificação: se i > 0, então lemos alguma string de
     * jogada pela metade. Isso não é correto, então retornamos
     * um erro.
     */
    if (i != 0) return(FALSO);
    else return(VERDADEIRO);
}
