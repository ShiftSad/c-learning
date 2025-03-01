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

enum Scores {
    WIN = 1,
    LOSE = -1,
    TIE = 0
};

int minimax(int depth, int isMaximizing) {
    return 1;
}

struct Move bestMove() {
    int bestScore = -1e9;
    struct Move bestMove;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == noone) {
                board[i][j] = opponent;
                int score = minimax(0, 1);
                board[i][j] = noone;
                if (score > bestScore) {
                    bestScore = score;
                    bestMove.row = i;
                    bestMove.col = j;
                }
            }
        }
    }

    return bestMove;
}

int checkWin(char player, int movesCount) {
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

    if (movesCount == 9) {
        return 2; // Tie
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
        if (currentPlayer == opponent) {
            // It's ai's turn.
            move = bestMove();
            board[move.row][move.col] = opponent;
            showBoard();
            currentPlayer = player;
        }

        printf("Player, enter your move (row and column 0-2): ");
        scanf("%d %d", &move.row, &move.col);

        if (!isValidMove(move)) {
            printf("Invalid move!");
            continue;
        }

        board[move.row][move.col] = currentPlayer;
        movesCount++;

        int win = checkWin(currentPlayer, movesCount);

        if (win == 1) {
            showBoard();
            printf("Player %c wins!", currentPlayer);
            break;
        }

        if (win == 2) {
            showBoard();
            printf("It's a draw!");
            break;
        }

        currentPlayer = opponent;
    }

    return 0;
}