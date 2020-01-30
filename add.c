#include "add.h"

int getNumber(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    else
        return -1;
}

int getPriority(char op)
{
    switch (op)
    {
        case '*':
        case '/':
            return 3;
        case '+':
        case '-':
            return 2;
        case '(':
        case ')':
            return 1;
        default:
            return -1;
    }
}

double calculateOperator(char op, double a, double b)
{
    switch (op)
    {
        case '*':
            return a * b;
        case '/':
            return a / b;
        case '+':
            return a + b;
        case '-':
            return a - b;
        default:
            printf("badinput fot calculateOperator");
            exit(1);
    }
}

token *parse(char *string, int *tokenCount)
{
    token *result = malloc(sizeof(token) * strlen(string));

    *tokenCount = 0;
    int boof = 0;
    int number = 0;

    for (int i = 0; i < strlen(string); i++)
    {
        if (getNumber(string[i]) != -1)
        {
            number = 1;
            boof *= 10;
            boof += getNumber(string[i]);
        }
        else
        {
            if (getPriority(string[i]) == -1)
                return NULL;

            if (number != 0)
            {
                result[*tokenCount].type = 0;
                result[*tokenCount].value = boof;
                (*tokenCount)++;
                number = 0;
                boof = 0;
            }

            result[*tokenCount].type = 1;
            result[*tokenCount].symbol = string[i];
            (*tokenCount)++;
        }
    }

    if (number)
    {
        result[*tokenCount].type = 0;
        result[*tokenCount].value = boof;
        (*tokenCount)++;
    }

    return result;
}

token *convertToRPN(token *expression, int expressionLength, int *resultLength)
{
    token *result = malloc(sizeof(token) * expressionLength);
    *resultLength = 0;
    token *stack = malloc(sizeof(token) * expressionLength);
    int stackEnd = -1;

    for (int i = 0; i < expressionLength; i++)
    {
        if (expression[i].type == 0)
        {
            result[(*resultLength)++] = expression[i];
        }
        else if (expression[i].type == 1 && expression[i].symbol == '(')
        {
            if (i < expressionLength - 1 && expression[i + 1].type == 1 && expression[i + 1].symbol == ')')
                return NULL; // "()"
            stack[++stackEnd] = expression[i];
        }
        else if (expression[i].type == 1 && expression[i].symbol == ')')
        {
            while (stackEnd >= 0)
            {
                if (stack[stackEnd].type == 1 && stack[stackEnd].symbol == '(')
                    break;
                result[(*resultLength)++] = stack[stackEnd--];
            }

            if (stackEnd == -1)
                return NULL; // Invalid brackets

            stackEnd--; // Remove '('
        }
        else
        {
            int opPriority = getPriority(expression[i].symbol);

            while (stackEnd >= 0 && opPriority <= getPriority(stack[stackEnd].symbol))
            {
                result[(*resultLength)++] = stack[stackEnd--];
            }
            stack[++stackEnd] = expression[i];
        }
    }

    while (stackEnd >= 0)
    {
        if (stack[stackEnd].type == 1 && stack[stackEnd].symbol == '(')
            return NULL; // Invalid brackets

        result[(*resultLength)++] = stack[stackEnd--];
    }

    free(stack);

    return result;
}

int calculateRPN(token *rpn, int lenght, double *result)
{
    double *stack = malloc(sizeof(double) * lenght);
    int length_stack = 0;

    for (int i = 0; i < lenght; i++)
    {
        token current_token = rpn[i];

        if (current_token.type == 0)
        {
            stack[length_stack++] = current_token.value;
        }
        else
        {
            if (length_stack < 1)
                return -1;
            double right = stack[length_stack - 1];
            length_stack--;

            if (length_stack < 1)
                return -1;
            double left = stack[length_stack - 1];
            length_stack--;

            char operator = current_token.symbol;

            if ((operator == '/') && (right == 0))
                return -2;

            double calculate = calculateOperator(operator, left, right);

            stack[length_stack] = calculate;
            length_stack++;
        }
    }

    if (length_stack == 1)
    {
        *result = stack[length_stack - 1];
        return 0;
    }
    else
        return -1;

}
