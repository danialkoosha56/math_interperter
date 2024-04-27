#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct _opertator
{
    uint8_t operation;
    int endAdress;
}operator;

int calc(uint8_t *);
void findOperation(uint8_t *str, operator *op);
void findValue(uint8_t *str, int *value);
// 1*2*4*8=
void main()
{
    uint8_t string[100];
    int result;
    printf("write your math porblem:");
    scanf("%s", string);
    result = calc(string);
    printf("\r\n%d", result);
    return;
}

//(12+14*(17-3)*2-2)/2=
int calc(uint8_t * str)
{
    uint8_t *dumm_buff;
    int buff=0;
    operator op;
    int firstValue;
    int afterValue;

    findOperation(str, &op);
    findValue(str, &firstValue);
    while( (op.operation == '*') || (op.operation == '/'))
    {
        switch (op.operation)
        {
        case '*':
            findValue(str+ op.endAdress+1, &afterValue);
            firstValue = firstValue * afterValue;
            str += op.endAdress+1;
            op = (operator){0};
            findOperation(str, &op);
            break;

        case '/':
            findValue(str+ op.endAdress+1, &afterValue);
            firstValue = firstValue / afterValue;
            str += op.endAdress+1;
            op = (operator){0};
            findOperation(str, &op);
        
        default:
            break;
        }
    }
    
    switch (op.operation)
    {
    case '+':
        buff = calc(str + op.endAdress + 1);
        return firstValue + buff;
        break;
     case '-':
        buff = calc(str + op.endAdress + 1);
        return firstValue - buff;
        break;
    case ')':
        return firstValue;
        break;
    case '=':
        return firstValue;
        break;
    
    default:
        break;
    }

}

void findOperation(uint8_t *str, operator *op)
{
    int start;
    int end;
    int cnt=0;
    int parantes=0;
    if( *str == '(')
    {
        parantes++;
        str++;
        cnt++;
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
            cnt++;
        }
        op->operation = *str;
        op->endAdress = cnt;
    }
    else
    {
        while ( '0'<=*str && *str<='9')
        {
            str++;
            cnt++;
        }
        op->operation = *str;
        op->endAdress = cnt;
    }
}

void findValue(uint8_t *str, int *value)
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