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

int main() {
    showBoard();
}