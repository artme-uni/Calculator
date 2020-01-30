#ifndef CALCULATOR_ADD_H
#define CALCULATOR_ADD_H

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct token
{
    int type; // 0 - number, 1 - character
    char symbol;
    int value;
} token;

int getNumber(char c);

int getPriority(char op);

double calculateOperator(char op, double a, double b);

token *parse(char *string, int *tokenCount);

token *convertToRPN(token *expression, int expressionLength, int *resultLength);

int calculateRPN(token *rpn, int lenght, double *result);

#endif //CALCULATOR_ADD_H
