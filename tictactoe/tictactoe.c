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
    WIN = 1,   // AI wins
    LOSE = -1, // Human wins
    TIE = 0
};

int countMoves() {
    int count = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != noone)
                count++;
        }
    }
    return count;
}

int checkWin(char p, int movesCount) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == p && board[i][1] == p && board[i][2] == p) ||
            (board[0][i] == p && board[1][i] == p && board[2][i] == p))
            return 1;
    }
    // Check diagonals
    if ((board[0][0] == p && board[1][1] == p && board[2][2] == p) ||
        (board[0][2] == p && board[1][1] == p && board[2][0] == p))
        return 1;

    if (movesCount == 9)
        return 2; // Tie

    return 0;
}

// Fire video 🔥
// https://www.youtube.com/watch?v=trKjYdBASyQ
int minimax(int depth, int isMaximizing) {
    int movesCount = countMoves();

    if (checkWin(opponent, movesCount) == 1)
        return WIN;
    if (checkWin(player, movesCount) == 1)
        return LOSE;
    if (movesCount == 9)
        return TIE;

    if (isMaximizing) {
        // AI's turn
        int bestScore = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == noone) {
                    board[i][j] = opponent;
                    int score = minimax(depth + 1, 0);
                    board[i][j] = noone;
                    if (score > bestScore)
                        bestScore = score;
                }
            }
        }
        return bestScore;
    }

    // Human's turn
    int bestScore = 1000;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == noone) {
                board[i][j] = player;
                int score = minimax(depth + 1, 1);
                board[i][j] = noone;
                if (score < bestScore)
                    bestScore = score;
            }
        }
    }

    return bestScore;
}

struct Move bestMove() {
    int bestScore = -1000;
    struct Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == noone) {
                board[i][j] = opponent;
                int score = minimax(0, 0);
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

int main() {
    showBoard();

    char currentPlayer = player;
    struct Move move;
    int movesCount = 0;
    
    while (1) {
        if (currentPlayer == opponent) {
            // AI's turn.
            move = bestMove();
            board[move.row][move.col] = opponent;
            movesCount++;
            showBoard();
            int win = checkWin(opponent, movesCount);
            
            if (win == 1) {
                printf("Player %c wins!\n", opponent);
                break;
            }
            
            if (win == 2) {
                printf("It's a draw!\n");
                break;
            }

            currentPlayer = player;
            continue;
        }

        printf("Player, enter your move (row and column 0-2): ");
        scanf("%d %d", &move.row, &move.col);

        if (!isValidMove(move)) {
            printf("Invalid move!\n");
            continue;
        }

        board[move.row][move.col] = player;
        movesCount++;
        showBoard();

        int win = checkWin(player, movesCount);
        if (win == 1) {
            printf("Player %c wins!\n", player);
            break;
        }

        if (win == 2) {
            printf("It's a draw!\n");
            break;
        }
        
        currentPlayer = opponent;
    }

    return 0;
}