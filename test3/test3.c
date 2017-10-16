// C实现连式结构
#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node
{
    int data;           //数据域
    struct Node *next; //指针域
} Node, *PNode;
/** 
**创建链表 
*/
PNode create_list()
{
    int len, i;
    printf("请输入链表的长度：len=\n");
    scanf("%d", &len);
    PNode PHead = malloc(sizeof(Node));
    PHead->next = NULL;
    PNode PTail = PHead; //PTail是永远指向尾节点的指针
    for (i = 0; i < len; i++)
    {
        int val;
        printf("请输入第 %d 个元素的值：", i + 1);
        scanf("%d", &val);
        PNode PNew = malloc(sizeof(Node));
        PNew->data = val;
        PNew->next = NULL;
        PTail->next = PNew;
        PTail = PNew;
    }
    return PHead;
}

// 遍历
void traverse(PNode pHead)
{
    PNode p = pHead->next;
    while (p != NULL)
    {
        printf("%d    ", p->data);
        p = p->next;
    }
    printf("\n");
}

bool isempty(PNode pHead)
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

/** 
*向链表中插入元素 
*/
bool insert_list(PNode pHead, int val, int pos)
{
    //需要找到第pos个位置，并且需要判断这个位置pos是否合法
    //i是p所指节点的位置，所以从一开始，为什么要pos-1呢，因为用的是while 当i=pos-1时跳出循环
    int i = 0;
    PNode p = pHead;
    while (NULL != p && i < pos - 1)
    {
        i++;
        p = p->next;
    }
    //如果插入位置过大，那么P=NULL,
    //如果插入的位置是0或者负数，那么i>pos-1
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

/** 
**在链表中删除节点 
*/

bool delete (PNode PHead, int pos, int *pval)
{
    int i = 0;
    PNode p = PHead;
    //我们要删除p后面的节点，所以p不能指向最后一个节点 p->next!=NULL
    while (p->next != NULL && i < pos - 1)
    {
        p = p->next;
        i++;
    }
    if (i > pos - 1 || p->next == NULL)
    {
        printf("删除位置不合法\n");
        return false;
    }
    PNode temp = p->next;
    p->next = temp->next;
    free(temp);
}
int main()
{

    PNode PHead = create_list();
    if (isempty(PHead))
        printf("链表为空\n");
    printf("链表的长度为：%d\n", get_length(PHead));
    traverse(PHead);
    //insert_list(PHead,55,1);
    // int val;
    // delete (PHead, 6, &val);
    // traverse(PHead);
    return 0;
}
