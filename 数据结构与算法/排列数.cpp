#include<stdio.h>
int n,m,book[100],a[100];
void pailie(int step){
	if(step==n+1){
		for(int i=1;i<=n;i++)
			printf("%5d",a[i]);
		puts("");
	}
	for(int i=1;i<=n;i++){
		if(!book[i]){
			a[step]=i;
			book[i]=1;
			pailie(step+1);
			book[i]=0;
		}
	}
}
int main(){
	scanf("%d",&n);
	pailie(1);
} 
