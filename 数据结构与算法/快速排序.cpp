#include<stdio.h>
int cnt=0; 
void qsort(int *a,int l,int r){
	cnt++;
	int t=l,v,right=r;
	if(l>r) 
		return ;
	while(l!=r){
		while(l<r&&a[r]>=a[t])//˳��Ҫ���� 
			r--;
		while(l<r&&a[l]<=a[t])
			l++;
		if(l!=r){
			v=a[l];
			a[l]=a[r];
			a[r]=v;
		}
	}
	v=a[r]; 
	a[r]=a[t];
	a[t]=v;//֮ǰ��д����a[t]=a[r]�����˺þ�û�ҳ�����. 
	qsort(a,t,l-1);
	qsort(a,r+1,right);
}
int main(){
	int a[1000],n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	qsort(a,0,n-1);
	printf("%d\n");
	for(int i=0;i<n;i++)
		printf("%d ",a[i]);
	puts("");
	return 0;
} 
