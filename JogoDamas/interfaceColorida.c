#include <stdio.h>

#ifdef _WIN32

#include <conio.h>
#include <windows.h>

#endif

#include "interfaceColorida.h"

#define INTERFACE_COLORIDA_CASA_ESCURA_COR_FONTE  INTERFACE_COLORIDA_COR_BRANCO
#define INTERFACE_COLORIDA_CASA_CLARA_COR_FONTE   INTERFACE_COLORIDA_COR_PRETO
#define INTERFACE_COLORIDA_PECA_PRETA_COR_FONTE   INTERFACE_COLORIDA_COR_BRANCO 
#define INTERFACE_COLORIDA_PECA_BRANCA_COR_FONTE  INTERFACE_COLORIDA_COR_PRETO
#define INTERFACE_COLORIDA_MOLDURA_COR_FONTE      INTERFACE_COLORIDA_COR_PRETO

#define INTERFACE_COLORIDA_CASA_ESCURA_COR_FUNDO  INTERFACE_COLORIDA_COR_CIANO
#define INTERFACE_COLORIDA_CASA_CLARA_COR_FUNDO   INTERFACE_COLORIDA_COR_BRANCO
#define INTERFACE_COLORIDA_PECA_PRETA_COR_FUNDO   INTERFACE_COLORIDA_COR_PRETO 
#define INTERFACE_COLORIDA_PECA_BRANCA_COR_FUNDO  INTERFACE_COLORIDA_COR_BRANCO
#define INTERFACE_COLORIDA_MOLDURA_COR_FUNDO      INTERFACE_COLORIDA_COR_AMARELO

#ifdef _WIN32

int interfaceColoridaWin32PrimeiraChamada = 1;
WORD wOldColorAttrs;

void textcolors(WORD colors) {
    
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

    GetConsoleScreenBufferInfo(h, &csbiInfo);

    if (interfaceColoridaWin32PrimeiraChamada) {

        wOldColorAttrs = csbiInfo.wAttributes;
        interfaceColoridaWin32PrimeiraChamada = 0;
    }

    SetConsoleTextAttribute(h, colors);
}

void textcolor(int color) {
    
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

    GetConsoleScreenBufferInfo(h, &csbiInfo);

    if (interfaceColoridaWin32PrimeiraChamada) {

        wOldColorAttrs = csbiInfo.wAttributes;
        interfaceColoridaWin32PrimeiraChamada = 0;
    }

    color = (color & 0x0F) | (csbiInfo.wAttributes & 0xF0);
    SetConsoleTextAttribute(h, color);
}

void textbackground(int color) {
    
    HANDLE h = GetStdHandle (STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

    GetConsoleScreenBufferInfo(h, &csbiInfo);

    if (interfaceColoridaWin32PrimeiraChamada) {

        wOldColorAttrs = csbiInfo.wAttributes;
        interfaceColoridaWin32PrimeiraChamada = 0;
    }

    color = (color << 4) | (csbiInfo.wAttributes & 0x0F);
    SetConsoleTextAttribute (h, color);
}

void clrscr() {

    HANDLE h = GetStdHandle (STD_OUTPUT_HANDLE);
    COORD coordScreen = {0, 0}; // home for the cursor
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    // Get the number of character cells in the current buffer.

    if (!GetConsoleScreenBufferInfo(h, &csbi)) {

        return;
    }

    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire screen with blanks.

    if (!FillConsoleOutputCharacter(h,        // Handle to console screen buffer
                                    (TCHAR)' ',      // Character to write to the buffer
                                    dwConSize,       // Number of cells to write
                                    coordScreen,     // Coordinates of first cell
                                    &cCharsWritten)) {// Receive number of characters written
    
        return;
    }

    // Get the current text attribute.

    if (!GetConsoleScreenBufferInfo(h, &csbi)) {

        return;
    }

    // Set the buffer's attributes accordingly.

    if (!FillConsoleOutputAttribute(h,         // Handle to console screen buffer
                                    csbi.wAttributes, // Character attributes to use
                                    dwConSize,        // Number of cells to set attribute
                                    coordScreen,      // Coordinates of first cell
                                    &cCharsWritten)) { // Receive number of characters written
    
        return;
    }

    // Put the cursor at its home coordinates.

    SetConsoleCursorPosition(h, coordScreen);
}

#endif

void interfaceColoridaMudaCorFonte(int cor) {

#ifdef _WIN32
    switch(cor) {

        case INTERFACE_COLORIDA_COR_PRETO:
            textcolor(0);
            break ;
        case INTERFACE_COLORIDA_COR_VERMELHO:
            textcolor(4);
            break ;
        case INTERFACE_COLORIDA_COR_VERDE:
            textcolor(2);
            break ;
        case INTERFACE_COLORIDA_COR_AMARELO:
            textcolor(14);
            break ;
        case INTERFACE_COLORIDA_COR_AZUL:
            textcolor(1);
            break ;
        case INTERFACE_COLORIDA_COR_MAGENTA:
            textcolor(5);
            break ;
        case INTERFACE_COLORIDA_COR_CIANO:
            textcolor(3);
            break ;
        case INTERFACE_COLORIDA_COR_BRANCO:
            textcolor(15);
            break ;
    }
#else
    printf("\033[%dm", cor + 30);
#endif

}

void interfaceColoridaMudaCorFundo(int cor) {

#ifdef _WIN32
    switch(cor) {

        case INTERFACE_COLORIDA_COR_PRETO:
            textbackground(0);
            break ;
        case INTERFACE_COLORIDA_COR_VERMELHO:
            textbackground(4);
            break ;
        case INTERFACE_COLORIDA_COR_VERDE:
            textbackground(2);
            break ;
        case INTERFACE_COLORIDA_COR_AMARELO:
            textbackground(14);
            break ;
        case INTERFACE_COLORIDA_COR_AZUL:
            textbackground(1);
            break ;
        case INTERFACE_COLORIDA_COR_MAGENTA:
            textbackground(5);
            break ;
        case INTERFACE_COLORIDA_COR_CIANO:
            textbackground(3);
            break ;
        case INTERFACE_COLORIDA_COR_BRANCO:
            textbackground(15);
            break ;
    }
#else
    printf("\033[%dm", cor + 100);
#endif

}

void interfaceColoridaNegrito() {

#ifndef _WIN32
    printf("\033[1m");
#endif

}

void interfaceColoridaReseta() {

#ifdef _WIN32
    textcolors(wOldColorAttrs);
#else
    printf("\033[0m");
#endif

}

void interfaceColoridaLimpaTela() {

#ifdef _WIN32
    clrscr();
#else
    printf("\033[2J");
    printf("\033[1;1H");
#endif

}

/*
 * Função que imprime um tabuleiro, usando uma saída monocromática.
 */
void interfaceColoridaImprimeTabuleiro(t_tabuleiro tabuleiro) {

    char * stringCentro;
    int i, j;

    /* 
     * Imprimir as coordenadas do eixo X do tabuleiro. Servem como guia
     * para o usuário. Colunas são identificadas por caracteres de 'a' a
     * 'h'.
     */
    printf("  ");
    for (i = 0; i < 8; i++){
        printf("   %c   ", 'a' + i);
    }
    printf("\n");

    /* 
     * Colocaremos uma espécie de moldura em volta do tabuleiro. Aqui,
     * colocamos a parte de cima. São 58 caracteres porque cada casa do
     * tabuleiro tem 7 caracteres de largura, enquanto a moldura tem 1
     * de cada lado.
     */
    interfaceColoridaMudaCorFundo(INTERFACE_COLORIDA_MOLDURA_COR_FUNDO);
    for (i = 0; i < 60; i++) {
        
        printf(" ");
    }
    interfaceColoridaReseta();
    printf("\n");

    /*
     * Iterar por todas as casas imprimindo o estado de cada uma.
     * Na tela, cada casa ocupa um bloco de 3x7 caracteres: casas
     * claras são representadas pelo caractere ' ' (espaço), enquanto
     * as escuras são representadas pelo caractere '#' (tralha). 
     * Se a casa ocupada, o caractere do meio é substituido por 'o' 
     * (peça preta normal), 'O' (dama preta), 'x' (peça branca normal)
     * ou 'X' (dama branca).
     */
    for (i = 0; i < 8; i++) {

        /*
         * Temos que trabalhar com a impressão das linhas na exata 
         * sequência em que elas apareceram na tela. Assim, temos
         * que começar imprimindo o topo de cada casa, seguido do 
         * centro e, finalmente, da base.
         */

        /*
         * Caractere de moldura.
         */
        interfaceColoridaMudaCorFundo(INTERFACE_COLORIDA_MOLDURA_COR_FUNDO);
        printf("  ");
        interfaceColoridaReseta();

        /*
         * Topo das casas.
         */
        for (j = 0; j < 8; j++) {

            if (tabuleiro.casas[i][j].cor == TABULEIRO_CASA_COR_CLARA) {

                interfaceColoridaMudaCorFundo(INTERFACE_COLORIDA_CASA_CLARA_COR_FUNDO);
            }
            else {

                interfaceColoridaMudaCorFundo(INTERFACE_COLORIDA_CASA_ESCURA_COR_FUNDO);
            }

            printf("       ");
            interfaceColoridaReseta();
        }

        /*
         * Caractere de moldura e final da linha.
         */
        interfaceColoridaMudaCorFundo(INTERFACE_COLORIDA_MOLDURA_COR_FUNDO);
        printf("  ");
        interfaceColoridaReseta();
        printf("\n");

        /*
         * Caractere de moldura da próxima linha.
         */
        interfaceColoridaMudaCorFundo(INTERFACE_COLORIDA_MOLDURA_COR_FUNDO);
        printf("  ");
        interfaceColoridaReseta();

        /*
         * Linha do centro.
         */
        for (j = 0; j < 8; j++) {

            if (tabuleiro.casas[i][j].cor == TABULEIRO_CASA_COR_CLARA) {

                interfaceColoridaMudaCorFundo(INTERFACE_COLORIDA_CASA_CLARA_COR_FUNDO);
                printf("       ");
            }
            else {

                interfaceColoridaMudaCorFundo(INTERFACE_COLORIDA_CASA_ESCURA_COR_FUNDO);
                printf("  ");

                /*
                 * Essa casa é escura e estamos imprimindo a linha do 
                 * meio. O caractere a ser impresso depende de se a casa
                 * está vazia e, se está cheia, de qual tipo de peça se
                 * encontra lá.
                 */
                if (tabuleiro.casas[i][j].ocupacao == NULL) {

                    stringCentro = "   ";
                }
                else {

                    if (tabuleiro.casas[i][j].ocupacao->tipo == PECA_NORMAL) {

                        stringCentro = "   ";
                    }
                    else {

                        stringCentro = " D ";
                    }

                    if (tabuleiro.casas[i][j].ocupacao->cor == PECA_BRANCA) {

                        interfaceColoridaMudaCorFundo(INTERFACE_COLORIDA_PECA_BRANCA_COR_FUNDO);
                        interfaceColoridaMudaCorFonte(INTERFACE_COLORIDA_PECA_BRANCA_COR_FONTE);
                    }
                    else {

                        interfaceColoridaMudaCorFundo(INTERFACE_COLORIDA_PECA_PRETA_COR_FUNDO);
                        interfaceColoridaMudaCorFonte(INTERFACE_COLORIDA_PECA_PRETA_COR_FONTE);
                    }
                }

                printf("%s", stringCentro);
                interfaceColoridaMudaCorFundo(INTERFACE_COLORIDA_CASA_ESCURA_COR_FUNDO);
                printf("  ");
            }

            interfaceColoridaReseta();
        }

        /*
         * Caractere de moldura, coordenada Y e final da linha.
         * A coordenada Y compreende números de 1 a 8.
         */
        interfaceColoridaMudaCorFundo(INTERFACE_COLORIDA_MOLDURA_COR_FUNDO);
        printf("  ");
        interfaceColoridaReseta();
        printf(" %d\n", i + 1);

        /*
         * Caractere de moldura da próxima linha.
         */
        interfaceColoridaMudaCorFundo(INTERFACE_COLORIDA_MOLDURA_COR_FUNDO);
        printf("  ");
        interfaceColoridaReseta();

        /* 
         * Linha da base.
         */
        for (j = 0; j < 8; j++) {

            if (tabuleiro.casas[i][j].cor == TABULEIRO_CASA_COR_CLARA) {

                interfaceColoridaMudaCorFundo(INTERFACE_COLORIDA_CASA_CLARA_COR_FUNDO);
            }
            else {

                interfaceColoridaMudaCorFundo(INTERFACE_COLORIDA_CASA_ESCURA_COR_FUNDO);
            }

            printf("       ");
            interfaceColoridaReseta();
        }

        /*
         * Caractere de moldura e final da linha.
         */
        interfaceColoridaMudaCorFundo(INTERFACE_COLORIDA_MOLDURA_COR_FUNDO);
        printf("  ");
        interfaceColoridaReseta();
        printf("\n");
    }

    /*
     * Base da moldura.
     */
    interfaceColoridaMudaCorFundo(INTERFACE_COLORIDA_MOLDURA_COR_FUNDO);
    for (i = 0; i < 60; i++) {
        
        printf(" ");
    }
    interfaceColoridaReseta();
    printf("\n");
}
