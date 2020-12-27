#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "parentheses.h"
// 스택 자료구조를 이용해서 괄호 쌍 찾기 구현
typedef struct{
    size_t* data;
    size_t top;
}stack_t;
int compare(const void* first, const void* second){
    parenthesis_t* p1 = (parentheses_t*)first;
    parenthesis_t* p2 = (parentheses_t*)second;

    if(p1->opening_index < p2->opening_index){
        return -1;
    }
    if (p1->opening_index > p2->opening_index){
        return 1;
    }

    return 0;
}
size_t get_matching_parentheses(parenthesis_t* parentheses, size_t max_size, const char* str)
{
    int str_length = 0;
    int num = 0;
    int i = 0;
    stack_t bracket;
    stack_t braces;
    stack_t square;
    stack_t angle;
    stack_t* stack_p;

    str_length = strlen(str);
    
    bracket.data = malloc(sizeof(size_t) * str_length); // not yet free 
    bracket.top = 0;
    braces.data = malloc(sizeof(size_t) * str_length); // not yet free 
    braces.top = 0;
    square.data = malloc(sizeof(size_t) * str_length); // not yet free
    square.top = 0;
    angle.data = malloc(sizeof(size_t) * str_length); // not yet free
    angle.top = 0;

    for(i = 0; i < str_length; i++) {
        switch(str[i]){
            case '<':
                stack_p = &angle;
                goto push;
                break;
            case '>':
                stack_p = &angle;
                goto pop;
                break;
            case '{':
                stack_p = &braces;
                goto push;
                break;
            case '}':
                stack_p = &braces;
                goto pop;
                break;
            case '[':
                stack_p = &square;
                goto push;
                break;
            case ']':
                stack_p = &square;
                goto pop;
                break;
            case '(':
                stack_p = &bracket;
                goto push;
                break;
            case ')':
                stack_p = &bracket;
                goto pop;
                break;
        }
push:
        stack_p->data[stack_p->top++] = i; // starting point
        continue;
pop:
        if(stack_p->top > 0){
            stack_p->top--;
            parentheses[num].opening_index = stack_p->data[stack_p->top];
            parentheses[num].closeing_index = i;
            num++;
        }
    }

    free(braces.data);
    free(bracket.data);
    free(angle.data);
    free(square.data);

    qsort(parentheses, num, sizeof(parenthesis_t), compare);

    return num;
}
