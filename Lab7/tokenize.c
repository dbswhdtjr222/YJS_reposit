#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>
#include "tokenize.h"

#define FULL_OF_TOKENS (128)
char** tokenize_malloc(const char* str, const char* delim)
{
    const char* str_p = str;
    const char* start_p = str;
    const char* delim_p;
    const char* token = NULL;
     
    char** tokens = malloc(sizeof(char*) * (FULL_OF_TOKENS + 1));

    int token_buffer = 0;
    size_t tokens_length = 0;
    if (str == NULL || delim == NULL) {
        return NULL;
    }
    while (*str_p != '\0') {
        for (delim_p = delim; *delim_p != '\0'; delim_p++) {
            if (*str_p == *delim_p) {
                if (token == NULL) {
                    token = start_p;
                }
                {
                    char* save_str = malloc(token_buffer + 1);
                    strncpy(save_str, token, token_buffer);
                    save_str[token_buffer] = '\0';
                    tokens[tokens_length++] = save_str;
                }

                token = NULL;
                token_buffer = 0;
                while ((65 > * str_p || *str_p > 90) && (97 > * str_p || *str_p > 122)) { /* alpabet discriminated */
                    start_p = str_p + 1;
                    str_p++;
                    if (*str_p == '\0') {
                        tokens[tokens_length] = NULL;
                        return tokens;
                    }
                }
                goto next;
            } else {
                continue;
            }
        }
        token_buffer++;
        str_p++;
    next:;
    }
    
    return tokens;
}
