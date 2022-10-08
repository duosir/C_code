#include<stdio.h>
#include<stdlib.h>
int v,e,book[20];
typedef struct vnode *pnode;
struct vnode{
	int data;
	pnode next; 
}a[20];
struct que{
	int data[100],rear,tail,len;
};
void insert(int v1,int v2){
	if(!a[v1].next ){//若表为空，则新建 
			a[v1].next=(pnode)malloc(sizeof(struct vnode));
			a[v1].next->data =v2;
			a[v1].next->next =NULL;
		}
		else{//不为空，则插入 
			pnode p=(pnode)malloc(sizeof(struct vnode));;
			p->data=v2;
			p->next =a[v1].next ;
			a[v1].next=p;
		}
}
int main(){
	int s=0;
	struct que qu;
	for(int i=0;i<20;i++){
		a[i].next =NULL;
	}
	qu.rear =qu.tail=qu.len=0;
	scanf("%d%d",&v,&e);
	for(int i=0;i<e;i++){
		int v1,v2;
		scanf("%d%d",&v1,&v2);
		insert(v1,v2);
		insert(v2,v1);
	}
	for(int i=0;i<v;i++){
		printf("%d",i);
		pnode p=a[i].next ;
		while(p){
			printf(" %d",p->data );
			p=p->next;
		}
		puts("");
	}
	puts("");
	for(int i=0;i<v;i++){
		while(s<v){
			//printf("hh");
			if(!book[i]){
				qu.data[qu.tail] =i;
				printf("%d ",i);s++;
				qu.len ++;qu.tail++;
				book[i]=1;
			}
			pnode p=a[i].next;
			while(p){//将表中顶点存入队列 ，并访问 
				if(!book[p->data]){
					qu.data[qu.tail]=p->data;
					printf("%d ",p->data);s++;
					qu.len ++;qu.tail++;
					book[p->data]=1;
					p=p->next ;
				}
			}
			while(qu.len) {//将该连通分支顶点全部访问 
				pnode p=a[qu.data[qu.rear]].next;
				qu.rear++;qu.len--;
				while(p){
					if(!book[p->data]){
						qu.data[qu.tail]=p->data;
						printf("%d ",p->data);s++;
						qu.len ++;qu.tail++;
						book[p->data]=1;
					}
					p=p->next ;
				}
			}
			if(!qu.len){
				break;
			}
		}
	}
	return 0;
}
