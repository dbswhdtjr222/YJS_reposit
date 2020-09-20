#include "pomoku.h"

size_t g_total_row = 15;
size_t g_total_col = 15;
size_t g_score_player1 = 0;
size_t g_score_player2 = 0;
size_t g_board[20][20] = { 0, };

void init_game(void) 
{
	size_t i;
    size_t j;
    g_total_row = 15;
    g_total_col = 15;
    g_score_player1 = 0;
    g_score_player2 = 0;

    for (i = 0; i < g_total_row; i++) {
        for (j = 0; j < g_total_col; j++) {
            g_board[i][j] = 13;
        }
    }

}


size_t get_row_count(void) 
{
    return g_total_row;
}

size_t get_column_count(void) 
{
    return g_total_col;
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
int insert_row(const color_t color, const size_t row) 
{
    int i;
    size_t j;
    if (color == COLOR_BLACK) { 
        if (row >= g_total_row || row < 0) {
            return FALSE;
        }
        if (g_total_row > 20) { 
            return FALSE;
        }

        for (i = (int)g_total_row - 1; i >= (int)row; i--) { 
            if (i < 0) {
                break;
            }
            for (j = 0; j < g_total_col; j++) { 
                g_board[i + 1][j] = g_board[i][j]; 
            }
        }
        for (j = 0; j < g_total_col; j++) { 
            g_board[row][j] = 13;
        }
        g_total_row += 1;
        g_score_player1 -= 3;
        return TRUE;
    } else if (color == COLOR_WHITE) { 
        if (g_total_row > 20) { 
            return FALSE;
        }

        for (i = (int)g_total_row - 1; i >= (int)row; i--) {
            if (i < 0) {
                break;
            } 
            for (j = 0; j < g_total_col; j++) {
                g_board[i + 1][j] = g_board[i][j]; 
            }
        }
        for (j = 0; j < g_total_col; j++) { 
            g_board[row][j] = 13;
        }
        g_total_row += 1;
        g_score_player2 -= 3;
        return TRUE;
    } else {
        return FALSE;
    }

    return 0;
}

int insert_column(const color_t color, const size_t col) 
{
    if (color == COLOR_BLACK) { 
        size_t i;
        int j;

        if (g_total_col > 20) { 
            return FALSE;
        }
        for (i = 0; i < g_total_row; i++) {
            for (j = (int)g_total_col - 1; j >= (int)col; j--) {
                if (j < 0) {
                    break;
                }
                g_board[i][j + 1] = g_board[i][j]; 
            }
        }
        for (i = 0; i < g_total_row; i++) { 
            g_board[i][col] = 13;
        }
        g_total_col += 1;
        g_score_player1 -= 3;

        return TRUE;
    } else if (color == COLOR_WHITE) {
        size_t i;
        int j;

        if (g_total_col > 20) { 
            return FALSE;
        }
        for (i = 0; i < g_total_row; i++) { 
            for (j = (int)g_total_col - 1; j >= (int)col; j--) { 
                if (j < 0) {
                    break;
                }
                g_board[i][j + 1] = g_board[i][j]; 
            }
        }
        for (i = 0; i < g_total_row; i++) { 
            g_board[i][col] = 13;
        }
        g_total_col += 1;
        g_score_player2 -= 3;
        return TRUE;
    } else {
        return FALSE;
    }

    return 0;
}

int remove_row(const color_t color, const size_t row)
{ 
    int i;
    size_t j;
    if(g_total_row <= 0) {
        return FALSE;
    }
    if (row >= g_total_row || row < 0) {
        return FALSE;
    }
    if (color == COLOR_BLACK) {
        for (i = (int)row + 1; i <= (int)g_total_row - 1; i++) {
            for (j = 0; j < g_total_col; j++) {
                g_board[i - 1][j] = g_board[i][j];
            }
        }
        g_total_row -= 1;
        g_score_player1 -= 3;
        return TRUE;
    } else if (color == COLOR_WHITE) {
        for (i = (int)row + 1; i <= (int)g_total_row - 1; i++) {
            for (j = 0; j < g_total_col; j++) {
                g_board[i - 1][j] = g_board[i][j];
            }
        }
        g_total_row -= 1;
        g_score_player2 -= 3;
        return TRUE;
    } else {
        return FALSE;
    }
    return 0;
}

int remove_column(const color_t color, const size_t col)
{
    size_t i;
    int j;
    if (g_total_col <= 0) {
        return FALSE;
    }
    if (col >= g_total_col || col < 0) {
        return FALSE;
    }
    if (color == COLOR_BLACK) { /* 행 진행하면서 열 값들 앞으로 땡겨주기  */
        for (i = 0; i < g_total_row; i++) {
            for (j = (int)col + 1; j <= (int)g_total_col - 1; j++) {
                g_board[i][j - 1] = g_board[i][j];
            }
        }
        g_total_col -= 1;
        g_score_player1 -= 3;
        return TRUE;
    } else if (color == COLOR_WHITE) {
        for (i = 0; i < g_total_row; i++) {
            for (j = col + 1; j <= (int)g_total_col - 1; j++) {
                g_board[i][j - 1] = g_board[i][j];
            }
        }
        g_total_col -= 1;
        g_score_player2 -= 3;
        return TRUE;
    }

    return 0;
}

int swap_rows(const color_t color, const size_t row0, const size_t row1)
{
    size_t i;
    size_t tmp[20] = {0, };

    if ((row1 >= g_total_row || row0 >= g_total_row) || (row1 < 0 || row0 < 0)) {
        return FALSE;
    }
    if (color == COLOR_BLACK) {
        for (i = 0; i < g_total_col; i++) {
            tmp[i] = g_board[row0][i];
            g_board[row0][i] = g_board[row1][i]; 
        }
        for (i = 0; i < g_total_col; i++) {
            g_board[row1][i] = tmp[i];
        }
        g_score_player1 -= 2;

        return TRUE;
    } else if (color == COLOR_WHITE) {
        for (i = 0; i < g_total_col; i++) {
            tmp[i] = g_board[row0][i];
            g_board[row0][i] = g_board[row1][i]; 
        }
        for (i = 0; i < g_total_col; i++) {
            g_board[row1][i] = tmp[i];
        }
        g_score_player2 -= 2;

        return TRUE;
    }

    return 0;
}

int swap_columns(const color_t color, const size_t col0, const size_t col1)
{
    size_t i;
    size_t tmp[20] = {0, };

    if ((col1 >= g_total_col || col0 >= g_total_col) || (col1 < 0 || col0 < 0)) {
        return FALSE;
    }
    if (color == COLOR_BLACK) {
        for (i = 0; i < g_total_row; i++) {
            tmp[i] = g_board[i][col0];
            g_board[i][col0] = g_board[i][col1];
        }
        for (i = 0; i < g_total_row; i++) {
            g_board[i][col1] = tmp[i];
        }
        g_score_player1 -= 2;

        return TRUE;
    } else if (color == COLOR_WHITE) {
        for (i = 0; i < g_total_row; i++) {
            tmp[i] = g_board[i][col0];
            g_board[i][col0] = g_board[i][col1];
        }
        for (i = 0; i < g_total_row; i++) {
            g_board[i][col1] = tmp[i];
        }
        g_score_player2 -= 2;

        return TRUE;
    }
    
    return 0;
}

int copy_row(const color_t color, const size_t src, const size_t dst) /* 원본 src 타겟 dst */
{
    size_t i;
    if ((src >= g_total_row || dst >= g_total_row) || (src < 0 || dst < 0)) {
        return FALSE;
    }
    if (color == COLOR_BLACK) {
        for (i = 0; i < g_total_col; i++) {
            g_board[dst][i] = g_board[src][i];
        }
        g_score_player1 -= 4;

        return TRUE;
    } else if (color == COLOR_WHITE) {
        for (i = 0; i < g_total_col; i++) {
            g_board[dst][i] = g_board[src][i];
        }
        g_score_player2 -= 4;

        return TRUE;
    }

    return 0;
}

int copy_column(const color_t color, const size_t src, const size_t dst) {
    size_t i;
    if ((src >= g_total_col || dst >= g_total_col) || (src < 0 || dst < 0)) {
        return FALSE;
    }
    if (color == COLOR_BLACK) {
        for (i = 0; g_total_row; i++) {
            g_board[i][dst] = g_board[i][src]; 
        }
        g_score_player1 -= 4;

        return TRUE;
    } else if (color == COLOR_WHITE) {
        for (i = 0; g_total_row; i++) {
            g_board[i][dst] = g_board[i][src]; 
        }
        g_score_player2 -= 4;

        return TRUE;
    }

    return 0;
}
