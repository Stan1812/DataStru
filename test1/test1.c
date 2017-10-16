// 顺序连续结构
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
// ‘　->　’ 感觉类似于JS的‘　.　’
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
    printf("数组为空\n");
    return true;
  }
  else
  {
    printf("数组不为空\n");
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
    printf("数组已经满了！\n");
    return false;
  }
  else
  {
    pArray->pBase[pArray->count] = val;
    pArray->count++;
  }
}
bool pop(struct Arr * pArray){
    pArray->count--;
}
bool delete(struct Arr * pArray,int index){
    if(index<0&&index>pArray->count){
      printf("该数字不存在");
      return false;
    }
    else {
      int i;   
      for(i=index;i<=pArray->count;i++)  
      {
         pArray->pBase[i-1]=pArray->pBase[i];  
      }  
        pArray->count--;  
        return true;
   }
}
void show_array(struct Arr *pArray)
{
  if (isempty(pArray))
    printf("数组为空！\n");
  else
  {
    int i;
    printf("------------------------------------\n");
    printf("数组为\n");
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
  printf("创建长度：");
  scanf("%d",&max_count);
  init_array(&arr, max_count);
  isempty(&arr);
  printf("填充数据长度");
  scanf("%d",&length);
  for ( int a = 0;a<length; a++){
    push(&arr,a);
  }
  show_array(&arr);
  // pop(&arr);
  // show_array(&arr);
  printf("删除脚标:");
  scanf("%d",&index);
  delete(&arr, index);
  show_array(&arr);

};