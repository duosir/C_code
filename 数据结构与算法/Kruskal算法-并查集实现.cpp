#include<stdio.h>
int v,e,se=0,se1,svalue,shuyu[50];//se��¼�ӵı��� ,se1��¼������ԭͼ�߼������ĵڼ����ߣ� 
struct prio{//ԭͼ�ı߼� 
	int v1,v2,value;
}ee[100];
int main(){
	scanf("%d%d",&v,&e);
	for(int i=0;i<v;i++)
		shuyu[i]=i;
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
		while(shuyu[vv1]!=vv1)
			vv1=shuyu[vv1];
		while(shuyu[vv2]!=vv2)
			vv2=shuyu[vv2];
		if(vv1!=vv2){//����������ڲ���ͬ���������. 
			se++;//�ӵı�����һ 
			svalue+=vvalue;
			if(ee[se1].v1<ee[se1].v2)
				printf("%d %d\n",ee[se1].v1,ee[se1].v2);
			else
				printf("%d %d\n",ee[se1].v2,ee[se1].v1);
			//��vv1�����ڱ�Ϊvv2 
			shuyu[vv1]=vv2;
		}
		se1++;	
	} 
	printf("%d\n",svalue);
} 
