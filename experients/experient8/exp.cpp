#include<stdio.h>
#include<stdlib.h>
#define MVNum 100
#define Maxint 32767
enum boolean{FALSE,TRUE};
typedef char VertexType;
typedef int Adjmatrix;
typedef struct{
   VertexType vexs[MVNum];//顶点数组，类型假定char型
   Adjmatrix arcs[MVNum][MVNum];//链接矩阵，假定int型
}MGraph;
int D1[MVNum],P1[MVNum];
int D[MVNum][MVNum],P[MVNum][MVNum];

// 创建有向图的存储结构
void CreateMGraph(MGraph *G,int n,int e)
{//采用邻接矩阵表示法构造有向图G，n,e表示图的当前结点数和边数
 int i,j,k,w;
 for(i=1;i<=n;i++)//输入顶点信息
    G->vexs[i]=(char)i;
 for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
      G->arcs[i][j]=Maxint;//初始化邻接矩阵，权值无限大
      printf("输入%d条边的两个顶点及权值: \n",e);
      for(k=1;k<=e;k++){//读入e条边，建立邻接矩阵
       scanf("%d %d %d",&i,&j,&w);
       G->arcs[i][j]=w;
       }
       printf("有向图的存储结构已建立\n");
}
// 迪杰斯特拉算法
void Dijkstra(MGraph *G,int v1,int n)
{
 //用Dijkstra算法求有向图G的v1顶点到其他顶点v的最短路径P[v]及其权D[v]
 //设G是有向图的邻接矩阵，若边<i,j>不存在，则G[i][j]=Maxint
 //S[v]为真，当且仅当v∈s,求得从v1到v的最短路径
  int D2[MVNum],P2[MVNum];
  int v,i,w,min;
  enum boolean S[MVNum];
  for (v=1;v<=n;v++){
   S[v]=FALSE;
   D2[v]=G->arcs[v1][v];
   if(D2[v]<Maxint)
    P2[v]=v1;
   else
    P2[v]=0;
  }
  D2[v1]=0;
  S[v1]=TRUE;
  for(i=2;i<n;i++){
   min=Maxint;
   for(w=1;w<=n;w++)
    if(!S[w]&&D2[w]<min){
    v=w;
    min=D2[w];
    }
    S[v]=TRUE;
    for(w=1;w<=n;w++)
     if(!S[w]&&(D2[v]+G->arcs[v][w]<D2[w])){
      D2[w]=D2[v]+G->arcs[v][w];
      P2[w]=v;
     }
   }
   for(i=1;i<=n;i++){
    printf("路径长度:%d\t",D2[i]);
    printf("路径:%d",i); v=P2[i];
    while(v!=0){
     printf("-%d",v);
     v=P2[v];
    }
    printf("\n");
   }
}
// 佛洛依德算法
void Floyd(MGraph *G,int n)
{
 int i,j,k,v,w;
 for(i=1;i<=n;i++)
  for(j=1;j<=n;j++)
  {
   if(G->arcs[i][j]!=Maxint)
    P[i][j]=j;
   else
    P[i][j]=0;
   D[i][j]=G->arcs[i][j];
  }
  for(k=1;k<=n;k++)
  {
   for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
    { if(D[i][k]+D[k][j]<D[i][j]){
     D[i][j]=D[i][k]+D[k][j];
     P[i][j]=P[i][k];
    }
    }
  }
}

int main(){
 MGraph *G;
 int m,n,e,v,w,k;
 int xz=1;
 G=(MGraph *)malloc(sizeof(MGraph));//创建一个新的结点
 printf("输入图中顶点个数(n)和边数(e): ");
 scanf("%d %d",&n,&e);
 CreateMGraph(G,n,e);//建立有向图的存储结构
 while(xz!=0){                                                                                                                                                                                                                    
  printf("求楼之间的最短路径\n");
  printf("============================================\n");
  printf("1.求一栋楼到所有楼的最短路径\n");
  printf("2.求任意的两栋楼之间的最短路径\n");
  printf("============================================\n");
  printf("请选择功能1或2,选择 0 退出: ");
  scanf("%d",&xz);
   if(xz==2){
   Floyd(G,n);
   printf("输入源点(或称起点)和终点：v,w: ");
   scanf("%d,%d",&v,&w);
   k=P[v][w];
   if(k==0)
     printf("顶点%d 到 %d 无路径!\n",v,w);
   else{
     printf("从顶点%d到%d的最短路径是: %d",v,w,v);
     while(k!=w){
      printf("-%d",k);
      k=P[k][w];
     }
     printf("-%d",w);
     printf("路径长度: %d\n",D[v][w]);
     }
   }
 else
  if(xz==1){
   printf("求单源路径,输入源点 v: ");
   scanf("%d",&v);
   Dijkstra(G,v,n);
  }
  }
    printf("结束求最短路径 \n");
    return 1;
}