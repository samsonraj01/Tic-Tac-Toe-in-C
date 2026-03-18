

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define EMPTY ' '

// Function prototypes
void printBoard(char board[]);
int checkWin(char board[], char player);
int isBoardFull(char board[]);
int isEmpty(char board[], int pos);
void playerMove(char board[], char player);
void aiMove(char board[]);
void clearInput();

int main() {
    char board[9];
    int mode, gameOver, turn;
    char currentPlayer;
    int playAgain;

    srand(time(NULL));  

    do {
        
        for (int i = 0; i < 9; i++)
            board[i] = EMPTY;

        
        printf("\n=== TIC-TAC-TOE ===\n");
        printf("1. Player vs Player\n");
        printf("2. Player vs AI\n");
        printf("Select mode (1 or 2): ");
        scanf("%d", &mode);
        clearInput();

        gameOver = 0;
        turn = 0;   

        while (!gameOver) {
            printBoard(board);
            currentPlayer = (turn == 0) ? 'X' : 'O';

            if (mode == 1) {
                
                printf("Player %d's turn (%c)\n", turn + 1, currentPlayer);
                playerMove(board, currentPlayer);
            } else {
                
                if (turn == 0) {
                    printf("Your turn (X)\n");
                    playerMove(board, 'X');
                } else {
                    printf("AI's turn (O)...\n");
                    aiMove(board);
                }
            }

            
            if (checkWin(board, currentPlayer)) {
                printBoard(board);
                if (mode == 1)
                    printf("Player %d (%c) wins!\n", turn + 1, currentPlayer);
                else {
                    if (turn == 0)
                        printf("You win!\n");
                    else
                        printf("AI wins.\n");
                }
                gameOver = 1;
            }
            
            else if (isBoardFull(board)) {
                printBoard(board);
                printf("It's a draw!\n");
                gameOver = 1;
            }

            turn = !turn;  
        }

        printf("\nPlay again? (1 = Yes, 0 = No): ");
        scanf("%d", &playAgain);
        clearInput();
    } while (playAgain == 1);

    printf("Thanks for playing!\n");
    return 0;
}


void printBoard(char board[]) {
    printf("\n");
    for (int i = 0; i < 9; i++) {
        if (board[i] == EMPTY)
            printf(" %d ", i + 1);     
        else
            printf(" %c ", board[i]);   

        if (i % 3 == 2) {
            printf("\n");
            if (i < 8) printf("---+---+---\n");
        } else {
            printf("|");
        }
    }
    printf("\n");
}


int checkWin(char board[], char player) {
    
    int lines[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8},  // rows
        {0,3,6}, {1,4,7}, {2,5,8},  // columns
        {0,4,8}, {2,4,6}            // diagonals
    };

    for (int i = 0; i < 8; i++) {
        if (board[lines[i][0]] == player &&
            board[lines[i][1]] == player &&
            board[lines[i][2]] == player)
            return 1;
    }
    return 0;
}

int isBoardFull(char board[]) {
    for (int i = 0; i < 9; i++)
        if (board[i] == EMPTY)
            return 0;
    return 1;
}


int isEmpty(char board[], int pos) {
    return (pos >= 1 && pos <= 9 && board[pos-1] == EMPTY);
}


void playerMove(char board[], char player) {
    int pos;
    while (1) {
        printf("Enter position (1-9): ");
        if (scanf("%d", &pos) != 1) {
            clearInput();
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        clearInput();

        if (isEmpty(board, pos)) {
            board[pos-1] = player;
            break;
        } else {
            printf("That cell is not empty. Try again.\n");
        }
    }
}

void aiMove(char board[]) {
    int empty[9];   
    int count = 0;

    for (int i = 0; i < 9; i++)
        if (board[i] == EMPTY)
            empty[count++] = i;

    if (count > 0) {
        int r = rand() % count;
        board[empty[r]] = 'O';
    }
}


void clearInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
