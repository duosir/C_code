#include<stdio.h>
int max=2147483647,v,e,graph[50][50],had[50],s=1,sv=0,va,had2[50]={1};
int main() {
    scanf("%d%d",&v,&e);
    for(int i=0; i<v; i++)
        for(int j=0; j<v; j++)
            graph[i][j]=max;
    for(int i=0; i<e; i++) {
        int v1,v2,value;
        scanf("%d%d%d",&v1,&v2,&value);
        graph[v1][v2]=value;
        graph[v2][v1]=value;
    }
    while(s<v) { //�������ж�����=�����������˳�
        int vv1,vv2,min=max;
        for(int ii=0; ii<s; ii++) { //������had[]���ڵĵ����������ļӱ�
            for(int i=0; i<v; i++) {
                if(had2[i])//ѡ�ĵ㲻���������еĵ�
                    continue;
                if(graph[had[ii]][i]<min) {
                    min=graph[had[ii]][i];
                    vv1=had[ii];
                    vv2=i;
                }
            }
        }
        va+=min;
        had[s]=vv2;had2[vv2]=1;
        s++;
        printf("%d %d\n",vv1,vv2);
    }
    printf("%d\n",va);
}
