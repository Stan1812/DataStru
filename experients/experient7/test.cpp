#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h> //输入表达式，利用二叉树求值。
using namespace std;
static int n = 1;
static int d = 0;
static int leaves = 1; //叶子
static int co = 0;     //字符串计数
typedef struct BiTNode
{
    float data;
    struct BiTNode *lchild, *rchild;
    BiTNode()
    { //初始化
        lchild = NULL;
        rchild = NULL;
    }
} BiTNode, *BiTree;
BiTree T;
void init(BiTree &T)
{ //初始化，给 T 分配空间。
    T = (BiTree)malloc(sizeof(BiTree));
}

int CreateBiTree(BiTree &T, char *s)
{ //构造二叉树
    char ch = 0;
    int isn = 0, isx = 0, isok = 0; //isn 标记是数字， isx 标记是小数,isok 标记是否可以给 data 赋值。
                                    //isok==0,不可赋值。isok==1，数字赋值，isok==2，符号赋值。
    float num = 0;

    while (isok == 0 && s[co] != '\0')
    {
        ch = s[co];
        ++co;

        if (ch >= '0' && ch <= '9' && isx == 0) //如果 ch 是数字，且无标记 2
        {
            isn = 1; //标记 1
            num = num * 10 + ch - 48;
        }
        else if (ch == '.') //如果是小数点
        {
            isx = 1;
        }
        else if (ch >= '0' && ch <= '9' && isx == 1) //如果 ch 是数字，有无标记 2
        {
            num = num + (ch - 48) * 0.1; //只能有一位小数
            isok = 1;                    //因为只能一位小数，所以直接让它可以赋值吧。
            //这两行代码使得程序只能进行小数点后一位的运算，增加精度的话改这里。
        }
        else //如果 ch 是符号
        {
            isok = 2;
        }

    } //while

    if (isok == 1)
    {
        if (!(T = (BiTNode *)malloc(sizeof(BiTree))))
            exit(1);
        T->data = num; //isok=0; //isn=0; //isx=0;
        T->lchild = NULL;
        T->rchild = NULL;
    }
    else if (isok == 2)
    {
        if (!(T = (BiTNode *)malloc(sizeof(BiTree))))
            exit(1);
        T->data = ch;

        //isok=0; //isn=0; //isx=0;
        CreateBiTree(T->lchild, s);
        CreateBiTree(T->rchild, s);
    }
    return 0;
}

void BiTreeleaves(BiTree &T)
{
    if (T->lchild != NULL)
    {
        leaves++;
        BiTreeleaves(T->lchild);
    }
    if (T->rchild != NULL)
    {
        leaves++;
        BiTreeleaves(T->rchild);
    }
}

int Pre(BiTree &T)
{
    if (T)
    {
        cout << T->data << " ";
        Pre(T->lchild);
        Pre(T->rchild);
    }
    return 0;
}
void print_PRE(BiTree &T)
{
    //先序遍历
    if (T != NULL)
    {
        if (T->data >= 40)
        {
            cout << (char)T->data;
            cout << ",";
        }

        else
        {
            cout << T->data;
            cout << ",";
        }
    }
    if (T->lchild != NULL)
        print_PRE(T->lchild);
    if (T->rchild != NULL)
        print_PRE(T->rchild);
}
void print_IN(BiTree &T)
{
    //中序遍历
    if (T->lchild != NULL)
    {
        print_IN(T->lchild);
    }
    if (T != NULL)
    {
        if (T->data >= 40)
        {
            cout << (char)T->data;
            cout << ",";
        }
        else
        {
            cout << T->data;
            cout << ",";
        }
    }
    if (T->rchild != NULL)
        print_IN(T->rchild);
}
void print_POST(BiTree &T)
{ //后序遍历
    if (T->lchild != NULL)
    {
        print_POST(T->lchild);
    }
    if (T->rchild != NULL)
        print_POST(T->rchild);
    if (T != NULL)
    {
        if (T->data >= 40)
        {
            cout << (char)T->data;

            cout << ",";
        }
        else
        {
            cout << T->data;
            cout << ",";
        }
    }
}
float Operate(float a, char theta, float b)
{ //数值计算
    float z;
    switch (theta)
    {
    case '+':
        z = a + b;
        break;
    case '-':
        z = a - b;
        break;
    case '*':
        z = a * b;
        break;
    case '/':
        z = a / b;
        break;
    }
    return z;
}
int BiTreeDepth(BiTree &T)
{
    //求树的深度
    int t; //保存 n 的值，使之不会再半途变回 1.
    if (T->lchild != NULL && T->rchild != NULL)
    {
        n++;
        if (n > d)
            d = n;
        t = n;
        BiTreeDepth(T->lchild);
        n = t;
        BiTreeDepth(T->rchild);
    }
    else if (T->lchild != NULL && T->rchild == NULL)
    {
        n++;
        if (n > d)
            d = n;
        BiTreeDepth(T->lchild);
    }
    else if (T->lchild == NULL && T->rchild != NULL)
    {
        n++;
        if (n > d)
            d = n;

        //被减数先进栈，故交换所取值

        BiTreeDepth(T->rchild);
    }
    n = 1;
    return 0;
}
void cal(BiTree &T)
{
    float a, theta, b;
    if (T->lchild != NULL && T->rchild != NULL && (!((T->lchild->data + 48 >= '0') && (T->lchild->data + 48 <= '9')) || !((T->rchild->data + 48 >= '0') && (T->rchild->data + 48 <= '9'))))
    {
        cal(T->lchild);
        cal(T->rchild);
    }
    if (T->lchild != NULL && T->rchild != NULL && (((T->lchild->data + 48 >= '0') && (T->lchild->data + 48 <= '9')) || ((T->rchild->data + 48 >= '0') && (T->rchild->data + 48 <= '9'))))
    {
        a = T->lchild->data;
        theta = T->data;
        b = T->rchild->data;
        T->data = Operate(a, theta, b); //所有计算都在这里完成 }
        if ((T->lchild == NULL && T->rchild != NULL) || ((T->lchild != NULL && T->rchild == NULL)))
            cout << "输入的表达式错误!";
    }
}

//---------------------------------------------------------------------------------------------------------------------------//
typedef struct
{
    char *base;
    char *top;
    int stacksize;
} SqStack;

//SqStack OPTR; //SqStack RESULT;
void init(SqStack &S)
{ //初始化一个 stack
    S.base = (char *)malloc(100 * (sizeof(char)));
    if (!S.base)
        exit(-1);
    S.top = S.base;
    S.stacksize = 100;
}
char GetTop(SqStack &S)
{ //GetTop
    if (S.base != S.top)
        return *(S.top - 1);
    return 10;
}
void pop(SqStack &S, char &e)
{ //pop
    e = *--S.top;
}
void push(SqStack &S, char e)
{ //push

    if (S.top - S.base >= S.stacksize)
    {
        S.base = (char *)realloc(S.base, (S.stacksize + 10) * sizeof(char));
        if (!S.base)
            exit(-1);
        S.top = S.base + S.stacksize; //重新定位 S.top，因为 S.base 重新分配了。
        S.stacksize += 10;
    }
    *S.top++ = e;
}
int Transfor(char c)
{ //返回字符 c 对应优先关系表中的行列号
    int k;

    switch (c)
    {
    case '+':
        k = 0;
        break;
    case '-':
        k = 1;
        break;
    case '*':
        k = 2;
        break;
    case '/':
        k = 3;
        break;
    case '(':
        k = 4;
        break;
    case ')':
        k = 5;
        break;
    case '#':
        k = 6;
        break;
    }
    return k;
}
char Precede(char c1, char c2)
{ //判断 c1 与 c2 的位序关系,优先的返回'=',非 '<',其他还有 '='和' '
    int i, j;
    char a[7][7] = {{'>', '>', '<', '<', '<', '>', '>'}, {'>', '>', '<', '<', '<', '>', '>'}, {'>', '>', '>', '>', '<', '>', '>'}, {'>', '>', '>', '>', '<', '>', '>'}, {'<', '<', '<', '<', '<', '=', '\0'}, {'>', '>', '>', '>', '\0', '>', '>'}, {'<', '<', '<', '<', '<', '\0', '='}};
    i = Transfor(c1);
    j = Transfor(c2);
    return (a[i][j]);
}

char *Transition(char *s)
{
    SqStack OPTR;
    SqStack RESULT;
    init(OPTR);                                     //初始化 OPTR
    push(OPTR, '#');                                //栈底
    init(RESULT);                                   //初始化 RESULT
    push(RESULT, '#');                              //栈底
    int i = 0;                                      //计数
    int of = 0;                                     //记录偏移量
    char temp;                                      //临时变量
    char *str = (char *)malloc(40 * sizeof(char));  //标准化s
    char *news = (char *)malloc(30 * sizeof(char)); //保存结果
    int isx = 0;                                    //标记，是否有小数点。

    for (; s[i] != '\0'; i++)
    {
        if (s[i] == '.')
            isx = 1; //如果遇到小数点，则标记。
        if (isx == 1)
        {
            str[i + of] = s[i];
            if (s[i + 1] == '+' || s[i + 1] == '-' || s[i + 1] == '*' || s[i + 1] == '/' || s[i + 1] == '(' || s[i + 1] == ')' || s[i + 1] == '#' || s[i + 1] == '\0')
                isx = 0;
        }
        else if ((s[i] >= '0' && s[i] <= '9') && isx == 0 && (s[i + 1] == '+' || s[i + 1] == '-' || s[i + 1] == '*' || s[i + 1] == '/' || s[i + 1] == '(' || s[i + 1] == ')' || s[i + 1] == '#' || s[i + 1] == '\0'))
        {
            str[i + of] = s[i];
            str[i + of + 1] = '.';
            str[i + of + 2] = '0';
            of += 2;
            isx = 0;
        }
        else
        {
            str[i + of] = s[i];
        }
    }
    str[i + of + 1] = '\0'; //给 str 添加一个结尾。

    for (i = 0; str[i] != '\0'; i++)
    { //计算表达式长度 ;
    }
    i--;
    for (; i >= 0; i--)
    {                      //从右往左遍历表达式
        if (str[i] == ' ') //如果是空格，则跳过。
            continue;
        else if (str[i] >= '0' && str[i] <= '9') //如果是操作数，则直接存入 RESULT
            push(RESULT, str[i]);
        else if (str[i] == '.')

            push(RESULT, str[i]);
        else if (str[i] == ')') //如果是'） ' ，则直接存入 RESULT
            push(OPTR, str[i]);
        else if (str[i] == '(')
        { //如果是 ' （' ， 则循环弹出 OPTR 栈中的运算符， 并存入 RESULT 中，直到取出'） ' ，舍弃'） ' 。
            while (1)
            {
                pop(OPTR, temp);
                if (temp != ')')
                    push(RESULT, temp);
                else
                    break;
            }
        }
        else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '(' || str[i] == ')' || str[i] == '#')
        {                            //如果是运算符
            if (GetTop(OPTR) == '#') //如果 OPTR 栈空,则存入 OPTR 栈
                push(OPTR, str[i]);
            else if (Precede(str[i], GetTop(OPTR)) == '>' || Precede(str[i], GetTop(OPTR)) == '=')
            {
                //如果该运算符优先级大于或等于栈顶，则存入 OPTR
                push(OPTR, str[i]);
            }
            else
            { //否则，循环弹出 OPTR 栈中运算符，并存入 RESULT，直至遇到优先级 相等或小于的运算符或栈空，然后将当前运算符存入 OPTR
                while (1)
                {
                    if (Precede(str[i], GetTop(OPTR)) == '=' || Precede(str[i], GetTop(OPTR)) == '>' || GetTop(OPTR) == '#')
                        break;
                    pop(OPTR, temp);
                    push(RESULT, temp);
                }
                push(OPTR, str[i]);
            } //else
        }
    } //for
    while (1)
    {
        if (GetTop(OPTR) != '#')
        { // 若表达式读取完后 OPTR 还有运算符，则弹出，存入 RESULT，直至栈空。
            pop(OPTR, temp);
            push(RESULT, temp);
        }
        else
            break;
    }
    for (i = 0; GetTop(RESULT) != '#'; i++)
    { //RESULT 中元素依次出栈，写入字符串。
        pop(RESULT, news[i]);
    }
    news[i] = '\0';
    return news;
} //

int main()
{

    int n = 0;
    char *s = (char *)malloc(30 * sizeof(char));
    cout << "请输入表达式！ ：" << endl;
    cin >> s;
    getchar();
    s = Transition(s);
    init(T);
    CreateBiTree(T, s);
    cout << "二叉树创建成功!" << endl;
    cout << "前序遍历：";
    print_PRE(T);
    cout << endl;
    cout << "中序遍历：";
    print_IN(T);
    cout << endl;
    cout << "后续遍历：";
    print_POST(T);
    cout << endl;
    BiTreeDepth(T);
    cout << "深度 = " << d << endl;
    BiTreeleaves(T);
    cout << "树叶 = " << (leaves + 1) / 2 << endl;
    cal(T);
    cout << "结果 = " << T->data << endl;
    return 0;
}