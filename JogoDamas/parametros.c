#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parametros.h"

/*
 * Função que imprime uma ajuda dos parâmetros de linha de 
 * comando. Programa é encerrado ao final. Usada apenas
 * internamente pelo módulo.
 * Parâmetros: nenhum.
 * Retorno: nenhum.
 */
void parametrosAjuda() {

    printf("Damas: jogo de damas em linha de comando.\n");
    printf("Uso: damas [opcoes]\n\n");
    printf("Lista de opcoes suportadas:\n");
    printf("\t--restaura <arquivoEstado>\tRestaura estado de jogo anteriormente salvo\n");
    printf("\t--colorido\t\t\tHabilita interface texto colorida (por padrao, \n\t\t\t\t\tinterface monocromatica e usada)\n");
    printf("\t--ajuda\t\t\t\tImprime essa ajuda e sai.\n\n");
    printf("\nEste jogo implementa as regras de acordo com a Confederacao Brasileira de Jogo de Damas.\n");
    printf("Para mais informacoes, consulte: http://www.codexdamas.com.br/regras_oficiais.html\n");

    exit(1);
}

/*
 * Função que realiza a leitura e verificação de correção
 * dos parâmetros de linha de comando. Em caso de erro,
 * ajuda é mostrada e execução é encerrada.
 */
t_configuracao parametrosLeitura(int argc, char * argv[]) {

    int i;
    t_configuracao conf;

    /* 
     * Iniciar configuracao para valores padrão. Com
     * base na leitura dos parâmetros, esses valores 
     * poderão ser alterados.
     */
    conf.restauraEstado = NULL;
    conf.interfaceColorida = FALSO;

    /*
     * Leitura dos parâmetros de linha de comando.
     * Parâmetros possíveis:
     */
    for (i = 1; i < argc; i++) {

        if (strcmp(argv[i], "--restaura") == 0) {

            /* 
             * Opcao "--restaura" encontrada. Ela deve possuir um argumento
             * (string com o nome do arquivo a partir do qual estado deve
             * ser restaurado).
             */
            if (i == argc - 1) {

                /* 
                 * Deveria haver mais um argumento pelo menos. Avisar
                 * usuario sobre o erro.
                 */
                printf("Opcao \"--restaura\" requer um argumento.\n\n");
                parametrosAjuda();
            }

            conf.restauraEstado = argv[i+1];

            /*
             * Como a opcao "--restaura" recebe um argumento, então temos que 
             * pular próximo elemento no vetor argv. Fazemos isso adiantando
             * a variável i.
             */
            i = i + 1;
        }
        else if (strcmp(argv[i], "--colorido") == 0) {

            /*
             * Usuario quer habilitar interface colorida.
             */
            conf.interfaceColorida = VERDADEIRO;
        }
        else if (strcmp(argv[i], "--ajuda") == 0) {
        
            /*
             * Usuario requisitou impressao da ajuda.
             */
            parametrosAjuda();
        }
        else {

            /* 
             * Opcao nao reconhecida. Avisar sobre erro e 
             * imprimir ajuda.
             */
            printf("Opcao de linha de comando nao reconhecida: %s\n\n", argv[i]);
            parametrosAjuda();
        }
    }

    return(conf);
}

