#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
typedef struct Node
{
    int data;
    struct Node *next;
} Node, *PNode;

PNode create_list()
{
    int len, i;
    printf("请输入初始化链表的长度：len=\t");
    scanf("%d", &len);
    PNode PHead = malloc(sizeof(Node));
    PHead->next = NULL;
    PNode PTail = PHead;
    printf("请依次输入元素的值：", i + 1);
    for (i = 0; i < len; i++)
    {
        int val;
        scanf("%d", &val);
        PNode PNew = malloc(sizeof(Node));
        PNew->data = val;
        PNew->next = NULL;
        PTail->next = PNew;
        PTail = PNew;
    }
    return PHead;
}

//从头遍历并输出该值，和下面的根据查询值类似
void traverse(PNode pHead)
{
    printf("----------------\n");
    PNode p = pHead->next;
    while (p != NULL)
    {
        printf("%d    ", p->data);
        p = p->next;
    }
    printf("\n------------------\n");
}

bool judge_if_empty(PNode pHead)
{
    if (NULL == pHead->next)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int get_length(PNode pHead)
{
    int num = 0;
    PNode p = pHead->next;
    while (p != NULL)
    {
        num++;
        p = p->next;
    }
    return num;
}

int query_pos(PNode pHead)
{
    int index;
    printf("请输入要查询的位置：\t");
    scanf("%d", &index);
    PNode p = pHead->next;
    if (get_length(pHead) < index)
    {
        printf("要查询的位置不存在");
    }
    else
    {
        for (int i = 1; i < index; i++)
        {
            p = p->next;
        }
        printf("该位置的值是：%d\n", p->data);
    }
    return p->data;
}
int query_midpos(PNode pHead)
{
    int ListLength = get_length(pHead);
    int midPos;
    if(ListLength%2==0){
        midPos = ListLength/2;
    }else{
        midPos = (ListLength+1)/2;
    }
    printf("%d",midPos);
    PNode p = pHead->next;
    int i=1;
    while(i!=midPos){
        ++i;
        p=p->next;
    }
    printf("中间值：%d\n", p->data);
}
bool insert_node(PNode pHead, int val, int pos)
{
    int i = 0;
    PNode p = pHead;
    while (NULL != p && i < pos - 1)
    {
        i++;
        p = p->next;
    }
    if (i > pos - 1 || NULL == p)
    {
        printf("插入位置不合法\n");
        return false;
    }
    PNode PNew = malloc(sizeof(PNode));
    PNew->data = val;
    PNode temp = p->next;
    p->next = PNew;
    PNew->next = temp;
    return true;
}
int main()
{
    PNode PHead = create_list();
    if (judge_if_empty(PHead))
        printf("链表为空\n");
    printf("链表的长度为：%d\n", get_length(PHead));
    traverse(PHead);
    query_pos(PHead);
    query_midpos(PHead);
    return 0;
}
