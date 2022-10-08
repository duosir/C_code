#include<stdio.h>
int v,e,se=0,se1,svalue,graph[50][50],keda,book[50];//se记录加的边数 ,se1记录现在是原图边集排序后的第几个边； 
struct prio{//原图的边集 
	int v1,v2,value;
}ee[100];
void dfs(int v1,int i,int v2){
	for(int j=0;j<v;j++)
		if(!book[j]&&graph[i][j]!=0){//若顶点j没遍历过，并且，a[i][j]有边，则将它遍历，即存入b[]中 ，并标记为已经遍历，即令book[j]=1. 
			book[j]=1;
			if(j==v2){//如果从i进入能遍历到v2,则i可达v2. 
				keda=1;
				return ;
			}
			dfs(v1,j,v2);
		}
}
int main(){
	scanf("%d%d",&v,&e);
	for(int i=0;i<e;i++)
		scanf("%d%d%d",&ee[i].v1,&ee[i].v2,&ee[i].value);
	for(int i=0;i<e-1;i++)//将原图边集升序排序.
		for(int j=i;j<e;j++)
			if(ee[i].value>ee[j].value){
				struct prio v=ee[i];
				ee[i]=ee[j];
				ee[j]=v;
			}
	while(se<v-1){//当生成树中边数=顶点总数-1，退出.
		int vv1= ee[se1].v1,vv2=ee[se1].v2,vvalue=ee[se1].value;
		keda=0;
		for(int i=0;i<v;i++)//将标记数组归零.
			book[i]=0;
		dfs(vv1,vv1,vv2);
		if(!keda){//两顶点不可达，则可连接. 
			se++;//加的边数加一 
			svalue+=vvalue;
			if(ee[se1].v1<ee[se1].v2)
				printf("%d %d\n",ee[se1].v1,ee[se1].v2);
			else
				printf("%d %d\n",ee[se1].v2,ee[se1].v1);
			//在graph中加vv1到vv2的边 
			graph[vv1][vv2]=vvalue;
			graph[vv2][vv1]=vvalue;
		}
		se1++;	
	} 
	printf("%d\n",svalue);
} 
