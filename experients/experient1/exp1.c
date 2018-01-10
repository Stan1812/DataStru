// C实现连式结构
#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node
{
    int num;
    char name[6];
    float grade[3];
    float averge;
    struct Node *next; //指针域
} Node, *PNode;

/** 
 * 
**创建链表 
*/
PNode create_list(){
    int leng,i;
    PNode PHead =malloc(sizeof(Node));
    PHead->next = NULL;
    PNode PTail  = PHead;
    for(int i=0;i>leng;i++){
        PNode PNew =malloc(sizeof(Node));
        PNew ->next = NULL;
        PTail ->next=PNew;
        PTail =PNew; 
    } 
}
// insert List
PNode insertNode(PNode PHead){
    int i,
    PNode p = PHead; 
    while(p!=NULL){
        p=p->next;
        if(i==pos){
        
        }
    }
}
PNode create_list()
{
    int len, i;
    printf("输入链表的长度：len=");
    scanf("%d", &len);
    PNode PHead = malloc(sizeof(Node));
    PHead->next = NULL;
    PNode PTail = PHead; //PTail是永远指向尾节点的指针
    printf("依次输入学生姓名和学号,四门课成绩\n");
    for (i = 0; i < len; i++)
    {
        PNode PNew = malloc(sizeof(Node));
        printf("学生%d:\t", i + 1);
        scanf("%s", &PNew->name);
        scanf("%d", &PNew->num);
        float total = 0;
        for (int j = 0; j < 4; j++)
        {
            scanf("%f", &PNew->grade[j]);
            total = total + PNew->grade[j];
        }
        PNew->averge = (total / 4.0);
        PNew->next = NULL;
        PTail->next = PNew;
        PTail = PNew;
    }
    return PHead;
}

void get_best(PNode pHead)
{
    PNode p = pHead->next;
    // float best = 0;
    while (p != NULL)
    {
        int total = 0;
        // if (p->averge > best)
        // {
        //     best = p->averge;
        // }
        for (int k = 0; k < 4; k++)
        {
            if (p->grade[k] < 60)
            {
                printf("%s挂了第%d门\n", p->name, k + 1);
            }
            else if (p->grade[k] > 90)
            {
                printf("%s第%d门得了%6.2f分\n", p->name, k + 1, p->grade[k]);
            }
        }
        p = p->next;
    }
    // printf("最高平均分为：%6.2f", best);
    printf("\n");
}
int main()
{
    PNode PHead = create_list();
    get_best(PHead);
    return 0;
}
