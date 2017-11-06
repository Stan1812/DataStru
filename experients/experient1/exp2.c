#include <stdio.h>
typedef struct Student
{
    int num;
    char name[20];
    float score[3];
    float aver;
} Student;
int main()
{
    void input(Student stu[]);
    Student max(Student stu[]);
    void print(Student stu);
    void query_not_pass(Student stu[]);
    Student stu[4], *p = stu;
    input(p);
    print(max(p));
    query_not_pass(p);
    return 0;
}
void input(Student stu[])
{
    int i, k;
    printf("请输入学生姓名和学号,四门课成绩\n");
    for (i = 0; i < 4; i++)
    {
        printf("student%d:", i);
        scanf("%s", stu[i].name);
        scanf("%d", &stu[i].num);
        for (k = 0; k < 4; k++)
        {
            scanf("%f", &stu[i].score[k]);
        }
        stu[i].aver = (stu[i].score[0] + stu[i].score[1] + stu[i].score[2] + stu[i].score[3]) / 4.0;
    }
}
Student max(Student stu[])
{
    int i, m;
    for (i = 0; i < 5; i++)
    {
        if (stu[i].aver > stu[m].aver)
        {
            m = i;
        }
    }
    printf("\n成绩最高的学生是:%s\n", stu[m].name);
    printf("平均成绩:%6.2f\n", stu[m].aver);
    return stu[m];
}
void query_not_pass(Student stu[])
{
    int j, k;
    for (j = 0; j < 4; j++)
    {
        for (k = 0; k < 4; k++)
        {
            if (stu[j].score[k] < 60)
            {
                printf("%s挂了第%d门\n", stu[j].name,k);
            }
            else if (stu[j].score[k] > 90)
            {
                printf("%s可能是个学霸，第%d门他得了%6.2f分\n",stu[j].name,k,stu[j].score[k]);
            }
        }
    }
}
void print(Student stu)
{
    printf("学号:%d\n姓名:%s\n四门课成绩:%5.1f%5.1f%5.1f%5.1f\n", stu.num, stu.name, stu.score[0], stu.score[1], stu.score[2], stu.score[3]);
}