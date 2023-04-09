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
        fprintf(stderr, "���� ���� ����\n");
        return;
    }
    else return s->data[(s->top)--];
}


int eval(char exp[])
{
    int op1, op2, value, i = 0; //�ǿ�����
    int len = strlen(exp); //���̺귯�� �Լ�, ��������
    char ch;
    StackType s; //����ü����
    init_stack(&s);
    for (i = 0; i < len; i++)
    {
        ch = exp[i];
        if (((ch - 'A') >= 0) && ((ch - 'A') <=57)) //�ƽ�Ű�ڵ尪 65~122�� ���ڰ� �ԷµǸ� invalid charater ���
            {
                printf("Invalid character");
                exit(1);
            }
        else if (ch != '+' && ch != '-' && ch != '*' && ch != '/')//�Է��� �ǿ����ڶ��
        {
            push(&s, ch - '0'); //���� �ٷ� ���������� (���߿� ���� ���ڷ� �ٲ㼭 ���)
        }
       

        //value = ch - '0' <-�߸��� (element�� char�� ����ֱ�� �ߴµ� int����
        else //�������ϰ��
        {
            if (is_empty(&s))
            {
                fprintf(stderr, "�ǿ����ڿ���");
            }
            //pop�ϱ� ���� ���� ����ִ��� Ȯ���ϴ� �Լ� �ʿ�
            else
            {
                op2 = pop(&s);
                op1 = pop(&s);

                switch (ch) {
                case '+': push(&s, op2 + op1); //pop�Ѱ� ���ؼ� ����ֱ�
                    break; //switch �����
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