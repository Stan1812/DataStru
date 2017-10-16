// 实现复数结构及其基本运算
#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW 0

typedef int status;

struct Plural
{
  int real;
  int imaginary;
  int *pBase;
};

status init_plural(struct Plural *pPlu, int real, int imaginary)
{
  pPlu->pBase = (int *)malloc(2 * sizeof(int));
  if (NULL == pPlu->pBase)
  {
    printf("动态内存分配失败\n");
    exit(ERROR);
  }
  else
  {
    pPlu->real = real;
    pPlu->imaginary = imaginary;
    printf("(%d,%d)动态内存分配成功\n", real, imaginary);
  }
  return OK;
}
status destroy_plural(struct Plural *pPlu)
{
  free(pPlu->pBase);
  pPlu->pBase = NULL;
  printf("销毁成功\n");
}

status add_Plu(struct Plural *pPlu1, struct Plural *pPlu2, struct Plural *pPlu3)
{
  pPlu3->real = pPlu1->real + pPlu2->real;
  pPlu3->imaginary = pPlu1->imaginary + pPlu2->imaginary;
  printf("相加结果:(%d.%d)\n", pPlu3->real, pPlu3->imaginary);
  return OK;
}

status sub_Plu(struct Plural *pPlu1, struct Plural *pPlu2, struct Plural *pPlu3)
{
  pPlu3->real = pPlu1->real - pPlu2->real;
  pPlu3->imaginary = pPlu1->imaginary - pPlu2->imaginary;
  printf("相减结果:(%d.%d)\n", pPlu3->real, pPlu3->imaginary);
  return OK;
}
status mult_Plu(struct Plural *pPlu1, struct Plural *pPlu2, struct Plural *pPlu3)
{
  pPlu3->real = (pPlu1->real * pPlu2->real) - (pPlu1->imaginary * pPlu2->imaginary);
  pPlu3->imaginary = (pPlu1->real * pPlu2->imaginary) + (pPlu1->real * pPlu2->imaginary);
  printf("相乘结果:(%d.%d)\n", pPlu3->real, pPlu3->imaginary);
  return OK;
}
status div_Plu(struct Plural *pPlu1, struct Plural *pPlu2, struct Plural *pPlu3)
{
  // 不会算。。GG
}
int main()
{
  struct Plural oneplu, twoplu, finalplu;
  init_plural(&oneplu, 1, 2);
  init_plural(&twoplu, 9, 10);
  init_plural(&finalplu, 0, 0);
  add_Plu(&oneplu, &twoplu, &finalplu);
  sub_Plu(&oneplu, &twoplu, &finalplu);
  mult_Plu(&oneplu, &twoplu, &finalplu);
};