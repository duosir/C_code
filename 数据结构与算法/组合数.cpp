#include<stdio.h>
int n,m,book[100],a[100];
void zuhe(int step){
	if(step==m+1){
		for(int i=1;i<=m;i++)
			printf("%d ",a[i]);
		puts("");
	}
	for(int i=1;i<=n;i++){
		if(!book[i]&&i>a[step-1]){//n的全排列（注意是全排列）加判断后一个大于前一个，就可得组合数。 
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
