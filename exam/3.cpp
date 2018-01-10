
#include <iostream>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#define LS(a,b) ((a)<(b))
#define LL(a,b) ((a)>(b))
#define MAXSIZE 1000
using namespace std;
typedef int KeyType;
int now=1;
typedef struct {
	KeyType key;
}RedType;
typedef struct {
	RedType r[MAXSIZE + 1];
	int length;
}SqList;
int compare = 0;
int change = 0;                             
int Create_Sq_M(SqList &L)
{   int k,temp;
	cout << "输入要排序的个数和值:";
	cin >> k;
	L.length = k;
	for (int x = 1; x <= k; x++)
	{   cin >> temp;
		L.r[x].key = temp;
	}
	return 1;}
void ShellInsert(SqList &L, int dk)
{    int i;
	int j;
	for (i = dk + 1; i <= L.length; ++i)
		if (LS(L.r[i].key, L.r[i - dk].key)) {
			++compare;
			L.r[0] = L.r[i];
			for (j = i - dk; j>0 && LS(L.r[0].key, L.r[j].key); j -= dk) {
				++compare;
				++change;
				L.r[j + dk] = L.r[j];
			}
			L.r[j + dk] = L.r[0];
		}
			cout<<"\n第"<<now<<"次排序"<<endl;
		for(int q=0;q<L.length;++q){
			cout<<L.r[q+1].key<<"   ";
		}
					now++;
}
void ShellSort(SqList &L, int dlta[])
{    int k, j = L.length / 2, t = 0;
	while (j >= 0) {
		++t;
		j -= 2;
	}
	j = L.length / 2;
	for (k = 0; k<t; ++k)
	{    if (j == 0)
			j = 1;
		dlta[k] = j;
		j -= 2;
	}
	for (k = 0; k<t; ++k)
		ShellInsert(L, dlta[k]);
}

int main() {
	int dlta[MAXSIZE];
	SqList L,d;
		Create_Sq_M(L);
		 d=L;
		ShellSort(d, dlta);
		cin.get();
		cin.get();
		return 0;
}

