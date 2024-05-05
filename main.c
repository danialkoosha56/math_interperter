#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum
{
    PLUS,
    MINUS,
    MULTIPLICATION,
    DEVIDE,
    EXPONENTE,
    EQUAL,
    OPEN_PARANTES,
    CLOSE_PARANTES,
}operatorType_e;

typedef struct _opertator
{
    char operation;
    char *Address;
}operator;

int calc(char *);
void findOperation(char *str, operator *op);
void findValue(char *str, int *value);
int _pow(int base, int exponent);

void main()
{
    char string[100];
    int result;
    printf("write your math porblem:");
    scanf("%s", string);
    result = calc(string);
    printf("\r\n%d", result);
    return;
}

//(12+14(17-3)2-2)/2=
//(12+14*(17-3)*2-2)/2=
int calc(char * str)
{
    char *dumm_buff;
    int buff=0;
    operator op;
    int firstValue;
    int afterValue;

    findOperation(str, &op);
    findValue(str, &firstValue);
    while( op.operation == EXPONENTE)
    {
        findValue(op.Address+1, &afterValue);
        firstValue = _pow(firstValue, afterValue);
        str = op.Address+1;
        memset(&op, 0, sizeof(operator));
        findOperation(str, &op);
    }
    while( (op.operation == MULTIPLICATION) || (op.operation == DEVIDE))
    {
        switch (op.operation)
        {
        case MULTIPLICATION:
            findValue(op.Address+1, &afterValue);
            firstValue = firstValue * afterValue;
            str = op.Address+1;
            memset(&op, 0, sizeof(operator));
            findOperation(str, &op);
            break;

        case DEVIDE:
            findValue(op.Address+1, &afterValue);
            firstValue = firstValue / afterValue;
            str = op.Address+1;
            memset(&op, 0, sizeof(operator));
            findOperation(str, &op);
        
        default:
            break;
        }
    }
    
    switch (op.operation)
    {
    case PLUS:
        buff = calc(op.Address + 1);
        return firstValue + buff;
        break;
     case MINUS:
        buff = calc(op.Address + 1);
        return firstValue - buff;
        break;
    case CLOSE_PARANTES:
        return firstValue;
        break;
    case EQUAL:
        return firstValue;
        break;
    
    default:
        break;
    }

}

void findOperation(char *str, operator *op)
{
    int start;
    int end;
    int parantes=0;
    if( *str == '(')
    {
        parantes++;
        str++;
        while ( parantes != 0)
        {
            if (*str == '(')
            {
                parantes++;
            }
            if (*str == ')')
            {
                parantes--;
            }
            str++;
        }

        if ( isdigit(*str))
        {
            str--;
            op->Address = str;
            op->operation = MULTIPLICATION;
            return;
        }
    }
    else
    {
        while ( isdigit(*str))
        {
            str++;
        }
    }

    op->Address = str;
    switch (*str)
    {
    case '+':
        op->operation = PLUS;
        break;
    case '-':
        op->operation = MINUS;
        break;
    case '*':
        op->operation = MULTIPLICATION;
        break;
    case '/':
        op->operation = DEVIDE;
        break;
    case '(':
        op->operation = MULTIPLICATION;
        --op->Address;
        break;
    case ')':
        op->operation = CLOSE_PARANTES;
        break;
    case '=':
        op->operation = EQUAL;
        break;
    case '^':
        op->operation = EXPONENTE ;
        break;
    case '\0':
        op->operation = EQUAL;
        break;
    
    default:
        break;
    }
}

void findValue(char *str, int *value)
{
    if( *str == '(')
    {
        *value = calc( str+1 );
    }
    else
    {
        *value = atoi(str);
    }
}

int _pow(int base, int exponent)
{
    if (base == 0)
        return 0;
    if( exponent == 0)
        return 1;
    return _pow(base,exponent-1) * base;
}
