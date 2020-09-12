#include "pomoku.h"

size_t total_row = 15;
size_t total_col = 15;
size_t score_player1 = 0;
size_t score_player2 = 0;
size_t board[15][15] = { 0, };

void init_game(void) { /*���� �ʱ�ȭ*/
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

int get_score(const color_t color) { /*���� ���� Ȯ��*/
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

int get_color(const size_t row, const size_t col) { /*�� Ȯ��*/
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
    if (color == COLOR_BLACK) { /* ���� ���� �������̶�� */
        if (total_row > 20) { /* �þ ���� ���� 20�� �Ѵ´ٸ� */
            return FALSE;
        }

        for (i = total_row - 1; i >= row; i--) { /* ������ �ִ� �� - 1 ���� �������� ������� �迭�� ������ ���������� ������ ����*/
            for (j = 0; j < total_col; j++) { /*�ุ �ǵ�� ���̹Ƿ�*/
                board[i + 1][j] = board[i][j]; /* �����ֱ� */
            }
        }
        for (j = 0; j < total_col; j++) { /* �������� ���� �� 13���� �ʱ�ȭ*/
            board[row][j] = 13;
        }
        total_row += 1;
        score_player1 -= 3;
        return TRUE;
    }
    else if (color == COLOR_WHITE) { /*���� ���� �Ͼ���̶�� */
        if (total_row > 20) { /* �þ ���� ���� 20�� �Ѵ´ٸ� */
            return FALSE;
        }

        for (i = total_row - 1; i >= row; i--) { /* ������ �ִ� �� - 1 ���� �������� ������� �迭�� ������ ������ ����*/
            for (j = 0; j < total_col; j++) { /*�ุ �ǵ�� ���̹Ƿ�*/
                board[i + 1][j] = board[i][j]; /* �����ֱ� */
            }
        }
        for (j = 0; j < total_col; j++) { /* �������� �� 13���� �ʱ�ȭ*/
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
    if (color == COLOR_BLACK) { /* ���� ���� �������̶�� */
        size_t i;
        size_t j;

        if (total_col > 20) { /* col���̰� 20�� �Ѵ´ٸ� */
            return FALSE;
        }
        for (i = 0; i < total_row; i++) { /* ���� �ǵ�� ��*/
            for (j = total_col - 1; j >= col; j--) { /* ������ �ִ� �� - 1 ���� �������� �������� �迭�� ������ ������ ����*/
                board[i][j + 1] = board[i][j]; /* ���� */
            }
        }
        for (i = 0; i < total_row; i++) { /* �������� �� 13���� �ʱ�ȭ */
            board[i][col] = 13;
        }
        total_col += 1;
        score_player1 -= 3;
        return TRUE;
    }
    else if (color == COLOR_WHITE) {
        size_t i;
        size_t j;

        if (total_col > 20) { /* col���̰� 20�� �Ѵ´ٸ� */
            return FALSE;
        }
        for (i = 0; i < total_row; i++) { /* ���� �ǵ�� ��*/
            for (j = total_col - 1; j >= col; j--) { /* ������ �ִ� �� - 1 ���� �������� �������� �迭�� ������ ������ ����*/
                board[i][j + 1] = board[i][j]; /* ���� */
            }
        }
        for (i = 0; i < total_row; i++) { /* �������� �� 13���� �ʱ�ȭ */
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
