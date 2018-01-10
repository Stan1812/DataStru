#include <iostream>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#define LS(a, b) ((a) < (b))
#define LL(a, b) ((a) > (b))
#define MAXSIZE 10000
using namespace std;
typedef int KeyType;
typedef struct
{ //定义线性表
    KeyType key;
} RedType;
typedef struct
{
    RedType r[MAXSIZE + 1];
    int length;
} SqList;
int compare = 0; //比较次数
int change = 0;  //交换次数
int seed = 0;
//因此采用随机种子 ++保证每一次的随机数种子不同

int Create_Sq(SqList &L, int k) //构建随机数表
{
    L.length = k;
    srand(seed++);
    for (int x = 1; x <= k; x++)
    {
        L.r[x].key = rand() % 1000; //随机域为0 - 999
    }

    return 1;
}
void CopyData(SqList &L, SqList &L1)
{ //顺序表拷贝，将排序后的表恢复乱序
    int i;
    L1.length = L.length;
    for (i = 1; i <= L.length; i++)
    {
        L1.r[i].key = L.r[i].key;
    }
}
void BubbleSort(SqList &L) //冒泡排序法
{
    int i, j, l, k = L.length, m = 0, n = 0;
    for (i = 1; i < k - 1; i++)
    {
        for (j = 1; j < k - 1; j++)
        {
            ++m;
            if (LL(L.r[j].key, L.r[j + 1].key))
            {
                l = L.r[j].key;
                L.r[j].key = L.r[j + 1].key;
                L.r[j + 1].key = l;
                n++;
            }
        }
        --k;
    }
    cout << "进行冒泡排序后的序列如下所示：" << endl;
    for (i = 1; i < L.length; i++)
        cout << "  " << L.r[i].key;
    cout << endl;
    cout << "冒泡排序的比较次数为：" << m << endl;
    cout << "冒泡排序的交换次数为：" << n << endl;
}
void InsertSort(SqList &L) //直接插入排序
{
    int i, j, m, n;
    m = 0;
    n = 0;
    for (i = 2; i <= L.length - 1; i++)
        if (LS(L.r[i].key, L.r[i - 1].key))
        {
            ++m;
            ++n;
            L.r[0] = L.r[i];
            L.r[i] = L.r[i - 1];
            for (j = i - 2; LS(L.r[0].key, L.r[j].key); --j)
            {
                ++m;
                L.r[j + 1] = L.r[j];
            }
            L.r[j + 1] = L.r[0];
        }
    // cout << "直接插入排序后的序列如下所示：" << endl;
    // for (i = 1; i <= L.length; i++)
    //     cout << "  " << L.r[i].key ;
    cout << "直接插入排序的比较次数为：" << m << endl;
    cout << "直接插入排序的交换次数为：" << n << endl;
}
void SelectSort(SqList &L) //简单选择排序
{
    int l, i, j, m = 0, n = 0;
    for (i = 1; i < L.length; ++i)
    {
        L.r[0] = L.r[i];
        j = i + 1;
        l = i;
        for (j; j <= L.length; ++j)
        {
            ++m;
            if (LL(L.r[0].key, L.r[j].key))
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
    // cout << "简单选择排序后的序列如下所示：" << endl;
    // for (i = 1; i <= L.length; i++)
    //     cout << " " << L.r[i].key;
    // cout << endl;
    cout << "简单选择排序的比较次数为:"<< m << endl;
    cout << "简单选择排序的交换次数为:" <<n << endl;
}
int Partition(SqList &L, int low, int high)
{
    int pivotkey;
    L.r[0] = L.r[low];
    pivotkey = L.r[low].key;
    while (low < high)
    {
        while (low < high && L.r[high].key >= pivotkey)
        {
            ++compare;
            --high;
        }
        ++change;
        L.r[low] = L.r[high];
        while (low < high && L.r[low].key <= pivotkey)
        {
            ++compare;
            ++low;
        }
        ++change;
        L.r[high] = L.r[low];
    }
    L.r[low] = L.r[0];
    return low;
}
void QSort(SqList &L, int low, int high) //递归形式的快速排序算法
{
    int pivotloc;
    if (low < high)
    {
        pivotloc = Partition(L, low, high);
        QSort(L, low, pivotloc - 1);
        QSort(L, pivotloc + 1, high);
    }
}
void QuickSort(SqList &L) //快速排序
{
    int i;
    QSort(L, 1, L.length);
    // cout << "快速排序后的序列为" << endl;
    // for (i = 1; i <= L.length; i++)
    //     cout << " " << L.r[i].key;
    // cout << endl;
    cout << "快速排序的比较次数为:" << compare << endl;
    cout << "快速排序的交换次数为:" << change << endl;
}
void choose()
{
    int cmd, i, j, m;
    int group = 18, k = 400;
    cout << "*****************Menu*****************" << endl;
    cout << " 1.默认设置进行算法测试" << endl;
    cout << " 2.设置表的存储大小 100 ~ 1000 (默认大小400)" << endl;
    cout << " 3.设置显示的组数 8 ~ 18 (默认组数18)" << endl;
    cout << " 4.退出" << endl;
    cout << "*****************Menu*****************" << endl;
    cout << "请输入你的选择：";
    cin >> cmd;
    switch (cmd)
    {
    case 1:
    {
        SqList L[group];
        SqList L1[group];
        for (j = 0; j < group; j++)
        {
            Create_Sq(L[j], k);
            CopyData(L[j], L1[j]); //在L1中保存乱序的数据，便于恢复
            cout << endl;
            cout << "第" << j + 1 << "组测试结果：";
            for (m = 1; m <= 4; m++)
            {
                CopyData(L1[j], L[j]); //恢复L中的数据为随机打乱的数据
                switch (m)
                {
                case 1:
                    BubbleSort(L[j]);
                    break;
                case 2:
                    InsertSort(L[j]);
                    break;
                case 3:
                    SelectSort(L[j]);
                    break;
                case 4:
                    QuickSort(L[j]);
                    break;
                }
            }
        }
    }
    break;
    case 2:
    {
        cout << "请输入表的存储大小：";
        cin >> k;
        if (k < 10)
            k = 10;
        if (k > 1000)
            k = 1000;
        cout << "此时表长为：" << k << endl;
    }break;
    case 3:
    {
        cout << "请输入要显示的组数：";
        cin >> group;
        if (group < 8)
            group = 8;
        if (group > 
            group = 18;
        cout << "此时组数为：" << group << endl;
        SqList L[group];
        SqList L1[group];
        for (j = 0; j < group; j++)
        {
            Create_Sq(L[j], k);
            CopyData(L[j], L1[j]); //在L1中保存乱序的数据，便于恢复
            cout << endl;
            cout << "第" << j + 1 << "组测试结果：";
            for (m = 1; m <= 4; m++)
            {
                CopyData(L1[j], L[j]); //恢复L中的数据为随机打乱的数据
                switch (m)
                {
                case 1:
                    BubbleSort(L[j]);
                    break;
                case 2:
                    InsertSort(L[j]);
                    break;
                case 3:
                    SelectSort(L[j]);
                    break;
                case 4:
                    QuickSort(L[j]);
                    break;
                }
            }
        }
    }
    break;
    case 4:
        break;
    }
    cout << endl;
}
int  main()
{
    int i, j;
    int dlta[MAXSIZE];
    choose();
    return 0;
}