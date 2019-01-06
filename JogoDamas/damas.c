#include <stdio.h>
#include <stdlib.h>

#include "parametros.h"
#include "tabuleiro.h"
#include "interfaceMonocromatica.h"
#include "interfaceColorida.h"
#include "jogada.h"
#include "util.h"
#include "logDeJogadas.h"
#include "estado.h"

int main(int argc, char * argv[]) {

    t_configuracao conf;    // Variável que armazena as configurações lidas dos argumentos de linha de comando.
    t_tabuleiro tabuleiro;  // Variável que armazena o tabuleiro.
    int vez;                // Variável que armazena a vez atual.
    t_lista jogada;         // Variável auxiliar que armazena jogada interpretada do teclado.
    char jogadaString[39];  // Idem ao anterior, mas em formato textual.
    t_jogadaInvalidaMotivo motivo;  // Armazena retorno da função que avalia validade de uma jogada.
    char motivoString[255]; // Idem ao anterior, mas em formato textual.
    t_logDeJogadas logDeJogadas;    // Log das jogadas realizadas.
    int opcao;              // Opção especificada pelo usuário no menu.
    char nomeDoArquivo[255];    // Nome de arquivo especificado pelo usuário para guardar log de jogadas ou estado.
    char ch;                // Caractere lido do teclado.

    /**
     * Ler e interpretar parâmetros de linha de comando.
     */
    conf = parametrosLeitura(argc, argv);

    /**
     * Opção de restaurar estado foi especificada?
     */
    if (conf.restauraEstado == NULL) {

        /**
         * Não. Inicializamos tabuleiro e log de jogadas zerados.
         * Por regra, vez começa com as peças brancas.
         */
        tabuleiro = tabuleiroInicializa();
        logDeJogadas = logDeJogadasInicializa();
        vez = VEZ_BRANCAS;
    }
    else {

        /**
         * Sim. Estado é carregado a partir do arquivo especificado pelo usuário.
         */
        if (estadoRestauraDeArquivo(& tabuleiro, & logDeJogadas, & vez, conf.restauraEstado) == FALSO) {

            /**
             * Houve algum erro na leitura do arquivo. Abortar.
             */
            printf("Falha ao tentar restaurar estado a partir do arquivo. Verifique o caminho\nespecificado e o formato do arquivo.\n");
            exit(1);
        }
    }

    /** 
     * Se a interface é colorida, limpamos a tela.
     */
    if (conf.interfaceColorida == VERDADEIRO) {

        /**
         * A função que limpa a tela é definida em uma biblioteca
         * externa nessa implementação.
         */        
        interfaceColoridaLimpaTela();

        /**
         * Usamos duas quebras de linha aqui porque as duas 
         * linhas do topo da tela são reservadas a mensagens de 
         * erro e avisos ao usuário.
         */
        printf("\n\n");
    }

    /**
     * Repetição principal do programa. Fim do jogo acontece quando
     * um dos dois times fica sem peça ou quando o time da vez não
     * tem movimentos válidos possíveis.
     */
    while(tabuleiroTimeSemPecas(& tabuleiro) == FALSO && jogadaPecasComMovimento(& tabuleiro, vez) > 0) {

        /**
         * Dependendo da configuração, usamos a interface colorida 
         * ou monocromática para imprimir o tabuleiro.
         */
        if (conf.interfaceColorida == VERDADEIRO)
            interfaceColoridaImprimeTabuleiro(tabuleiro);
        else 
            interfaceMonocromaticaImprimeTabuleiro(tabuleiro);

        /**
         * Imprimir um aviso sobre qual time deve jogar agora.
         */
        if (vez == VEZ_BRANCAS) printf("\nVez das pecas brancas. ");
        else printf("\nVez das pecas pretas. ");

        /**
         * Imprimir o menu de opções.
         */
        printf("Opcoes:\n");
        printf("\t1) Fazer proxima jogada.\n");
        printf("\t2) Salvar log de jogadas em arquivo.\n");
        printf("\t3) Salvar estado da partida em arquivo.\n");
        printf("Especifique o numero da opcao desejada -> ");

        /**
         * Leitura da opção especificada pelo usuário.
         */
        opcao = -1;
        scanf("%d", & opcao);

        /** 
         * A função scanf pode não ler tudo o que o usuário digitou 
         * antes do <enter>. Assim, usamos a função getchar() e uma 
         * repetição para terminar de ler todos os caracteres.
         */
        ch = getchar();
        while (ch != '\n') {  // Consome o que quer que tenha sobrado na linha após o número de opção.

            /**
             * Se o caractere é diferente de espaço ou de quebra de linha
             * então o usuário digitou algo além de um algarismo. Logo, 
             * a opção especificada não é válida. Representamos isso 
             * atribuindo o valor -1 à variável opção.
             */
            if (ch != ' ') opcao = -1;
            ch = getchar();
        }

        /**
         * Testamos os possíveis valores da opção especificada pelo usuário.
         */
        switch(opcao) {

            default:

                /**
                 * Não é nenhum dos valores válidos. Imprimir mensagem de
                 * erro.
                 */
                if (conf.interfaceColorida == VERDADEIRO) {

                    /**
                     * Se estamos usando a interface colorida, limpamos
                     * a tela, mudamos a cor da fonte, imprimimos e mudamos
                     * de volta.
                     */
                    interfaceColoridaLimpaTela();
                    interfaceColoridaMudaCorFonte(INTERFACE_COLORIDA_COR_VERMELHO);
                    printf("Opcao especificada e invalida!\n\n");
                    interfaceColoridaReseta();
                }
                else {

                    printf("Jogada invalida!\nRazao: espeficicacao em formato invalido.\n");
                }

                break ;
            case 1:

                /**
                 * Opção de especificação de jogada. Lemos a jogada do usuário.
                 */
                printf("Indique a jogada -> ");
                jogada = jogadaLe(jogadaString);

                if (conf.interfaceColorida == VERDADEIRO) interfaceColoridaLimpaTela();

                /**
                 * Se a função de leitura da jogada retornou uma lista vazia,
                 * especificação da jogada pelo usuário está errada.
                 */
                if (listaVazia(jogada) == VERDADEIRO) {

                    if (conf.interfaceColorida == VERDADEIRO) {

                        interfaceColoridaMudaCorFonte(INTERFACE_COLORIDA_COR_VERMELHO);
                        printf("Jogada invalida!\nRazao: espeficicacao em formato invalido.\n");
                        interfaceColoridaReseta();
                    }
                    else {

                        printf("Jogada invalida!\nRazao: espeficicacao em formato invalido.\n");
                    }
                }
                else {

                    /** 
                     * Se chegamos aqui, jogada especificada está em formato adequado.
                     * Delegamos a outra função a responsabilidade de fazer verificações
                     * adicionais de validade da jogada e, se correta, execute-a.
                     */
                    motivo = jogadaValidaExecuta(& jogada, & tabuleiro, vez);

                    /**
                     * Jogada era realmente válida?
                     */
                    if (motivo != JOGADA_INVALIDA_MOTIVO_VALIDA) {

                        /**
                         * Não. Convertemos o motivo de uma constante numérica para uma
                         * representação textual para que a mesma possa ser impressa ao
                         * usuário.
                         */
                        jogadaInvalidaMotivoParaString(motivo, motivoString);
                        if (conf.interfaceColorida == VERDADEIRO) {

                            interfaceColoridaMudaCorFonte(INTERFACE_COLORIDA_COR_VERMELHO);
                            printf("Jogada invalida!\nRazao: %s\n", motivoString);
                            interfaceColoridaReseta();
                        }
                        else {

                            printf("Jogada invalida!\nRazao: %s\n", motivoString);
                        }
                    }
                    else {

                        /**
                         * Jogada é válida e foi executada. Vamos armazená-la no log.
                         */
                        logDeJogadasAdiciona(& logDeJogadas, jogadaString);

                        printf("\n\n");

                        /**
                         * Nesse caso, alternamos a vez.
                         */
                        if (vez == VEZ_BRANCAS) vez = VEZ_PRETAS;
                        else vez = VEZ_BRANCAS;
                    }

                    /** 
                     * Válida ou não, liberamos a memória alocada para a representação
                     * da jogada.
                     */
                    jogadaListaLiberaMemoria(& jogada);
                }

                break ;
            case 2:

                /**
                 * Opção de armazenamento do log de jogadas em um arquivo.
                 * Começamos solicitando o nome do arquivo ao usuário.
                 */
                printf("Especifique o nome do arquivo onde deseja salvar o log -> ");
                scanf("%s", nomeDoArquivo);

                /**
                 * Solicitamos agora ao módulo de log de jogadas que salve o log
                 * no arquivo.
                 */
                if (logDeJogadasSalvaEmArquivo(& logDeJogadas, nomeDoArquivo) == FALSO) {

                    /** 
                     * Módulo retornou algum erro na manipulação do arquivo. Reportar 
                     * ao usuário.
                     */
                    if (conf.interfaceColorida == VERDADEIRO) {

                        interfaceColoridaLimpaTela();
                        interfaceColoridaMudaCorFonte(INTERFACE_COLORIDA_COR_VERMELHO);
                        printf("Erro ao salvar o arquivo de log. Verifique o caminho especificado.\n\n");
                        interfaceColoridaReseta();
                    }
                    else {

                        printf("Erro ao salvar o arquivo de log. Verifique o caminho especificado.\n\n");
                    }
                }
                else {

                    /**
                     * Criação do arquivo de log de jogadas foi bem sucedido. Avisar
                     * ao usuário.
                     */
                    if (conf.interfaceColorida == VERDADEIRO) {

                        interfaceColoridaLimpaTela();
                        interfaceColoridaMudaCorFonte(INTERFACE_COLORIDA_COR_VERDE);
                        printf("Arquivo salvo com sucesso!\n\n");
                        interfaceColoridaReseta();
                    }
                    else {

                        printf("Arquivo salvo com sucesso!\n\n");
                    }
                }
                break ;
            case 3:

                /**
                 * Opção de salvamento do estado da partida em um arquivo.
                 * Começamos lendo o nome do arquivo especificado pelo usuário.
                 */
                printf("Especifique o nome do arquivo onde deseja salvar o estado -> ");
                scanf("%s", nomeDoArquivo);

                /**
                 * Solicitamos ao módulo estado que salve o estado no arquivo.
                 */
                if (estadoSalvaEmArquivo(& tabuleiro, & logDeJogadas, nomeDoArquivo) == FALSO) {

                    /** 
                     * Módulo reportou algum erro na manipulação do arquivo.
                     */
                    if (conf.interfaceColorida == VERDADEIRO) {

                        interfaceColoridaLimpaTela();
                        interfaceColoridaMudaCorFonte(INTERFACE_COLORIDA_COR_VERMELHO);
                        printf("Erro ao salvar o arquivo de estado. Verifique o caminho especificado.\n\n");
                        interfaceColoridaReseta();
                    }
                    else {

                        printf("Erro ao salvar o arquivo de estado. Verifique o caminho especificado.\n\n");
                    }
                }
                else {

                    /**
                     * Geração do arquivo foi bem sucedida. Avisar ao usuário.
                     */
                    if (conf.interfaceColorida == VERDADEIRO) {

                        interfaceColoridaLimpaTela();
                        interfaceColoridaMudaCorFonte(INTERFACE_COLORIDA_COR_VERDE);
                        printf("Arquivo salvo com sucesso!\n\n");
                        interfaceColoridaReseta();
                    }
                    else {

                        printf("Arquivo salvo com sucesso!\n\n");
                    }
                }
                break ;
        }
    }

    /**
     * Se chegamos até aqui, jogo acabou. Vamos imprimir o estado final do 
     * tabuleiro e o vencedor.
     */
    if (conf.interfaceColorida == VERDADEIRO)
        interfaceColoridaImprimeTabuleiro(tabuleiro);
    else 
        interfaceMonocromaticaImprimeTabuleiro(tabuleiro);

    /**
     * Vencedor é o jogador que fez última jogada válida. Como a jogada foi
     * executada na repetição anterior, a variável vez foi modificada passando
     * a vez ao outro jogador. Assim, se vez aponta para as peças brancas, isso
     * significa que as peças pretas ganharam (e vice-versa).
     */    
    if (vez == VEZ_BRANCAS) printf("Fim de jogo. Pretas ganharam!\n");
    else printf("Fim de jogo. Brancas ganharam!\n");

    /**
     * Execução bem-sucedida.
     */
    return(0);    
}