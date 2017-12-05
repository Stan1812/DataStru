#include <iostream>
using namespace std;

#define MAXSIZE 100

typedef int ElemType;

typedef struct
{
    ElemType data[MAXSIZE];
    int front; /* 头指针 */
    int rear;  /* 尾指针，若队列不空，指向队列尾元素的下一个位置 */
    int count; //元素个数
} SqQueue;

bool InitQueue(SqQueue &Sq)
{
    cout << "初始化..." << endl;
    Sq.front = 0;
    Sq.rear = 0;
    Sq.count = 0;
    return true;
}

bool ClearQueue(SqQueue &Sq)
{
    cout << "Clear Queue ..." << endl;
    Sq.front = 0;
    Sq.rear = 0;
    Sq.count = 0;
    return true;
}

bool QueueEmpty(SqQueue &Sq)
{
    return Sq.count == 0; /* 队列空的标志 */
}

bool QueueFull(SqQueue &Sq)
{
    return Sq.count == MAXSIZE;
}

int QueueLength(SqQueue &Sq)
{
    if (QueueFull(Sq))
        return MAXSIZE;

    /* 队列的当前长度 */
    return (Sq.rear - Sq.front + MAXSIZE) % MAXSIZE;
}
/* 返回头元素 */
bool GetHead(SqQueue &Sq, ElemType *pe)
{
    if (QueueEmpty(Sq))
        return false;
    else
    {
        *pe = Sq.data[Sq.front];
        cout << "获取头" << *pe << endl;
        return true;
    }
}

bool EnQueue(SqQueue &Sq, ElemType Elem)
{
    /* 队列满 */
    if (QueueLength(Sq) == MAXSIZE)
        return false;
    Sq.data[Sq.rear] = Elem;           /* 将元素赋值给队尾 */
    Sq.rear = (Sq.rear + 1) % MAXSIZE; /* rear指针向后移一位置， */
    /* 若到最后则转到数组头部 */
    Sq.count++;
    return true;
}

bool DeQueue(SqQueue &Sq, ElemType *pe)
{
    if (QueueEmpty(Sq))
        return false;
    *pe = Sq.data[Sq.front];             /* 将队头元素赋值给*pe */
    Sq.front = (Sq.front + 1) % MAXSIZE; /* front指针向后移一位置， */
    /* 若到最后则转到数组头部 */
    Sq.count--;
    return true;
}

bool QueueTraverse(SqQueue &Sq)
{
    if (QueueEmpty(Sq))
    {
        cout << "Queue is empty" << endl;
        return false;
    }

    cout << "队列遍历：";
    for (int i = 0; i < Sq.count; i++)
        cout << Sq.data[i + Sq.front] << ' ';
    cout << endl;
    return true;
}

int main(void)
{
    SqQueue Sq;
    InitQueue(Sq);

    //往队列里面传值
    cout << "请输入一个队列以0结束: " << endl;
    int e;
    cin >> e;
    while (e != 0)
    {
        if (EnQueue(Sq, e) != 0)
            scanf("%d", &e);
    }
    QueueTraverse(Sq);

    if (!QueueEmpty(Sq))
        cout << "队列长度: " << QueueLength(Sq) << endl;
    int result;
    //获取头并输出队列值
    GetHead(Sq, &result);

    //删除并输出队列值
    DeQueue(Sq, &result);
    if (!QueueEmpty(Sq))
        cout << "队列长度: " << QueueLength(Sq) << endl;
    QueueTraverse(Sq);
    return 0;
}