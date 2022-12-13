#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "trabalho.h"

int VIDA_INICIAL = 6;
int vidaJogador;
char palavraHist[9];
int replaying = 0;
int dificuldade;
int tamanhoReplay;
// 0 - JOGADOR VS JOGADOR
// 1 - JOGADOR VS COMPUTADOR (JOGADOR ESCOLHE PALAVRA)
// 2 - JOGADOR VS COMPUTADOR (COMPUTADOR ESCOLHER PALAVRA)
int gameMode;


REPLAY *historico;
LETRA *palavra;
LETRA *ultimo;


int main()
{

    int op;
    // displayPalavra();
    while (1)
    {
        // system("clear");
        system("cls");
        printf("--------------------------------------------------------------");
        printf("\nEscolha sua opcao: ");
        printf("\n1 - Comecar novo jogo");
        printf("\n2 - Exibir replay");
        printf("\n");
        printf("--------------------------------------------------------------\n");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            replaying = 0;
            startGame();
            break;
        case 2:
            showLastReplay();
            break;
        default:
            printf("Opcao invalida");
            break;
        }
    }
}

void startGame()
{
    escolherModoDeJogo();
    escolherDificuldade();
    //char palavras[2][5] = {"TESTE", "PORTA"};
    //setupGame(palavras[0], 5);
    while (letraDisponivel() == 1 && lifeAvailable() == 1)
    {
        desenhaForca();
        if (gameMode == 1) {
            chooseRandomChar();
            system("PAUSE");

        }
        else
        {
            askForChar();
        }
        // displayCharactersAndStatus();
        // displayWord();
        displayVidaJogador();
    }

    calcularVencedor();
}

void chooseRandomChar() {
    char ch;
    int i, isIn;

    for (i = 1; i <= dificuldade; i++) {
        ch = generateChar();
        isIn = isCharInPalavra(ch);

        if (isIn == 1) {
            break;
        }
    }
    computarChar(ch);
}

char generateChar() {
    return 'A' + (rand() % 26);
}

int isCharInPalavra(char ch) {
    int isIn = 0;
    LETRA *aux = palavra;

    while (aux != NULL) {
        if (ch == aux->letra) {
            isIn = 1;
            break;
        }

        aux = aux->prox;
    }
    return isIn;
}

void escolherModoDeJogo() {
    int valid = 0, op;
    char escolherPalavra = 'K';

    while (valid == 0) {
        printf("Escolha o modo de jogo: \n");
        printf("1 - JOGADOR VS JOGADOR\n");
        printf("2 - JOGADOR VS COMPUTADOR\n");
        scanf("%d", &op);

        switch(op) {
            case 1:
                gameMode = 0;
                valid = 1;
                break;
            case 2:
                
                while(escolherPalavra != 'S' && escolherPalavra != 'N') {
                    printf("Voce deseja escolher a palavra? [S/N]\n");
                    scanf(" %c", &escolherPalavra);
                }

                if (escolherPalavra == 'S') {
                    gameMode = 1;
                } else {
                    gameMode = 2;
                }
                valid = 1;
                break;
            default:
                printf("Opcao invalida\n");
                break;
        }
    }
}

void escolherDificuldade2() {
    int dif, pos, i;

    printf("\nEscolha a dificuldade: 1 - Facil, 2 - Medio, 3 - Dificil\n");
    scanf("%d", &dif);
    srand(time(NULL));

    printf("\nrandom number %d\n", pos);
    char palavrasM[4][6] = {"HABITO", "ROTINA", "PENSAR", "VIAGEM"};
    char palavrasD[4][8] = {"PARALELO", "TELEFONE", "CARAMELO", "PATINETE"};
    char palavrasF[4][4] = {"FATO", "VIDA", "BOLO", "MEIA"};
    dificuldade = dif;

    if (gameMode == 2) {
        pos = rand() % 4;
    } else {
        printf("Escolha a palavra dentre as seguintes: \n");
        for (i = 0; i < 4; i++){
            if (dif == 1) {
                printf("%d - %s\n", i + 1, palavrasF[i]);
            } else if (dif == 2) {
                printf("%d - %s\n", i + 1, palavrasM[i]);
            } else {
                printf("%d - %s\n", i + 1, palavrasD[i]);
            }
        }
        scanf("%d", &pos); 
        pos -= 1;
    }

    switch (dif) {
        case 2:
            setupGame(palavrasM[pos], 6);
            break;
        case 3:
            setupGame(palavrasD[pos], 8);
            break;
        case 1:
            setupGame(palavrasF[pos], 4);
            break;
        default:
            printf("\nDificuldade automaticamente definida como Facil\n");
            dificuldade = 1;
            setupGame(palavrasF[pos], 4);
            break;
    }
}

void escolherDificuldade() {
    int dif = 0, pos, i, palavraEscolhida = -1;

    while (dif != 1 && dif != 2 && dif != 3) {
        printf("\nEscolha a dificuldade: 1 - Facil, 2 - Medio, 3 - Dificil\n");
        scanf("%d", &dif);
        switch (dif) {
            case 1:
            case 2:
            case 3:
                break;
            default:
                printf("\nOpcao Invalida\n");
                break;
        }
    }

    char palavrasM[4][7] = {"HABITO\0", "ROTINA\0", "PENSAR\0", "VIAGEM\0"};
    char palavrasD[4][9] = {"PARALELO\0", "TELEFONE\0", "CARAMELO\0", "PATINETE\0"};
    char palavrasF[4][5] = {"FATO\0", "VIDA\0", "BOLO\0", "MEIA\0"};
    dificuldade = dif;
    printf("\ndif = %d\n", dif);
    if (gameMode == 2) {
        srand(time(NULL));
        pos = rand() % 4;
        printf("\nrandom number %d\n", pos);
    } else {
        while (palavraEscolhida <= 0 || palavraEscolhida > 4) {
            printf("Escolha a palavra dentre as seguintes: \n");
            for (i = 0; i < 4; i++){
                if (dif == 1) {
                    printf("%d - %s\n", i + 1, palavrasF[i]);
                } else if (dif == 2) {
                    printf("%d - %s\n", i + 1, palavrasM[i]);
                } else {
                    printf("%d - %s\n", i + 1, palavrasD[i]);
                }
            }
            scanf("%d", &palavraEscolhida);
            pos = palavraEscolhida - 1;
            system("cls");
        }
    }

    switch (dif) {
        case 2:
            setupGame(palavrasM[pos], 6);
            break;
        case 3:
            setupGame(palavrasD[pos], 8);
            break;
        case 1:
            setupGame(palavrasF[pos], 4);
            break;
    }
}

void desenhaForca()
{

    int erros = VIDA_INICIAL - vidaJogador;

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros >= 1 ? '(' : ' '), (erros >= 1 ? '_' : ' '), (erros >= 1 ? ')' : ' '));
    printf(" |      %c%c%c  \n", (erros >= 3 ? '\\' : ' '), (erros >= 2 ? '|' : ' '), (erros >= 3 ? '/' : ' '));
    printf(" |       %c     \n", (erros >= 2 ? '|' : ' '));
    printf(" |      %c %c   \n", (erros >= 4 ? '/' : ' '), (erros >= 4 ? '\\' : ' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    LETRA *aux = palavra;
    while (aux != NULL)
    {

        if (aux->status == 1)
        {
            printf("%c ", aux->letra);
        }
        else
        {
            printf("_ ");
        }

        aux = aux->prox;
    }
    printf("\n");
}

void setupGame(char pal[], int tamanho)
{
    int i = 0;

    for (i = 0; i < tamanho; i++)
    {
        LETRA *temp = malloc(sizeof(LETRA));
        temp->letra = pal[i];
        palavraHist[i] = pal[i];
        temp->status = 0;
        temp->prox = NULL;
        if (i == 0)
        {
            palavra = temp;
        }
        else
        {
            ultimo->prox = temp;
        }
        ultimo = temp;
    }
    if (replaying == 0)
    {
        historico = NULL;
        tamanhoReplay = dificuldade == 1 ? 4 : (dificuldade == 2 ? 6 : 8);
    }

    palavraHist[tamanho] = '\0';

    vidaJogador = VIDA_INICIAL;
    displayVidaJogador();
}

void showLastReplay()
{
    if (historico == NULL)
    {
        printf("Nenhum replay disponivel");
        waitForUserInput("Digite uma letra para voltar ao menu anterior");
        return;
    }

    replaying = 1;
    setupGame(palavraHist, tamanhoReplay);
    REPLAY *aux = historico;
    while (aux != NULL)
    {
        computarChar(aux->jogada);
        desenhaForca();
        aux = aux->prox;
        //waitForUserInput("Digite uma letra para continuar o replay");
        system("PAUSE");
    }
    calcularVencedor();
}

void showReplayStatus() {
    REPLAY *aux = historico;
    LETRA *pal = palavra;
    while (pal != NULL)
    {
        printf("letra: %c\n", pal->letra);
        pal = pal->prox;
    }
    
    while (aux != NULL)
    {
        //computarChar(aux->jogada);
        //desenhaForca();
        printf("jogada %c\n", aux->jogada);
        printf("palavraHist %s\n", palavraHist);
        printf("tamanhoReplay %d\n", tamanhoReplay);
        printf("replaying %d\n", replaying);
        printf("vidaJogador %d\n", vidaJogador);
        if(aux->prox != NULL) {
            printf("tem prox\n");
        }
        aux = aux->prox;
        //waitForUserInput("Digite uma letra para continuar o replay");
        system("PAUSE");
    }
}

// void jogadaReplay(char ch) {
//     computarChar(ch);
// }

void displayPalavra()
{
    LETRA *aux = palavra;
    printf("\n");
    while (aux != NULL)
    {
        printf("%c", aux->letra);
        aux = aux->prox;
    }
    printf("\n");
}

void displayCharactersAndStatus()
{
    LETRA *aux = palavra;
    while (aux != NULL)
    {
        printf("\n");
        printf("letra: %c status: %d", aux->letra, aux->status);
        aux = aux->prox;
    }
    printf("\n");
}

void displayVidaJogador()
{
    printf("\n");
    printf("Vida(s) restante: %d", vidaJogador);
    printf("\n");
}

void askForChar()
{
    char ch;
    printf("\n");
    fflush(stdin);
    scanf(" %c", &ch);
    fflush(stdin);
    computarChar(ch);
    printf("\n");
}

void computarChar(char ch)
{
    LETRA *aux = palavra;
    int hit = 0;
    printf("\n");
    while (aux != NULL)
    {
        if (aux->letra == ch)
        {
            aux->status = 1;
            hit = 1;
        }
        aux = aux->prox;
    }

    if (hit == 1)
    {
        printf("Voce Acertou!\n");
    }
    else
    {
        vidaJogador--;
        printf("Voce Errou :(\n");
    }
    if (replaying == 0)
    {
        salvarJogada(ch);
    }
    
    if (replaying == 1 || gameMode == 1) {
        printf("O chute foi: %c\n", ch);
    }
}

void computarCharReplay(char ch)
{
    LETRA *aux = palavra;
    int hit = 0;
    printf("\n");
    while (aux != NULL)
    {
        if (aux->letra == ch)
        {
            aux->status = 1;
            hit = 1;
        }
        aux = aux->prox;
    }

    if (hit == 1)
    {
        printf("Voce Acertou!");
    }
    else
    {
        vidaJogador--;
        printf("Voce Errou :(");
    }
    if (replaying == 0)
    {
        salvarJogada(ch);
    }
}

void salvarJogada(char ch)
{
    REPLAY *temp = malloc(sizeof(REPLAY));
    temp->jogada = ch;
    temp->player = 0;
    temp->ant = NULL;
    temp->prox = NULL;
    if (historico == NULL)
    {
        historico = temp;
    }
    else
    {
        REPLAY *ultimo = historico;
        while (ultimo->prox != NULL)
        {
            ultimo = ultimo->prox;
        }
        temp->ant = ultimo;
        ultimo->prox = temp;
    }
}

// Retorna 1 caso ainda existem letras disponivel no jogo e 0 caso não tenha
int letraDisponivel()
{
    LETRA *aux = palavra;
    while (aux != NULL)
    {
        if (aux->status == 0)
        {
            return 1;
        }
        aux = aux->prox;
    }

    return 0;
}

void displayWord()
{
    LETRA *aux = palavra;
    while (aux != NULL)
    {

        if (aux->status == 1)
        {
            printf(" %c", aux->letra);
        }
        else
        {
            printf(" _");
        }
        aux = aux->prox;
    }
}

int lifeAvailable()
{
    if (vidaJogador < 1)
    {
        return 0;
    }

    return 1;
}

void calcularVencedor()
{
    printf("\n");
    if (vidaJogador > 0)
    {
        desenharTrofeu();
    }
    else
    {
        desenharCaveira();
    }
    displayVidaJogador();
    waitForUserInput("Digite uma letra para voltar ao menu");
}

void waitForUserInput(char msg[])
{
    char input;
    printf("\n%s\n", msg);
    scanf(" %c", &input);
}

void desenharCaveira()
{
    printf("\n voce foi enforcado!\n");
    // printf("A palavra era **%s**\n\n", palavrasecreta);

    printf("    _______________         \n");
    printf("   /               \\       \n");
    printf("  /                 \\      \n");
    printf("//                   \\/\\  \n");
    printf("\\|   XXXX     XXXX   | /   \n");
    printf(" |   XXXX     XXXX   |/     \n");
    printf(" |   XXX       XXX   |      \n");
    printf(" |                   |      \n");
    printf(" \\__      XXX      __/     \n");
    printf("   |\\     XXX     /|       \n");
    printf("   | |           | |        \n");
    printf("   | I I I I I I I |        \n");
    printf("   |  I I I I I I  |        \n");
    printf("   \\_             _/       \n");
    printf("     \\_         _/         \n");
    printf("       \\_______/           \n");
}

void desenharTrofeu()
{
    printf("\nParabens, voce ganhou!\n\n");

    printf("       ___________      \n");
    printf("      '._==_==_=_.'     \n");
    printf("      .-\\:      /-.    \n");
    printf("     | (|:.     |) |    \n");
    printf("      '-|:.     |-'     \n");
    printf("        \\::.    /      \n");
    printf("         '::. .'        \n");
    printf("           ) (          \n");
    printf("         _.' '._        \n");
    printf("        '-------'       \n\n");
}
