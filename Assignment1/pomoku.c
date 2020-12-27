#include "pomoku.h"

size_t g_board[20][20] = { 0, };
size_t g_player1_point = 0;
size_t g_player2_point = 0;
size_t g_board_row = 15;
size_t g_board_col = 15;

void init_game(void)/*오목 판 초기화*/
{
	size_t i = 0;
	size_t j = 0;
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 20; j++) {
			g_board[i][j] = 13; /* 13값으로 보드판 초기화 */
		}
	}
	{
		g_board_col = 15; /* 변수들 초깃값으로 초기화 */
		g_board_row = 15;
        g_player1_point = 0;
	    g_player2_point = 0;
	}
}

size_t get_row_count(void) 
{
	return g_board_row;
}

size_t get_column_count(void)
{
	return g_board_col;
}

int get_score(const color_t color) 
{
    if (color == COLOR_BLACK) {
        return g_score_player1;
    } else if (color == COLOR_WHITE) {
        return g_score_player2;
    } else {
        return -1;
    }

    return 0;
}

int get_color(const size_t row, const size_t col) 
{ 
    if (g_board[row][col] == COLOR_BLACK) {
        return 0;
    } else if (g_board[row][col] == COLOR_WHITE) {
        return 1;
    } else {
        return -1;
    }
    
    return 0;
}

int is_placeable(const size_t row, const size_t col) 
{
    if (g_board[row][col] == 13) {
        return TRUE;
    } else {
        return FALSE;
    }

    return 0;
}

int place_stone(const color_t color, const size_t row, const size_t col) 
{
    if (g_board[row][col] == COLOR_BLACK) {
        return FALSE;
    } else if (g_board[row][col] == COLOR_WHITE) {
        return FALSE;
    } else {
        g_board[row][col] = color;
        return TRUE;
    }

    return 0;
}

/* special moves */
int insert_column(const color_t color, const size_t col)
{
	size_t i;
	size_t j;
	if (g_board_col == 20) { /* col이 20이 되면 불가 */
		return FALSE;
	}
	else if (col < 0 || col >= g_board_col) { /*col이 범위를 벗어나면 불가 */
		return FALSE;
	}
	else { /* 범위 내 col */
		if (color == COLOR_BLACK) {
			for (i = 0; i < g_board_row; i++) {
				for (j = g_board_col; j >= col + 1; j--) {
					g_board[i][j] = g_board[i][j - 1];
				}
			}
			g_board_col += 1;
			g_player1_point -= 3;
			for (i = 0; i < g_board_row; i++) {
				g_board[i][col] = 13;
			}
			return TRUE;
		}
		else if (color == COLOR_WHITE) {
			for (i = 0; i < g_board_row; i++) {
				for (j = g_board_col; j >= col + 1; j--) {
					g_board[i][j] = g_board[i][j - 1];
				}
			}
			g_board_col += 1;
			g_player2_point -= 3;
			for (i = 0; i < g_board_row; i++) {
				g_board[i][col] = 13;
			}
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
}

int insert_row(const color_t color, const size_t row)
{
	size_t i;
	size_t j;
	if (g_board_row == 20) { /*보드 크기 20이면 불가*/
		return FALSE;
	}
	else if (row < 0 || row >= g_board_row) { /*row의 범위가 벗어남*/
		return FALSE;
	} else {
		if (color == COLOR_BLACK) {
			for (i = g_board_row; i >= row + 1; i--) { /* 3 <- 2 대입 2 <- 1 대입 ...*/
				for (j = 0; j < g_board_col; j++) {
					g_board[i][j] = g_board[i - 1][j];
				}
			}
			g_board_row += 1;
			g_player1_point -= 3;
			for (i = 0; i < g_board_col; i++) {
				g_board[row][i] = 13; /*삽입 시 어떤 돌도 x*/
			}
			return TRUE;
		} else if (COLOR_WHITE) {
			for (i = g_board_row; i >= row + 1; i--) { /* 3 <- 2 대입 2 <- 1 대입 ...*/
				for (j = 0; j < g_board_col; j++) {
					g_board[i][j] = g_board[i - 1][j];
				}
			}
			g_board_row += 1;
			g_player2_point -= 3;
			for (i = 0; i < g_board_col; i++) {
				g_board[row][i] = 13; /*삽입 시 어떤 돌도 x*/
			}
			return TRUE;
		} else {
			return FALSE;
		}
	}
}

int remove_row(const color_t color, const size_t row)
{
	if (g_board_row == 10) { /* 최소 크기 */
		return FALSE;
	} else if (row < 0 || row >= g_board_row) {
		return FALSE;
	} else {
		if (color == COLOR_BLACK) {
			size_t i;
			size_t j;
			
			for (i = row + 1; i < g_board_row; i++) {
				for (j = 0; j < g_board_col; j++) { /*0 <- 1, 1 <- 2, 2 <- 3 */
					g_board[i - 1][j] = g_board[i][j];
				}
			}
			g_board_row -= 1;
			g_player1_point -= 3;
			return TRUE;
		} else if (color == COLOR_WHITE){
			size_t i;
			size_t j;

			for (i = row + 1; i < g_board_row; i++) {
				for (j = 0; j < g_board_col; j++) { /*0 <- 1, 1 <- 2, 2 <- 3 */
					g_board[i - 1][j] = g_board[i][j];
				}
			}
			g_board_row -= 1;
			g_player2_point -= 3;
			return TRUE;
		} else {
			return FALSE;
		}
	}
}

int remove_column(const color_t color, const size_t col)
{
	if (g_board_col == 10) {
		return FALSE;
	} else if (col < 0 || col >= g_board_col) { /* 범위를 벗어남 */
		return FALSE;
	} else {
		if (color == COLOR_BLACK) {
			size_t i;
			size_t j;
			for (i = 0; i < g_board_row; i++) {
				for (j = col + 1; j < g_board_col; j++) {
					g_board[i][j - 1] = g_board[i][j];
				}
			}
			g_board_col -= 1;
			g_player1_point -= 3;
			return TRUE;
		} else if (color == COLOR_WHITE) {
			size_t i;
			size_t j;
			for (i = 0; i < g_board_row; i++) {
				for (j = col + 1; j < g_board_col; j++) {
					g_board[i][j - 1] = g_board[i][j];
				}
			}
			g_player2_point -= 3;
			g_board_col -= 1;
			return TRUE;
		} else {
			return FALSE;
		}
	}
}

int swap_rows(const color_t color, const size_t row0, const size_t row1)
{
	size_t i;

	if ((row0 < 0 || row0 >= g_board_row) || (row1 < 0 || row1 >= g_board_row)) {
		return FALSE;
	} else {
		if (color == COLOR_BLACK) {
			size_t temp[20] = { 0, };
			for (i = 0; i < g_board_row; i++) {
				temp[i] = g_board[row0][i]; /* 임시 배열에 row0의 값들을 저장 */
				g_board[row0][i] = g_board[row1][i]; /* row0에 row1의 값들을 저장*/
			}
			for (i = 0; i < g_board_row; i++) {
				g_board[row1][i] = temp[i]; /* 임시 배열 값들을 row1에 저장 */
			}
			g_player1_point -= 2;
			return TRUE;
		} else if (color == COLOR_WHITE) {
			size_t temp[20] = { 0, };
			for (i = 0; i < g_board_row; i++) {
				temp[i] = g_board[row0][i]; /* 임시 배열에 row0의 값들을 저장 */
				g_board[row0][i] = g_board[row1][i]; /* row0에 row1의 값들을 저장*/
			}
			for (i = 0; i < g_board_row; i++) {
				g_board[row1][i] = temp[i]; /* 임시 배열 값들을 row1에 저장 */
			}
			g_player2_point -= 2;
			return TRUE;
		} else {
			return FALSE;
		}
	}
}

int swap_columns(const color_t color, const size_t col0, const size_t col1)
{
	size_t i;
	if ((col0 < 0 || col0 >= g_board_col) || (col1 < 0 || col1 >= g_board_col)) {
		return FALSE;
	} else {
		if (color == COLOR_BLACK) {
			size_t temp[20] = { 0, };
			for (i = 0; i < g_board_col; i++) {
				temp[i] = g_board[i][col0]; /* 임시 배열에 col0의 값들을 저장 */
				g_board[i][col0] = g_board[i][col1]; /* col0에 col1의 값들을 저장*/
			}
			for (i = 0; i < g_board_col; i++) {
				g_board[i][col1] = temp[i]; /* 임시 배열 값들을 col1에 저장 */
			}
			g_player1_point -= 2;
			return TRUE;
		} else if (color == COLOR_WHITE){
			size_t temp[20] = { 0, };
			for (i = 0; i < g_board_col; i++) {
				temp[i] = g_board[i][col0]; /* 임시 배열에 col0의 값들을 저장 */
				g_board[i][col0] = g_board[i][col1]; /* col0에 col1의 값들을 저장*/
			}
			for (i = 0; i < g_board_col; i++) {
				g_board[i][col1] = temp[i]; /* 임시 배열 값들을 col1에 저장 */
			}
			g_player2_point -= 2;
			return TRUE;
		} else {
			return FALSE;
		}
	}
}

int copy_row(const color_t color, const size_t src, const size_t dst) /* 원본 src 타겟 dst */
{
	size_t i;
	if ((src < 0 || src >= g_board_row) || (dst < 0 || dst >= g_board_row)) {
		return FALSE;
	} else {
		if (color == COLOR_BLACK) {
			for (i = 0; i < g_board_row; i++) {
				g_board[dst][i] = g_board[src][i];
			}
			g_player1_point -= 4;
			return TRUE;
		} else if (color == COLOR_WHITE){
			for (i = 0; i < g_board_row; i++) {
				g_board[dst][i] = g_board[src][i];
			}
			g_player2_point -= 4;
			return TRUE;
		} else {
			return FALSE;
		}
	}
}

int copy_column(const color_t color, const size_t src, const size_t dst)
{
	size_t i;
	if ((src < 0 || src >= g_board_col) || (dst < 0 || dst >= g_board_col)) {
		return FALSE;
	} else {
		if (color == COLOR_BLACK) {
			for (i = 0; i < g_board_col; i++) {
				g_board[i][dst] = g_board[i][src];
			}
			g_player1_point -= 4;
			return TRUE;
		} else if (color == COLOR_WHITE){
			for (i = 0; i < g_board_col; i++) {
				g_board[i][dst] = g_board[i][src];
			}
			g_player2_point -= 4;
			return TRUE;
		} else {
			return FALSE;
		}
	}
}
