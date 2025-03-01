#include <stdio.h>

struct Move {
    int row;
    int col;
};

const char noone = '-';
const char player = 'x';
const char opponent = 'o';

char board[3][3] = {
    {noone, noone, noone}, 
    {noone, noone, noone}, 
    {noone, noone, noone}
};

void showBoard() {
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("-----------\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("-----------\n");
    printf(" %c | %c | %c \n\n", board[2][0], board[2][1], board[2][2]);
}

int isValidMove(struct Move move) {
    return board[move.row][move.col] == noone;
}

int checkWin(char player) {
    // Check for rows and columns
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return 1;
        }
    }

    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return 1;
    }

    return 0;
}

int main() {
    showBoard();

    char currentPlayer = player;
    struct Move move;
    int movesCount = 0;
    
    // Todo -> Game running
    while (1) {
        printf("Player %c, enter your move (row and column 0-2): ", currentPlayer);
        scanf("%d %d", &move.row, &move.col);

        if (!isValidMove(move)) {
            printf("Invalid move!");
            continue;
        }

        board[move.row][move.col] = currentPlayer;
        showBoard();
        movesCount++;

        if (checkWin(currentPlayer)) {
            printf("Player %c wins!", currentPlayer);
            break;
        }

        if (movesCount == 9) {
            printf("It's a draw!");
            break;
        }

        currentPlayer = (currentPlayer == player) ? opponent : player;
    }

    return 0;
}