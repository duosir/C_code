#include<stdio.h>
int a[50][50],book[50],e,v,b[50],s=0; //数组a[][]为邻接矩阵，book[i]标记顶点i是否遍历过，s记录已经遍历了多少个顶点 
void dfs(int i){
	for(int j=0;j<v;j++)
		if(!book[j]&&a[i][j]){//@若顶点j没遍历过，并且，a[i][j]有边，则将它遍历，即存入b[]中 ，并标记为已经遍历，即令book[j]=1. 
			book[j]=1;
			b[s]=j;//printf("b[%d]=%d\n",s,j);
			s++;
			dfs(j);
		}
}
int main(){
	int i=0;
	scanf("%d%d",&v,&e);
	for(i;i<e;i++){
		int v1,v2;
		scanf("%d%d",&v1,&v2);
		a[v1][v2]=1;
		a[v2][v1]=1;
	}
	for(int i=0;i<v;i++){
		for(int j=0;j<v;j++)
			if(j==0)
				printf("%d",a[i][j]);
			else
				printf(" %d",a[i][j]);
		puts("");
	}
	puts("");
	for(i=0;i<v;i++){//可能含多个连通分支，而dfs一次只能遍历一个，所以用for循环,从每个顶点开始遍历 
		if(!book[i]){//因为a[i][i]必为0，所以不会进入 @中，需要另外判断。 
			b[s]=i;
			book[i]=1;
			s++;
		}
		if(s<v)//没遍历完所有结点则继续遍历 
			dfs(i);//遍历与顶点i邻接的点（不包括i自身） 
		else
			break;//遍历完了，直接退出 
	}
	for(int i=0;i<v;i++)
		printf("%d ",b[i]);
	return 0;
}
