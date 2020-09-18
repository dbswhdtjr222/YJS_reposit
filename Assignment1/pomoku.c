#include "pomoku.h"

size_t total_row = 15;
size_t total_col = 15;
size_t score_player1 = 0;
size_t score_player2 = 0;
size_t board[15][15] = { 0, };

void init_game(void) 
{ /*���� �ʱ�ȭ*/
	size_t i;
    size_t j;
    total_row = 15;
    total_col = 15;
    score_player1 = 0;
    score_player2 = 0;

    for (i = 0; i < total_row; i++) {
        for (j = 0; j < total_col; j++) {
            board[i][j] = 13;
        }
    }

}


size_t get_row_count(void) 
{
    return total_row;
}

size_t get_column_count(void) 
{
    return total_col;
}

int get_score(const color_t color) 
{ /*���� ���� Ȯ��*/
    if (color == COLOR_BLACK) {
        return score_player1;
    } else if (color == COLOR_WHITE) {
        return score_player2;
    } else {
        return -1;
    }

    return 0;
}

int get_color(const size_t row, const size_t col) 
{ /*�� Ȯ��*/
    if (board[row][col] == COLOR_BLACK) {
        return 0;
    } else if (board[row][col] == COLOR_WHITE) {
        return 1;
    } else {
        return -1;
    }
    
    return 0;
}

int is_placeable(const size_t row, const size_t col) 
{
    if (board[row][col] == 13) {
        return TRUE;
    } else {
        return FALSE;
    }

    return 0;
}

int place_stone(const color_t color, const size_t row, const size_t col) 
{
    if (board[row][col] == COLOR_BLACK) {
        return FALSE;
    } else if (board[row][col] == COLOR_WHITE) {
        return FALSE;
    } else {
        board[row][col] = color;
        return TRUE;
    }

    return 0;
}

/* special moves */
int insert_row(const color_t color, const size_t row) 
{
    size_t i;
    size_t j;
    if (color == COLOR_BLACK) { /* ���� ���� �������̶�� */
        if (total_row > 20) { /* �þ ���� ���� 20�� �Ѵ´ٸ� */
            return FALSE;
        }

        for (i = (int)total_row - 1; i >= row; i--) { /* ������ �ִ� �� - 1 ���� �������� ������� �迭�� ������ ���������� ������ ����*/
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
    } else if (color == COLOR_WHITE) { /*���� ���� �Ͼ���̶�� */
        if (total_row > 20) { /* �þ ���� ���� 20�� �Ѵ´ٸ� */
            return FALSE;
        }

        for (i = (int)total_row - 1; i >= row; i--) { /* ������ �ִ� �� - 1 ���� �������� ������� �迭�� ������ ������ ����*/
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
    } else {
        return FALSE;
    }

    return 0;
}

int insert_column(const color_t color, const size_t col) 
{
    if (color == COLOR_BLACK) { /* ���� ���� �������̶�� */
        size_t i;
        size_t j;

        if (total_col > 20) { /* col���̰� 20�� �Ѵ´ٸ� */
            return FALSE;
        }
        for (i = 0; i < total_row; i++) { /* ���� �ǵ�� ��*/
            for (j = (int)total_col - 1; j >= col; j--) { /* ������ �ִ� �� - 1 ���� �������� �������� �迭�� ������ ������ ����*/
                board[i][j + 1] = board[i][j]; /* ���� */
            }
        }
        for (i = 0; i < total_row; i++) { /* �������� �� 13���� �ʱ�ȭ */
            board[i][col] = 13;
        }
        total_col += 1;
        score_player1 -= 3;

        return TRUE;
    } else if (color == COLOR_WHITE) {
        size_t i;
        size_t j;

        if (total_col > 20) { /* col���̰� 20�� �Ѵ´ٸ� */
            return FALSE;
        }
        for (i = 0; i < total_row; i++) { /* ���� �ǵ�� ��*/
            for (j = (int)total_col - 1; j >= col; j--) { /* ������ �ִ� �� - 1 ���� �������� �������� �迭�� ������ ������ ����*/
                board[i][j + 1] = board[i][j]; /* ���� */
            }
        }
        for (i = 0; i < total_row; i++) { /* �������� �� 13���� �ʱ�ȭ */
            board[i][col] = 13;
        }
        total_col += 1;
        score_player2 -= 3;
        return TRUE;
    } else {
        return FALSE;
    }

    return 0;
}

int remove_row(const color_t color, const size_t row) 
{ /* ���� �� ���� */
    size_t i, j;
    if (color == COLOR_BLACK) {
        for (i = (int)row + 1; i <= total_row - 1; i++) {
            for (j = 0; j < total_col; j++) {
                board[i - 1][j] = board[i][j];
            }
        }
        total_row -= 1;
        score_player1 -= 3;
        return TRUE;
    } else if (color == COLOR_WHITE) {
        for (i = (int)row + 1; i <= total_row - 1; i++) {
            for (j = 0; j < total_col; j++) {
                board[i - 1][j] = board[i][j];
            }
        }
        total_row -= 1;
        score_player2 -= 3;
        return TRUE;
    } else {
        return FALSE;
    }
    return 0;
}

int remove_column(const color_t color, const size_t col)
{
    size_t i;
    size_t j;
    if(col >= total_col || col < 0) {
        return FALSE;
    }
    if (color == COLOR_BLACK) { /* 행 진행하면서 열 값들 앞으로 땡겨주기  */
        for (i = 0; i < total_row; i++) {
            for (j = (int)total_col - 1; j >= col; j--) {
                board[i][j-1] = board[i][j];
            }
        }
        total_col -= 1;
        score_player1 -= 3;
        return TRUE;
    } else if(color == COLOR_WHITE) {
        for (i = 0; i < total_row; i++) {
            for (j = total_col - 1; j >= col; j--) {
                board[i][j-1] = board[i][j];
            }
        }
        total_col -= 1;
        score_player2 -= 3;
        return TRUE;
    }

    return 0;
}

int swap_rows(const color_t color, const size_t row0, const size_t row1)
{
    size_t i;
    size_t tmp[20] = {0, };

    if((row1 >= total_row || row0 >= total_row) || (row1 < 0 || row0 < 0)) {
        return FALSE;
    }
    if (color == COLOR_BLACK) {
        for (i = 0; i < total_col; i++) {
            tmp[i] = board[row0][i];
            board[row0][i] = board[row1][i]; 
        }
        for (i = 0; i < total_col; i++) {
            board[row1][i] = tmp[i];
        }
        score_player1 -= 2;

        return TRUE;
    } else if (color == COLOR_WHITE) {
        for (i = 0; i < total_col; i++) {
            tmp[i] = board[row0][i];
            board[row0][i] = board[row1][i]; 
        }
        for (i = 0; i < total_col; i++) {
            board[row1][i] = tmp[i];
        }
        score_player2 -= 2;

        return TRUE;
    }

    return 0;
}

int swap_columns(const color_t color, const size_t col0, const size_t col1)
{
    size_t i;
    size_t tmp[20] = {0, };

    if ((col1 >= total_col || col0 >= total_col) || (col1 < 0 || col0 < 0)) {
        return FALSE;
    }
    if (color == COLOR_BLACK) {
        for (i = 0; i < total_row; i++) {
            tmp[i] = board[i][col0];
            board[i][col0] = board[i][col1];
        }
        for (i = 0; i < total_row; i++) {
            board[i][col1] = tmp[i];
        }
        score_player1 -= 2;

        return TRUE;
    } else if (color == COLOR_WHITE) {
               for (i = 0; i < total_row; i++) {
            tmp[i] = board[i][col0];
            board[i][col0] = board[i][col1];
        }
        for (i = 0; i < total_row; i++) {
            board[i][col1] = tmp[i];
        }
        score_player2 -= 2;

        return TRUE;
    }
    
    return 0;
}

int copy_row(const color_t color, const size_t src, const size_t dst) /* 원본 src 타겟 dst */
{
    size_t i;
    if ((src >= total_row || dst >= total_row) || (src < 0 || dst < 0)) {
        return FALSE;
    }
    if (color == COLOR_BLACK) {
        for (i = 0; i < total_col; i++) {
            board[dst][i] = board[src][i];
        }
        score_player1 -= 4;

        return TRUE;
    } else if (color == COLOR_WHITE) {
            for (i = 0; i < total_col; i++) {
            board[dst][i] = board[src][i];
        }
        score_player2 -= 4;

        return TRUE;
    }

    return 0;
}

int copy_column(const color_t color, const size_t src, const size_t dst) {
    size_t i;
    if ((src >= total_col || dst >= total_col) || (src < 0 || dst < 0)) {
        return FALSE;
    }
    if (color == COLOR_BLACK) {
        for (i = 0; total_row; i++) {
            board[i][dst] = board[i][src]; 
        }
        score_player1 -= 4;

        return TRUE;
    } else if (color == COLOR_WHITE) {
        for (i = 0; total_row; i++) {
            board[i][dst] = board[i][src]; 
        }
        score_player2 -= 4;

        return TRUE;
    }

    return 0;
}
