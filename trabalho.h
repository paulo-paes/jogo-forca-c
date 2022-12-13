typedef struct no
{
    char letra;
    int status;
    struct no *prox;
} LETRA;

typedef struct node
{
    char jogada;
    int player;
    struct node *ant;
    struct node *prox;
} REPLAY;

void setupGame(char pal[], int tamanho);
void startGame();
void showLastReplay();
void displayPalavra();
void displayCharactersAndStatus();
void displayWord();
void displayVidaJogador();
void askForChar();
void computarChar(char ch);
void computarCharReplay(char ch);
void salvarJogada(char ch);
int lifeAvailable();
int letraDisponivel();
void calcularVencedor();
void waitForUserInput(char msg[]);
void desenhaForca();
void desenharTrofeu();
void desenharCaveira();
void escolherDificuldade();
void showReplayStatus();
void escolherModoDeJogo();
void chooseRandomChar();
char generateChar();
int isCharInPalavra(char ch);