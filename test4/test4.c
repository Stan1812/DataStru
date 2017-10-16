#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW 0
#define maxinum 10
typedef int Status;
Stack Sta
{
    int data[maxinum];
    int top;
}
void init_stack(SqStack *S)
{
    S->top = -1;
}
Status push_stack(SqStack *S, int value)
{
    if (S->top == maxinum)
    {
        printf("栈满");
    }
    else
    {
        S->data[S->top] = value;
        S->top++ ；
    }
}
Status pop_stack(SqStack *S)
{
    if (S->top == -1)
    {
        printf("数据不合理") ；
    }
    else
    {
        S - top--;
    }
}
Status show_stack(SqStack *S)
{
    printf("----------");
    if (S->top == -1)
    {
        printf("栈为空")
    }
    else
    {
        int i;
        for (i = 0; i < S->top + 1; i++)
        {
            printf("%d\n", S->data[i]);
        }
    }
    printf("-----------");
}

int main()
{
    struct Sta sta1;
    init_stack(&sta1);
    int value;
    printf("输入push值：\n");
    scanf("%d", &value);
    push_stack(&sta1, value);
    show_stack(&sta1);
    pop_stack(&sta1);
}