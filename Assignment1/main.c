#include <stdio.h>

#include "pomoku.c"

extern size_t total_row;
extern size_t total_column;
extern size_t score_player1;
extern size_t score_player2;
extern size_t board[15][15];



int main(void)
{
	init_game();
	return 0;
}
