#include<stdio.h>
int n,m,book[100],a[100];
void zuhe(int step){
	if(step==m+1){
		for(int i=1;i<=m;i++)
			printf("%d ",a[i]);
		puts("");
	}
	for(int i=1;i<=n;i++){
		if(!book[i]&&i>a[step-1]){//n��ȫ���У�ע����ȫ���У����жϺ�һ������ǰһ�����Ϳɵ�������� 
			a[step]=i;
			book[i]=1;//!!
			zuhe(step+1);
			book[i]=0;
		}
	}
}
int main(){
	scanf("%d %d",&n,&m);
	zuhe(1);
} 
