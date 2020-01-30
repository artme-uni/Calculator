#include "add.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("bad input\n");
        return 1;
    }

    int tokensLenght = -1;

    token *tokens = parse(argv[1], &tokensLenght);
    if (tokens == NULL)
    {
        printf("syntax error\n");
        exit(0);
    }

    int rpnLength = -1;
    token *rpn = convertToRPN(tokens, tokensLenght, &rpnLength);
    if (rpn == NULL)
    {
        printf("syntax error\n");
        exit(0);
    }

    double result;

    int err = calculateRPN(rpn, rpnLength, &result);
    if (err == -2)
    {
        printf("division by zero\n");
        exit(0);
    }
    if (err == -1)
    {
        printf("syntax error\n");
        exit(0);
    }

    if ((result - (int) result) == 0)
        printf("%d\n", (int) result);
    else
        printf("%lf\n", result);

    return 0;
}