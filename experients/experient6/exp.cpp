#include <iostream> 
#include <iomanip> 
using namespace std; 
const int MAXSIZE=100;
// 预定义最大行数为10  
const int MAXROW=10; 

typedef struct { 
	int i,j; 
	int e; 
}Triple; 

typedef struct { 
	Triple data[MAXSIZE+1]; 
	int mu,nu,tu; 
}TSMatrix; 

typedef struct { 
	Triple data[MAXSIZE+2]; 
	int rpos[MAXROW+1]; 
	int mu,nu,tu; 
}RLSMatrix; 

template <class P> 
bool InPutMatrix(P & T,int y){ 
	cout<<"输入矩阵的行，列和非零元素个数:"<<endl; 
	cin>>T.mu>>T.nu>>T.tu; 
	cout<<"请输出非零元素的位置和值:"<<endl; 
	int k=1; 
	for(;k<=T.tu;k++) 
		cin>>T.data[k].i>>T.data[k].j>>T.data[k].e; 
	return true; 
} 
// C++模板语法
template <class P> 
	bool OutPutMatrix(P T){ 
	int m,n,k=1; 
	for(m=0;m<T.mu;m++)
	{ 
		for(n=0;n<T.nu;n++)
		{ 
			if((T.data[k].i-1)==m&&(T.data[k].j-1)==n)
			{ 
				cout.width(4); 
				cout<<T.data[k++].e;} 
			else{ 
				cout.width(4); cout<<"0"; } 
			} 
			cout<<endl; 
			} 
		return true; 
	} 
// 转置矩阵
bool TransMatrix( ){ 
	TSMatrix M,T; //定义预转置的矩阵 
	InPutMatrix(M, 0); //输入矩阵 
	int num[MAXROW+1]; 
	int cpot[MAXROW+1]; // 构建辅助数组 
	int q,p,t; 
	T.tu=M.tu; T.mu=M.nu; T.nu=M.mu; 
	if(T.tu){ 
		for(int col=1;col<=M.nu;col++) num[col]=0; 
		for(t=1;t<=M.tu;t++) ++num[M.data[t].j]; 
		cpot[1]=1; 
		for(int i=2;i<=M.nu;i++) cpot[i]=cpot[i-1]+num[i-1]; // 求出每一列中非零元素在三元组中出现的位置 
		for(p=1;p<=M.tu;p++){ 
		int	col =M.data[p].j; q=cpot[col]; 
			T.data[q].i=col; T.data[q].j=M.data[p].i; 
			T.data[q].e=M.data[p].e; ++cpot[col]; 
		} 
	} 
	cout<<"输入矩阵的转置矩阵为"<<endl; 
	OutPutMatrix(T); 
	return true; 
} 

bool Count(RLSMatrix &T) 
{ 
	int num[MAXROW+1]; 
	for(int col=1;col<=T.mu;col++) num[col]=0; 
	for(int col=1;col<=T.tu;col++) ++num[T.data[col].i]; 
	T.rpos[1]=1; 
	for(int i=2;i<=T.mu;i++) T.rpos[i]=T.rpos[i-1]+num[i-1]; 
	return true; 
} 
// 矩阵的乘
bool MultSMatrix ( )
{ 
	RLSMatrix M,N,Q; 
	InPutMatrix(M,1); 
	InPutMatrix(N,1); 
	Count(M); Count(N); 
	if(M.nu!=N.mu) return false; 
	Q.mu=M.mu; Q.nu=N.nu; Q.tu=0; // Q初始化 
	int ctemp[MAXROW+1]; 
	int arow,tp,p,brow,t,q,ccol; 
	if(M.tu*N.tu){ 
		for( arow=1;arow<=M.mu;arow++){ 
			///memset(ctemp,0,N.nu); 
			for(int x=1;x<=N.nu;x++) 
				ctemp[x]=0; 
			Q.rpos[arow]=Q.tu+1; 
			if(arow<M.mu) tp=M.rpos[arow+1]; 
			else tp=M.tu+1; 
			for(p=M.rpos[arow];p<tp;p++){ 
				brow=M.data[p].j; 
				if(brow<N.mu) t=N.rpos[brow+1]; 
				else t=N.tu+1; 
				for(q=N.rpos[brow];q<t;q++){ 
					ccol=N.data[q].j; 
					ctemp[ccol] += M.data[p].e*N.data[q].e;
				} 
			} 
			for(ccol=1;ccol<=Q.nu;ccol++) 
				if(ctemp[ccol]){ 
					if(++Q.tu>MAXSIZE) return false; 
					Q.data[Q.tu].e=ctemp[ccol]; 
					Q.data[Q.tu].i=arow; 
					Q.data[Q.tu].j=ccol; 
				} 
		} 
	} 
	cout<<"输入的矩阵的积矩阵为"<<endl;
	OutPutMatrix(Q);
	return true; 
} 

typedef struct OLNode{ 
	int i,j; 
	int e; 
	struct OLNode *right,*down; 
}OLNode,*OLink; 

typedef struct{ 
	OLink *rHead,*cHead; 
	int mu,nu,tu; 
}CrossList; 
// 创建矩阵
bool CreateSMatrix_OL(CrossList & M){ 
	int x,y,m; 
	cout<<"依次输入矩阵的行，列，及非零元素个数"<<endl; 
	cin>>M.mu>>M.nu>>M.tu; 
	if(!(M.rHead=(OLink*)malloc((M.mu+1)*sizeof(OLink)))) exit(0); 
	if(!(M.cHead=(OLink*)malloc((M.nu+1)*sizeof(OLink)))) exit(0); 
	for(x=0;x<=M.mu;x++) 
		M.rHead[x]=NULL; 
	for(x=0;x<=M.nu;x++) 
		M.cHead[x]=NULL; 
	cout<<"以三元组的格式输入数组："<<endl; 
	for(int i=1;i<=M.tu;i++){ 
		cin>>x>>y>>m; 
		OLink p,q; 
		if(!(p=(OLink)malloc(sizeof(OLNode)))) exit(0); 
		p->i=x; p->j=y; p->e=m; 
		if(M.rHead[x]==NULL||M.rHead[x]->j>y){ 
			p->right=M.rHead[x]; M.rHead[x]=p; 
		} 
		else{ 
			for(q=M.rHead[x];(q->right)&&(q->right->j<y);q=q->right); 
			p->right=q->right; q->right=p; // 完成行插入 
		} 
		if(M.cHead[y]==NULL||M.cHead[y]->i>x){ 
			p->down=M.cHead[y]; M.cHead[y]=p; 
		} 
		else{ 
			for(q=M.cHead[y];(q->down)&&(q->down->i<x);q=q->down); 
			p->down=q->down; q->down=p; // 完成列插入 
		} 
	} 
	return true; 
} 
// 输出矩阵
bool OutPutMatrix_OL(CrossList T){ 
	for(int i=1;i<=T.mu;i++){ 
		OLink p=T.rHead[i]; 
		for(int j=1;j<=T.nu;j++){ 
			if((p)&&(j==p->j)){ 
				cout<<setw(3)<<p->e; p=p->right; 
			} 
			else 
				cout<<setw(3)<<"0"; 
		} 
		cout<<endl; 
	} 
	return true; 
} 
// 矩阵的相加
bool AddSMatrix(){ 
	CrossList M,N; 
	CreateSMatrix_OL(M); 
	CreateSMatrix_OL(N); 
	cout<<"输入的两矩阵的和矩阵为："<<endl; 
	OLink pa,pb,pre ,hl[MAXROW+1]; 
	for(int x=1;x<=M.nu;x++) hl[x]=M.cHead[x]; 
	for(int k=1;k<=M.mu;k++){ 
		pa=M.rHead[k]; pb=N.rHead[k]; pre=NULL; 
		while(pb){ 
			OLink p; 
			if(!(p=(OLink)malloc(sizeof(OLNode)))) exit(0); 
			p->e=pb->e; p->i=pb->i; p->j=pb->j; 
			if(NULL==pa||pa->j>pb->j){ 
				if(NULL==pre) 
					M.rHead[p->i]=p; 
				else 
					pre->right=p; 
				p->right=pa; pre=p; 
				if(NULL==M.cHead[p->j]){ 
					M.cHead[p->j]=p; p->down=NULL; 
				} 
				else{ 
					p->down=hl[p->j]->down; hl[p->j]->down=p; 
				} 
				hl[p->j]=p; 
				pb=pb->right; 
			} 
			else 
				if((NULL!=pa)&&pa->j<pb->j){ 
					pre=pa; pa=pa->right; 
				} 
				else 
					if(pa->j==pb->j){ 
						pa->e += pb->e; 
						if(!pa->e){ 
							if(NULL==pre) 
								M.rHead[pa->i]=pa->right; 
							else 
								pre->right=pa->right; 
							p=pa; pa=pa->right; 
							if(M.cHead[p->j]==p) M.cHead[p->j]=hl[p->j]=p->down; 
							else 
								hl[p->j]->down=p->down; 
							free(p); pb=pb->right; 
						} 
						else{ 
							pa=pa->right; pb=pb->right; 
						} 
					} 
		} 
	} 
	OutPutMatrix_OL(M); 
	return true; 
} 

int main()
{ 
	cout.fill(' '); 
	// system("color 0C"); 
	cout.fill(' '); 
	cout<<"-----请选择要进行的操作：-----"<<endl; 
	cout<<"| 1:矩阵的转置               |"<<endl; 
	cout<<"| 2:矩阵的加法或减法         |"<<endl; 
	cout<<"| 3:矩阵的乘法               |"<<endl; 
	cout<<"| 4:退出程序                 |"<<endl; 
	cout<<"------------------------------"<<endl;
	char c=getchar(); 
	if(c=='1') 
	TransMatrix( ); 
	else 
	if(c=='2') 
	AddSMatrix(); 
	else 
	if(c=='3') 
	MultSMatrix (); 
	else 
	exit(0); //退出 
	return 0;
}