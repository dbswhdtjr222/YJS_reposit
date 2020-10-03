#include <limits.h>
#include <stdio.h>
#include "my_string.h"

static char* current_str;

void reverse(char* str)
{
	char temp_char; /*임시 char문자*/
	size_t i = 0; /*시작 인덱스*/
	size_t j = 0; /*끝 인덱스*/
	//if (*str == '\0') {
	//	return;
	//}
	//else {
	//	reverse(str + 1);
	//	printf("%c", *str);
	//}
	if (*str == '\0') {
		return;
	}

	while (*(str + i) != '\0') {
		i++;
	}
	while (j < i - 1) {
		temp_char = str[j];
		str[j] = str[i - 1];
		str[i - 1] = temp_char;
		j++;
		i--;
	}
}

int index_of(const char* str, const char* word)
{
	size_t word_length = 0u;
	size_t str_index = 0u;
	size_t word_count = 0u;

	if (*word == '\0') {
		return 0;
	} else if (*str == '\0') {
		return -1;
	} else {
		while (*(word + word_length) != '\0') {
			word_length++;
		}
		while (*(str + str_index) != '\0') {
			if (*(str + str_index) == *(word + word_count)) {
				word_count++;
				if (word_count == word_length) {
					str_index++;
					return str_index - word_count;
				}
			}
			else {
				word_count = 0;
			}
			str_index++;
		}
	}
	return -1;
}

void reverse_by_words(char* str)
{
	char temp; /*임시 char문자*/
	size_t count = 0; /*끝 인덱스*/
	size_t j = 0; /*현재 인덱스의 위치*/
	size_t i = 0; /* 시작 인덱스*/
	while (*(str + j) != '\0') {
		while (*(str + j) != ' ' && *(str + j) != '\0') {
			count++;
			j++;
		}
		while (i < count-1) {
			temp = str[i];
			str[i] = str[count-1];
			str[count-1] = temp;
			i++;
			count--;
		}
		if (*(str + j) == '\0') {
			break;
		}
		j++;
		i = j;
		count = j;
	}
}

char* tokenize(char* str, const char* delims)
{
	size_t i = 0;
	size_t j = 0;
	if (str == NULL) {
		str = current_str;
	}
	else {
		current_str = str;
	}
	while (*(delims + i) != '\0') {
		while (*(delims + j) != '\0') {
			if (*current_str == *(delims + j)) {
				*current_str = '\0';
			}
			j++;
		}
		if (*current_str == '\0') {
			current_str++;
		}
		j = 0;
		i++;
	}
	i = 0;
	str = current_str;
	while (*current_str != '\0') {
		while (*(delims + i) != '\0') {
			if (*current_str == *(delims + i)) {
				*current_str = '\0';
				current_str++;
				return str;
			}
			i++;
		}
		current_str++;
		i = 0;
	}
	if (*current_str == '\0') {
		return NULL;
	}
	return str;
}

char* reverse_tokenize(char* str, const char* delims)
{
	size_t i = 0;
	size_t j = 0;
	if (str == NULL) {
		str = current_str;
	}
	else {
		current_str = str;
	}
	while (*(delims + i) != '\0') {
		while (*(delims + j) != '\0') {
			if (*current_str == *(delims + j)) {
				*current_str = '\0';
			}
			j++;
		}
		if (*current_str == '\0') {
			current_str++;
		}
		j = 0;
		i++;
	}
	i = 0;
	str = current_str;
	while (*current_str != '\0') {
		while (*(delims + i) != '\0') {
			if (*current_str == *(delims + i)) {
				*current_str = '\0';
				current_str++;
				reverse(str);
				return str;
			}
			i++;
		}
		current_str++;
		i = 0;
	}
	if (*current_str == '\0') {
		return NULL;
	}
	return str;
}
