#include "pomoku.h"

size_t total_row = 15;
size_t total_col = 15;
size_t score_player1 = 0;
size_t score_player2 = 0;
size_t board[15][15] = { 0, };

void init_game(void) { /*게임 초기화*/
	size_t i, j;
	total_row, total_col = 15;
	score_player1, score_player2 = 0;

    for (i = 0; i < total_row; i++) {
        for (j = 0; j < total_col; j++) {
            board[total_row][total_col] = 13;
        }
    }

}


size_t get_row_count(void) {
    return total_row;
}

size_t get_column_count(void) {
    return total_col;
}

int get_score(const color_t color) { /*색별 점수 확인*/
    if (color == COLOR_BLACK) {
        return score_player1;
    }
    else if (color == COLOR_WHITE) {
        return score_player2;
    }
    else {
        return -1;
    }
}

int get_color(const size_t row, const size_t col) { /*색 확인*/
    if (board[row][col] == COLOR_BLACK) {
        return 0;
    }
    else if (board[row][col] == COLOR_WHITE) {
        return 1;
    }
    else {
        return -1;
    }
}

int is_placeable(const size_t row, const size_t col) {
    if (board[row][col] == 13) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

int place_stone(const color_t color, const size_t row, const size_t col) {
    if (board[row][col] == COLOR_BLACK) {
        return FALSE;
    }
    else if (board[row][col] == COLOR_WHITE) {
        return FALSE;
    }
    else {
        board[row][col] = color;
        return TRUE;
    }
}

/* special moves */
int insert_row(const color_t color, const size_t row) {
    size_t i;
    size_t j;
    if (color == COLOR_BLACK) { /* 들어온 색이 검정색이라면 */
        if (total_row > 20) { /* 늘어난 행의 수가 20을 넘는다면 */
            return FALSE;
        }

        for (i = total_row - 1; i >= row; i--) { /* 보드의 최대 행 - 1 부터 넣을려는 행까지의 배열의 값들을 오른쪽으로 덮어줄 것임*/
            for (j = 0; j < total_col; j++) { /*행만 건드는 것이므로*/
                board[i + 1][j] = board[i][j]; /* 덮어주기 */
            }
        }
        for (j = 0; j < total_col; j++) { /* 넣을려는 행의 값 13으로 초기화*/
            board[row][j] = 13;
        }
        total_row += 1;
        score_player1 -= 3;
        return TRUE;
    }
    else if (color == COLOR_WHITE) { /*들어온 색이 하얀색이라면 */
        if (total_row > 20) { /* 늘어난 행의 수가 20을 넘는다면 */
            return FALSE;
        }

        for (i = total_row - 1; i >= row; i--) { /* 보드의 최대 행 - 1 부터 넣을려는 행까지의 배열의 값들을 덮어줄 것임*/
            for (j = 0; j < total_col; j++) { /*행만 건드는 것이므로*/
                board[i + 1][j] = board[i][j]; /* 덮어주기 */
            }
        }
        for (j = 0; j < total_col; j++) { /* 넣을려는 행 13으로 초기화*/
            board[row][j] = 13;
        }
        total_row += 1;
        score_player2 -= 3;
        return TRUE;
    }
    else {
        return FALSE;
    }
}

int insert_column(const color_t color, const size_t col) {
    if (color == COLOR_BLACK) { /* 들어온 색이 검정색이라면 */
        size_t i;
        size_t j;

        if (total_col > 20) { /* col길이가 20을 넘는다면 */
            return FALSE;
        }
        for (i = 0; i < total_row; i++) { /* 열만 건드는 것*/
            for (j = total_col - 1; j >= col; j--) { /* 보드의 최대 열 - 1 부터 넣을려는 열까지의 배열의 값들을 덮어줄 것임*/
                board[i][j + 1] = board[i][j]; /* 덮기 */
            }
        }
        for (i = 0; i < total_row; i++) { /* 넣을려는 열 13으로 초기화 */
            board[i][col] = 13;
        }
        total_col += 1;
        score_player1 -= 3;
        return TRUE;
    }
    else if (color == COLOR_WHITE) {
        size_t i;
        size_t j;

        if (total_col > 20) { /* col길이가 20을 넘는다면 */
            return FALSE;
        }
        for (i = 0; i < total_row; i++) { /* 열만 건드는 것*/
            for (j = total_col - 1; j >= col; j--) { /* 보드의 최대 열 - 1 부터 넣을려는 열까지의 배열의 값들을 덮어줄 것임*/
                board[i][j + 1] = board[i][j]; /* 덮기 */
            }
        }
        for (i = 0; i < total_row; i++) { /* 넣을려는 열 13으로 초기화 */
            board[i][col] = 13;
        }
        total_col += 1;
        score_player2 -= 3;
        return TRUE;
    }
    else {
        return FALSE;
    }
}

int remove_row(const color_t color, const size_t row) {

}

int remove_column(const color_t color, const size_t col);

int swap_rows(const color_t color, const size_t row0, const size_t row1);

int swap_columns(const color_t color, const size_t col0, const size_t col1);

int copy_row(const color_t color, const size_t src, const size_t dst);

int copy_column(const color_t color, const size_t src, const size_t dst);
