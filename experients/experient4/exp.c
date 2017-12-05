#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define ERROR -1
typedef int Status;
typedef char ElemType;
typedef struct qNode
{
    ElemType data;
    struct qNode *next;
} QNode, *QueuePtr;
typedef struct
{
    QueuePtr front, rear;
} QueueLink;
// init queue
Status InitQueue(QueueLink *q)
{
    q->front = q->rear = (QueuePtr)malloc(sizeof(QNode));
    if (!q->front)
        return ERROR;
    q->front->next = NULL;
    return TRUE;
}
//入队
Status InsertQueue(QueueLink *q, ElemType e)
{
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
    if (!p)
        return ERROR;
    p->data = e;
    p->next = NULL;
    q->rear->next = p;
    q->rear = p;
    return TRUE;
}
//出队
Status DeleteQueue(QueueLink *q, ElemType *e)
{
    if (q->front == q->rear)
        return FALSE;
    QueuePtr p = q->front->next;
    *e = p->data;
    q->front->next = p->next;
    if (q->rear == p)
        q->rear = q->front;
    free(p);
    return TRUE;
}
// get queue's head item
int GetQueue(QueueLink *q)
{
    QueuePtr p;
    if (q->front == q->rear)
        printf("队列为空，无对头。\n");
    p = q->front->next;
    int e;
    e = p->data;
    printf("队头元素为%d\n", e);
    return e;
}
// output queue
void OutQueue(QueueLink *q)
{
    if (q->rear == q->front)
        printf("队列为空，无元素值。\n");
    QueuePtr p = q->front->next;
    while (p != NULL)
    {
        printf("%d", p->data);
        printf(" ");
        p = p->next;
    }
}
Status DestroyQueue(QueueLink *q)
{
    while (q->front)
    {
        q->rear = q->front->next;
        free(q->front);
        q->front = q->rear;
    }
    return TRUE;
}
int main(int argc, char **argv)
{
    QueueLink q;
    int e;
    char ch;
    //初始化队列
    InitQueue(&q);

    //往队列里面传值
    printf("请输入一个队列以0结束: ");
    scanf("%d", &e);
    while (e != 0)
    {
        if (InsertQueue(&q, e) != 0)
            scanf("%d", &e);
    }
    printf("链队的元素有: \n");
    OutQueue(&q);
    printf("\n");

    //获取头并输出队列值
    GetQueue(&q);
    OutQueue(&q);

    //删除头并输出剩余值
    DeleteQueue(&q, &ch);
    printf("删除头之后的队列为：\n");
    OutQueue(&q);
    printf("\n");

    //销毁队列
    DestroyQueue(&q);
    exit(0);
}
