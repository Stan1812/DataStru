// 很大程度借鉴了各位前辈的代码==
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef int ElemType;

typedef struct Node
{
    ElemType data;
    struct Node *next;
} Node;
typedef struct Node *LinkList; /* 定义LinkList */

// 1 写一求单链表的结点数目ListLength(L)的算法。
Status getLength(LinkList L)
{
    int i = 0;
    LinkList p;
    p = L->next;
    while (p)
    {
        p = p->next;
        i++;
    }
    return i;
}

// 2 写一算法将单链表中值重复的结点删除，使所得的结果链表中所有结点的值均不相同。

LinkList RemoveDupNode(LinkList L) //删除重复结点的算法
{
    LinkList p, q, r;
    p = L->next;
    while (p) // p用于遍历链表
    {
        q = p;
        while (q->next) // q遍历p后面的结点，并与p数值比较
        {
            if (q->next->data == p->data)
            {
                r = q->next;       // r保存需要删掉的结点
                q->next = r->next; // 需要删掉的结点的前后结点相接
                free(r);
            }
            else
                q = q->next;
        }
        p = p->next;
    }
    return L;
}

// 3 写一算法从一给定的向量A删除值在x到y(x≤y)之间的所有元素(注意：x和y是给定的参数，可以和表中的元素相同，也可以不同)。
LinkList RemoveNodes(LinkList L, int x, int y)
{
    LinkList p, q, r;
    p = L->next;
    int j = 1;
    while (p->next && j <= x)
    {
        p = p->next;
        j++;
    };
    q = p;
    while (j > x && j < y)
    {
        r = q->next;       // r保存需要删掉的结点
        q->next = r->next; // 需要删掉的结点的前后结点相接
        free(r);
    }
}

// 4 设A和B是两个按元素值递增有序的单链表，写一算法将A和B归并为按按元素值递减有序的单链表C，试分析算法的时间复杂度。
Node *merge_lists(Node *a, Node *b)
{
    Node *pa = a->next, *pb = b->next, *t;

    /* 新链表的头结点使用 a 的头结点 */
    a->next = NULL;
    free(b); // b 的头结点是不需要的，可以释放掉

    while (pa != NULL && pb != NULL)
    {
        if (pa->data < pb->data)
        { // 将 pa 插入新链表头部
            t = pa->next;
            pa->next = a->next;
            a->next = pa;
            pa = t;
        }
        else
        { // 将 pb 插入新链表头部
            t = pb->next;
            pb->next = a->next;
            a->next = pb;
            pb = t;
        }
    }

    /* 注：以下两个循环只会执行其中一个 */
    /* 只剩链表 a 的节点 */
    while (pa != NULL)
    {
        t = pa->next;
        pa->next = a->next;
        a->next = pa;
        pa = t;
    }

    /* 只剩链表 b 的节点 */
    while (pb != NULL)
    {
        t = pb->next;
        pb->next = a->next;
        a->next = pb;
        pb = t;
    }
    return a;
}

// 5 写出单链表的就地逆置算法。
// 主要是使用头插法把按原顺序依次拿到的数据插到头成为头结点，实现逆置
void ReverseList(LinkList L)
{
    Node *p, *q;
    p = L->next;    /*p为原链表的当前处理节点*/
    L->next = NULL; /*逆置单链表初始为空*/

    while (p != NULL)
    {                      /*当原链表未处理完*/
        q = p->next;       /*q指针保留原链表当前处理节点的下一个节点*/
        p->next = L->next; /*将当前处理节点p插入到逆置L的表头*/
        L->next = p;
        p = q; /*p指向下一个待插入的节点*/
    }//头还是头@_@
}