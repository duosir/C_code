#include<stdio.h>
int a[50][50],book[50],e,v,b[50],s=0; //����a[][]Ϊ�ڽӾ���book[i]��Ƕ���i�Ƿ��������s��¼�Ѿ������˶��ٸ����� 
void dfs(int i){
	for(int j=0;j<v;j++)
		if(!book[j]&&a[i][j]){//@������jû�����������ң�a[i][j]�бߣ�����������������b[]�� �������Ϊ�Ѿ�����������book[j]=1. 
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
	for(i=0;i<v;i++){//���ܺ������ͨ��֧����dfsһ��ֻ�ܱ���һ����������forѭ��,��ÿ�����㿪ʼ���� 
		if(!book[i]){//��Ϊa[i][i]��Ϊ0�����Բ������ @�У���Ҫ�����жϡ� 
			b[s]=i;
			book[i]=1;
			s++;
		}
		if(s<v)//û���������н����������� 
			dfs(i);//�����붥��i�ڽӵĵ㣨������i���� 
		else
			break;//�������ˣ�ֱ���˳� 
	}
	for(int i=0;i<v;i++)
		printf("%d ",b[i]);
	return 0;
}
