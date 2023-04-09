#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_STACK_SIZE 100

typedef char element;
typedef struct
{
    element data[MAX_STACK_SIZE];
    int top;
}StackType;

init_stack(StackType* s)
{
    s->top = -1;
}
int is_empty(StackType* s)
{
    return (s->top == -1);
}

void push(StackType* s, element item)
{
    s->data[++(s->top)] = item;
}
element pop(StackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        return;
    }
    else return s->data[(s->top)--];
}


int eval(char exp[])
{
    int op1, op2, value, i = 0; //피연산자
    int len = strlen(exp); //라이브러리 함수, 길이측정
    char ch;
    StackType s; //구조체스택
    init_stack(&s);
    for (i = 0; i < len; i++)
    {
        ch = exp[i];
        if (((ch - 'A') >= 0) && ((ch - 'A') <=57)) //아스키코드값 65~122인 문자가 입력되면 invalid charater 출력
            {
                printf("Invalid character");
                exit(1);
            }
        else if (ch != '+' && ch != '-' && ch != '*' && ch != '/')//입력이 피연산자라면
        {
            push(&s, ch - '0'); //문자 바로 집어넣으면됨 (나중에 빼서 숫자로 바꿔서 계산)
        }
       

        //value = ch - '0' <-잘못됨 (element에 char값 집어넣기로 했는데 int값임
        else //연산자일경우
        {
            if (is_empty(&s))
            {
                fprintf(stderr, "피연산자오류");
            }
            //pop하기 전에 스택 비어있는지 확인하는 함수 필요
            else
            {
                op2 = pop(&s);
                op1 = pop(&s);

                switch (ch) {
                case '+': push(&s, op2 + op1); //pop한것 더해서 집어넣기
                    break; //switch 벗어나기
                case '-': push(&s, (op2 - op1));
                    break;
                case '*': push(&s, (op2 * op1));
                    break;
                case '/': push(&s, (op2 / op1));
                    break;

                }

            }
        }
    }
    return pop(&s);
}

int main()
{
    int result;
    char* topostfix = (char*)malloc(sizeof(char*));
    printf("Postfix expression : ");
    gets(topostfix);
    result = eval(topostfix);
    printf("Result: %d\n", result);
    system("pause");
    return 0;
}