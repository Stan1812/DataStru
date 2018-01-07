#include "iostream"
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
#define MAXSIZE 10000
int compCount = 0;  
int shiftCount = 0; 
typedef struct
{
    int key;
} nodeType;

typedef struct
{
    nodeType r[MAXSIZE + 1];
    int length;
} SqList;
// -----------------------工具函数---------------------
// 大小比较函数
bool Smaller(int a,int b){
    return (a<b);
};
bool Larger(int a,int b){
    return (a>b);
};
// 输出格式化函数
int outPut(SqList &L, int m, int n)
{
    // for (int i = 1; i <= L.length; i++)
    //     cout << " " << L.r[i].key;
    // cout << endl;
    cout << "比较次数:";
    cout << m << endl;
    cout << "交换次数:";
    cout << n << endl;
}

// -----------------------功能函数-----------------------
int createSq(SqList &L)
{
    int sortLength;
    cout << "输入待排表元素个数:";
    cin >> sortLength;
    L.length = sortLength;
    srand(time(NULL));
    for (int index = 1; index <= sortLength; index++)
    {
        L.r[index].key = rand() % sortLength;
    }
    return 1;
}
//  冒泡排序
void bubbleSort(SqList &L) 
{
    int i, j, l, k = L.length, m = 0, n = 0;
    for (i = 1; i <= L.length - 1; ++i)
    {
        for (j = 1; j <= k - 1; ++j)
        {
            ++m;
            if (Larger(L.r[j].key, L.r[j + 1].key))
            {
                l = L.r[j].key;
                L.r[j].key = L.r[j + 1].key;
                L.r[j + 1].key = l;
                ++n;
            }
        }
        --k;
    }
    cout << endl
         << "-----冒泡排序结果序列-----" << endl;
    outPut(L, m, n);
}
//直接插入排序
void insertSort(SqList &L) 
{
    int i, j, m = 0, n = 0;
    cout << endl;
    for (i = 2; i <= L.length; ++i)
        if (Smaller(L.r[i].key, L.r[i - 1].key))
        {
            ++m;
            ++n;
            L.r[0] = L.r[i];
            L.r[i] = L.r[i - 1];

            for (j = i - 2; Smaller(L.r[0].key, L.r[j].key); --j)
            {
                ++m;
                L.r[j + 1] = L.r[j]; //记录后移
            }

            L.r[j + 1] = L.r[0]; //插入到正确位置
        }

    cout << "-----直接插入排序结果序列-----" << endl;
    outPut(L, m, n);
}
//简单选择排序
void selectSort(SqList &L) 
{
    int l, i, j, m = 0, n = 0;
    cout << endl;
    for (i = 1; i < L.length; ++i)
    { 
        L.r[0] = L.r[i];
        j = i + 1;
        l = i;
        for (j; j <= L.length; ++j)
        {
            ++m;
            if (Larger(L.r[0].key, L.r[j].key))
            {
                l = j;
                L.r[0] = L.r[j];
            }
        }
        if (l != i)
        {
            ++n;
            L.r[l] = L.r[i];
            L.r[i] = L.r[0];
        }
    }
    cout << "-----简单选择排序结果序列-----" << endl;
    outPut(L, m, n);
}

int Partition(SqList &L, int low, int high)
{
    int pivotkey;
    L.r[0] = L.r[low];
    pivotkey = L.r[low].key; 
    while (low < high)
    { //从表的两端交替向中间扫描
        while (low < high && L.r[high].key >= pivotkey)
        {
            ++compCount;
            --high;
        }
        ++shiftCount;
        L.r[low] = L.r[high]; //比枢轴记录小的移动到低端
        while (low < high && L.r[low].key <= pivotkey)
        {
            ++compCount;
            ++low;
        }
        ++shiftCount;
        L.r[high] = L.r[low]; //比枢轴记录大的移动到高端
    }
    L.r[low] = L.r[0]; //枢轴记录到位
    return low;        //返回枢轴位置
}

void QSort(SqList &L, int low, int high) 
{
    int pivotloc;
    if (low < high)
    {
        pivotloc = Partition(L, low, high); 
        QSort(L, low, pivotloc - 1);
        QSort(L, pivotloc + 1, high);
    }
}
//递归形式的快速排序算法
void QuickSort(SqList &L)
{
    int i;
    QSort(L, 1, L.length);
    cout << endl;
    cout << "-----快速排序结果序列为-----" << endl;
    outPut(L, compCount, shiftCount);
    compCount = 0;
    shiftCount = 0;
}

int main()
{
    int i;
    SqList L, La, Lb, Lc, Ld;
    createSq(L);
    La = Lb = Lc = Ld = L;
    cout << "待排表：" << endl;
    for (i = 1; i <= L.length; i++)
        cout << " " << L.r[i].key;
    bubbleSort(L);
    insertSort(La);
    selectSort(Lb);
    QuickSort(Lc);
    return 0;
};