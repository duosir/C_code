#include <stdio.h>
#include <windows.h>
void color(int c){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); 
}
void gotoxy(int x, int y) {
    COORD pos = {x,y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
    SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
}
void print(int m,int n,int r,int c){
	int i;
	gotoxy((2*m+c)/2+2,(2*n+r)/2);
	printf("$");
	color(6); //4是红色， 6是土黄色 
	for(i=0;i<r;i++){
		m+=2;
		gotoxy(m,n);
		printf("*");
	}
	for(i=0;i<c;i++){
		n+=1;
		gotoxy(m,n);
		printf("*");
	}
	for(i=0;i<r;i++){
		m-=2;
		gotoxy(m,n);
		printf("*");
	}
	for(i=0;i<c;i++){
		n-=1;
		gotoxy(m,n);
		printf("*");
	}
}
void dele(int m,int n,int r,int c){
	int i;
	gotoxy((2*m+c)/2+2,(2*n+r)/2);
	printf(" ");
	for(i=0;i<r;i++){
		m+=2;
		gotoxy(m,n);
		printf(" ");
	}
	for(i=0;i<c;i++){
		n+=1;
		gotoxy(m,n);
		printf(" ");
	}
	for(i=0;i<r;i++){
		m-=2;
		gotoxy(m,n);
		printf(" ");
	}
	for(i=0;i<c;i++){
		n-=1;
		gotoxy(m,n);
		printf(" ");
	}
}
int main(){
	int m=40,n=10,k=1;
	//打印外框 
	for(int i=0;i<70;i++){
		for(int j=0;j<70;j++){
			if(j>19&&j<=49&&(i==9||i==40))
				printf("-");
			else
				printf(" ");
			if(i>=9&&i<=40&&(j==19||j==49))
				printf("|");
			else
				printf(" ");
		}
		printf("\n");
	}
	Sleep(1000);
	
	while(1){
		print(m,n,4,4);
		Sleep(20);
		if(k<=75&&k>50||k<=150&&k>125)
			Sleep(40);
		dele(m,n,4,4);
		if(k<=50)
			m++;//k初值得为1 ，不然这里k++了51次，而下面只--了50次 
		else if(k<=75)
			n++;
		else if(k<=125)
			m--;
		else if(k<=150)
			n--;
		k++;
		if(k==151)
			k=1;
	}
}
