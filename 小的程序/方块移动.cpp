#include <stdio.h>
#include <windows.h>
void color(int c){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); 
}
void gotoxy(int x, int y) {
    COORD pos = {x,y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ��׼����豸���
    SetConsoleCursorPosition(hOut, pos);//���������ֱ���ָ���ĸ����壬����λ��
}
void print(int m,int n,int r,int c){
	int i;
	gotoxy((2*m+c)/2+2,(2*n+r)/2);
	printf("$");
	color(6); //4�Ǻ�ɫ�� 6������ɫ 
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
	//��ӡ��� 
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
			m++;//k��ֵ��Ϊ1 ����Ȼ����k++��51�Σ�������ֻ--��50�� 
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
