// 顺序结构
#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW 0
typedef int Status;

struct Arr
{
  int len;
  int count;
  int *pBase;
};
// struct Arr *pArray  指向结构的指针
// ‘　->　’ 类似于JS的‘　.　’
void init_array(struct Arr *pArray, int len)
{
  pArray->pBase = (int *)malloc(sizeof(int) * len);
  if (NULL == pArray->pBase)
  {
    printf("动态分配内存失败\n");
    exit(ERROR);
  }
  else
  {
    pArray->len = len;
    pArray->count = 0;
    printf("%d动态内存分配成功\n", len);
  }
  return;
}
bool isempty(struct Arr *pArray)
{
  if (0 == pArray->count)
  {
    printf("表为空\n");
    return true;
  }
  else
  {
    printf("表不为空\n");
    return false;
  }
}
bool isfull(struct Arr *pArray)
{
  if (pArray->len == pArray->count)
  {
    return true;
  }
  else
  {
    return false;
  }
}
bool push(struct Arr *pArray, int val)
{
  if (isfull(pArray))
  {
    printf("表已经满了！\n");
    return false;
  }
  else
  {
    pArray->pBase[pArray->count] = val;
    pArray->count++;
  }
} 
void get_length(struct Arr *pArray){
  printf("顺序表的长度为：%d",pArray->count);
}
bool delete (struct Arr *pArray)
{
  int index;
  printf("删除脚标:\t");
  scanf("%d", &index);
  if (index < 0 || index > pArray->count)
  {
    printf("该数字不存在");
    return false;
  }
  else
  {
    int i;
    for (i = index; i <= pArray->count; i++)
    {
      pArray->pBase[i - 1] = pArray->pBase[i];
    }
    pArray->count--;
    return true;
  }
}
bool insert(struct Arr *pArray, int index, int val)
{
  if (index < 0 || index > pArray->count)
  {
    printf("插入位置不合理");
    return false;
  }
  else
  {
    if (!isfull(pArray))
    {
      int j = index;
      pArray->pBase[j + 1] = val;
      for (j = index; j <= pArray->count; j++)
      {
        pArray->pBase[j - 1] = pArray->pBase[j];
      }
    }
    pArray->count++;
  }
}
void query_value(struct Arr *pArray)
{
  int query_val;
  printf("请输入要查找的值");
  scanf("%d", &query_val);
  for (int i = 0; i < pArray->count; i++)
  {
    if (pArray->pBase[i] == query_val)
    {
      printf("该值的位置为：%d\n", i + 1);
    }
  }
}
void query_pos(struct Arr *pArray)
{
  int query_pos;
  printf("请输入要查找的序列值\t");
  scanf("%d", &query_pos);
  printf("垓值为：%d\n", pArray->pBase[query_pos - 1]);
}
void show_array(struct Arr *pArray)
{
  if (isempty(pArray))
    printf("表为空！\n");
  else
  {
    int i;
    printf("------------------------------------\n");
    printf("表为\n");
    for (i = 0; i < pArray->count; i++)
    {
      printf("%d \n", pArray->pBase[i]);
    }
    printf("------------------------------------\n");
  }
}

int main()
{
  int max_count, length, index;
  struct Arr arr;
  printf("创建长度：\t");
  scanf("%d", &max_count);
  init_array(&arr, max_count);
  printf("填充数据长度\t");
  scanf("%d", &length);
  for (int a = 1; a <= length; a++)
  {
    int val;
    printf("第%d个元素值为:\t", a);
    scanf("%d", &val);
    push(&arr, val);
  }
  show_array(&arr);
  get_length(&arr);
  delete (&arr);
  show_array(&arr);
  query_value(&arr);
  query_pos(&arr);
  get_length(&arr);
};