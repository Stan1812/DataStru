#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
const int maxExprLen = 100;
const int stackInitSize = 100;
//定义二叉树的存储结构
typedef struct BiTNode
{
    int data;
    BiTNode *lChild, *rChild;
} * BiTree;

// 定义一个栈类型
// 当多种类型，多个对象，多个事物只取其一时
// 可以使用联合体来发挥其长处。
union sType {
    char optr;
    BiTree bt;
};
//栈结构
struct stack
{
    sType *elem;
    int top;
    int ssize;
};
//全局定义
stack optrS, btnS; //操作数栈和树的节点
//符号表 
// 枚举类型enum,默认未显式赋值的值为上一个值+1
enum
{
    PLUS = 0,
    MINUS,
    MUL,
    DIV
};
//初始化栈
void initStack(stack &s, int maxsize)
{
    s.elem = new sType[maxsize];
    s.top = -1;
    s.ssize = maxsize;
}
//获得栈顶元素
int getTop(stack s, sType &e)
{
    if (s.top == -1)
        return 0;
    e = s.elem[s.top];
    return 1;
}
//出栈
int pop(stack &s, sType &e)
{
    if (s.top == -1)
        return 0;
    e = s.elem[s.top--];
    return 1;
}
//压栈
void push(stack &s, sType e)
{
    s.elem[++s.top] = e;
}

//获得表达式
void getExpr(char *exp)
{
    char ch = 0;
    int n = 1, i = 0;
    do
    {
        cin >> ch;
        if (n == 1 && (ch == '-' || ch == '+'))
            exp[i++] = '0';
        else
            n = 0;
        exp[i++] = ch;
        if (ch == '(')
            n = 1;
    } while (ch != '=');
    exp[i] = '\0';
}
//判断输入字符是否为操作数
int in(char ch, char *opt)
{
    char *p = opt;
    while (*p && ch != *p)
        ++p;
    if (!*p)
        return 0;
    return 1;
}
//将字符转换为对应的操作数
void changeOpnd(char *p, int pos, int &n, double *opd)
{
    char data[20];
    char *q = data;
    n = 0;
    while ((*p <= '9' && *p >= '0') || (*p == '.'))
    {
        *q++ = *p++;
        n++;
    }
    *q = '\0';
    opd[pos] = (double)atof(data);
}
//将字符转换为对应的运算符
int changeOptr(char ch)
{
    int n;
    if (ch == '+')
        n = PLUS;
    else if (ch == '-')
        n = MINUS;
    else if (ch == '*')
        n = MUL;
    else if (ch == '/')
        n = DIV;
    return n;
}
//创建叶节点，节点的数据是操作数在数组中的位置
void createNode(BiTree &t, int pos, stack &ptr)
{
    sType e;
    // struct和class的比较:
    // 默认继承权限。如果不明确指定，来自class的继承按照private继承处理，来自struct的继承按照public继承处理；
    // 成员的默认访问权限。class的成员默认是private权限，struct默认是public权限。
    // 除了这两点，class和struct基本就是一个东西。语法上没有任何其它区别。
    // 所以为了简洁使用了C++中的new,没有使用malloc
    t = new BiTNode;
    t->data = pos;
    t->lChild = t->rChild = NULL;
    e.bt = t;
    push(ptr, e);
}
//创建子树
void createSubtree(BiTree &t, char ch, stack &ptr)
{
    sType a, c, e;
    BiTree m = new BiTNode;
    m->data = changeOptr(ch);
    if (pop(ptr, a))
        m->rChild = a.bt;
    else
        m->rChild = NULL;
    if (pop(ptr, c))
        m->lChild = c.bt;
    else
        m->lChild = NULL;
    e.bt = m;
    t = m;
    push(ptr, e);
}
//判断运算符的优先级
int precede(char a, char b)
{
    switch (a)
    {
    case '=':
    case '(':
        return 0;
    case '*':
    case '/':
    case '+':
    case '-':
        if (!(b != '*' && b != '/'))
            return 0;
        return 1;
    default:
        return 1;
    }
}
//创建二叉树表达式
void createBiTree(BiTree &t, char *exp, double *opd, char *opt)
{
    sType e, c;
    char *p, ch;
    int n = 0, pos = 0;
    e.optr = '=';
    push(optrS, e);
    p = exp;
    ch = *p;
    getTop(optrS, e);
    while (!(e.optr == '=' && ch == '='))
    {
        if (!in(ch, opt))
        {
            changeOpnd(p, pos, n, opd);
            p += (n - 1);
            createNode(t, pos++, btnS);
        }
        else
        {
            switch (ch)
            {
            case '(':
                e.optr = ch;
                push(optrS, e);
                break;
            case ')': //创建子树
                pop(optrS, c);
                while (c.optr != '(')
                {
                    createSubtree(t, c.optr, btnS);
                    pop(optrS, c);
                }
                break;
            default:
                while (getTop(optrS, c) && precede(c.optr, ch))
                { //如果栈顶的运算符具有更高的优先级
                    createSubtree(t, c.optr, btnS);
                    pop(optrS, c);
                }
                if (ch != '=')
                {
                    e.optr = ch;
                    push(optrS, e);
                }
                break;
            }
        }
        if (ch != '=')
        {
            p++;
            ch = *p;
        }
        getTop(optrS, e);
    }
    e.bt = t;
    pop(btnS, e);
}
//后序遍历，递归运算
double evaluateExpr(BiTree t, double *opd)
{
    double lv, rv, v;
    if (!t)
        return 0;
    if (!t->lChild && !t->rChild)
        return opd[t->data];
    lv = evaluateExpr(t->lChild, opd);
    rv = evaluateExpr(t->rChild, opd);
    switch (t->data)
    {
    case PLUS:
        v = lv + rv;
        break;
    case MINUS:
        v = lv - rv;
        break;
    case MUL:
        v = lv * rv;
        break;
    case DIV:
        if (rv == 0)
            cerr << "Can't divide 0\n";
        v = lv / rv;
        break;
    }
    return v;
}
//----------------------------------
int main(int argc, char **argv)
{
    char expr[maxExprLen];
    BiTree t;
    initStack(optrS, stackInitSize);
    initStack(btnS, stackInitSize);
    double opnd[maxExprLen / 2];
    //  char *op; = "/+-*=()";
    //  在使用较高版本的g++编译时,此处报错: ISO C++ forbids converting a string constant to ‘char*’ [-Wwrite-strings]
    //  op="/+-*=()";
    //     ^~~~~~~~~
    // 解决:使用强制转换
    char *op;
    op = (char *)"/+-*=()";
    cout << "*********** 计算器************" << endl
         << endl;
    cout << "请输入运算表达式为（以= 结束）:" << endl
         << endl;
    getExpr(expr);
    createBiTree(t, expr, opnd, op);
    cout << endl;
    cout << "计算结果为: " << evaluateExpr(t, opnd) << endl
         << endl;
    cout << "*****************************" << endl;
    getchar();
    getchar();
}