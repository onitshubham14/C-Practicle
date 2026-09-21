#include <stdio.h>
#include <ctype.h>

char board[3][3];
int player1Score = 0;
int player2Score = 0;
int drawScore = 0;

void initializeBoard();
void displayBoard();
int isValidMove(int choice);
void makeMove(int choice, char mark);
int checkWin();
int checkDraw();
void playGame();

int main() {
    char playAgain;

    printf("===================================================\n");
    printf("         WELCOME TO TIC-TAC-TOE (C GAME)           \n");
    printf("===================================================\n");

    do {
        playGame();

        printf("\n--- SCOREBOARD ---\n");
        printf(" Player 1 (X) Wins : %d\n", player1Score);
        printf(" Player 2 (O) Wins : %d\n", player2Score);
        printf(" Draws             : %d\n", drawScore);
        printf("-------------------\n");

        printf("\nDo you want to play another round? (Y/N): ");
        if (scanf(" %c", &playAgain) != 1) {
            break;
        }

        playAgain = (char)toupper((unsigned char)playAgain);

    } while (playAgain == 'Y');

    printf("\nThanks for playing Tic-Tac-Toe! Final Scores:\n");
    printf("Player 1: %d | Player 2: %d | Draws: %d\n",
           player1Score, player2Score, drawScore);
    printf("Goodbye!\n");

    return 0;
}

void initializeBoard() {
    int count = 1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = '0' + count;
            count++;
        }
    }
}

void displayBoard() {
    printf("\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n", board[0][0], board[0][1], board[0][2]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n", board[1][0], board[1][1], board[1][2]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n", board[2][0], board[2][1], board[2][2]);
    printf("     |     |     \n");
    printf("\n");
}

int isValidMove(int choice) {
    if (choice < 1 || choice > 9) return 0;

    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;

    if (board[row][col] == 'X' || board[row][col] == 'O') {
        return 0;
    }

    return 1;
}

void makeMove(int choice, char mark) {
    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;
    board[row][col] = mark;
}

int checkWin() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return 1;
    }

    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return 1;
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return 1;

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return 1;

    return 0;
}

int checkDraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return 0;
            }
        }
    }

    return 1;
}

void playGame() {
    int currentPlayer = 1;
    int choice;
    int gameOver = 0;
    char mark;

    initializeBoard();

    while (!gameOver) {
        displayBoard();

        mark = (currentPlayer == 1) ? 'X' : 'O';
        printf("Player %d (%c), enter position (1-9): ",
               currentPlayer, mark);

        if (scanf("%d", &choice) != 1) {
            printf("  [Error] Invalid input! Please enter a number between 1 and 9.\n");
            while (getchar() != '\n' && !feof(stdin)) {
            }
            continue;
        }

        if (!isValidMove(choice)) {
            printf("  [Error] Invalid move! Cell is either occupied or out of bounds (1-9).\n");
            continue;
        }

        makeMove(choice, mark);

        if (checkWin()) {
            displayBoard();
            printf("🎉 CONGRATULATIONS! Player %d (%c) wins this round!\n",
                   currentPlayer, mark);

            if (currentPlayer == 1)
                player1Score++;
            else
                player2Score++;

            gameOver = 1;
        } else if (checkDraw()) {
            displayBoard();
            printf("🤝 IT'S A DRAW! Good game both players.\n");
            drawScore++;
            gameOver = 1;
        } else {
            currentPlayer = (currentPlayer == 1) ? 2 : 1;
        }
    }
}
