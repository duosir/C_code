#include<stdio.h>
int v,e,se=0,se1,svalue,graph[50][50],keda,book[50];//se��¼�ӵı��� ,se1��¼������ԭͼ�߼������ĵڼ����ߣ� 
struct prio{//ԭͼ�ı߼� 
	int v1,v2,value;
}ee[100];
void dfs(int v1,int i,int v2){
	for(int j=0;j<v;j++)
		if(!book[j]&&graph[i][j]!=0){//������jû�����������ң�a[i][j]�бߣ�����������������b[]�� �������Ϊ�Ѿ�����������book[j]=1. 
			book[j]=1;
			if(j==v2){//�����i�����ܱ�����v2,��i�ɴ�v2. 
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
	for(int i=0;i<e-1;i++)//��ԭͼ�߼���������.
		for(int j=i;j<e;j++)
			if(ee[i].value>ee[j].value){
				struct prio v=ee[i];
				ee[i]=ee[j];
				ee[j]=v;
			}
	while(se<v-1){//���������б���=��������-1���˳�.
		int vv1= ee[se1].v1,vv2=ee[se1].v2,vvalue=ee[se1].value;
		keda=0;
		for(int i=0;i<v;i++)//������������.
			book[i]=0;
		dfs(vv1,vv1,vv2);
		if(!keda){//�����㲻�ɴ�������. 
			se++;//�ӵı�����һ 
			svalue+=vvalue;
			if(ee[se1].v1<ee[se1].v2)
				printf("%d %d\n",ee[se1].v1,ee[se1].v2);
			else
				printf("%d %d\n",ee[se1].v2,ee[se1].v1);
			//��graph�м�vv1��vv2�ı� 
			graph[vv1][vv2]=vvalue;
			graph[vv2][vv1]=vvalue;
		}
		se1++;	
	} 
	printf("%d\n",svalue);
} 
