#include <stdio.h>
#include <windows.h>
#include <time.h>
#define XHOUR 40 //��ӡСʱ����ʼx���꣬��a��g���������
#define YHOUR 27
#define HOUR 1  //Сʱ
#define MIN 2    //����
#define SECOND 3  //��
#define SIZE 4
//��ɫ����
void color(int c){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); //��ɫ����
	//ע��SetConsoleTextAttribute��һ��API��Ӧ�ó����̽ӿڣ�
}
void gotoxy(int x, int y) {
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ��׼����豸���
	SetConsoleCursorPosition(hOut, pos);//���������ֱ���ָ���ĸ����壬����λ��
}
/*				b
			 a     c
				g   
			 f     d
				e
*/
void preprint(int num,int x,int y) {//num:��ӡ������;
	int i;
	/*a*/
	for (i = 0; i < SIZE-1; i++) {
		y-=1;
		gotoxy(x,y);
		if (num == 0 || num > 3 && num != 7)
			printf("%d", num);
		else
			printf(" ");
	}
	y--;
	/*b*/
	for (i = 0; i < SIZE-1; i++) {
		x += 2;
		gotoxy(x,y);
		if (num != 1&& num !=4)
			printf("%d", num);
		else
			printf(" ");
	}
	x += 2;
	/*c*/
	for (i = 0; i < SIZE-1; i++) {
		y += 1;
		gotoxy(x,y);
		if (num != 5 && num != 6)
			printf("%d", num);
		else
			printf(" ");
	}
	y += 1;
	/*d*/
	for (i = 0; i < SIZE-1; i++) {
		y += 1;
		gotoxy(x,y);
		if (num != 2 )
			printf("%d", num);
		else
			printf(" ");
	}
	y += 1;
	/*e*/
	for (i = 0; i < SIZE-1; i++) {
		x -= 2;
		gotoxy(x, y);
		if (num != 1 && num != 4 && num != 7)
			printf("%d", num);
		else
			printf(" ");
	}
	x -= 2;
	/*f*/
	for (i = 0; i < SIZE-1; i++) {
		y -= 1;
		gotoxy(x, y);
		if (num != 1 && num != 3 && num != 4 && num != 5 && num != 7 && num != 9)
			printf("%d", num);
		else
			printf(" ");
	}
	y -= 1;
	/*g*/
	for (i = 0; i < SIZE-1; i++) {
		x += 2;
		gotoxy(x, y);
		if (num != 1 && num != 0 && num != 7)
			printf("%d", num);
		else
			printf(" ");
	}
}
void print(int nums, int mode) {//nums:��ӡ����;mode:1��Сʱ��2�Ƿ��ӣ�3����;isprint:�Ǵ�ӡ����ɾ��������ӡ�ո񣬶����ǿ��ַ���
	color(6); //��ɫ����Ϊ����ɫ
	int x, y;//�������
	x = XHOUR + (mode - HOUR) * 27;
	y = YHOUR;
	preprint(nums /10,x,y);
	preprint(nums % 10,x+10,y);
	gotoxy(1, 1);
	printf("");
}
void print1() {
	gotoxy(XHOUR + 27-4, YHOUR-1);
	printf("#");
	gotoxy(XHOUR + 27-4, YHOUR +1);
	printf("#");
	gotoxy(XHOUR + 27*2-4, YHOUR + 1);
	printf("#");
	gotoxy(XHOUR + 27*2-4, YHOUR - 1);
	printf("#");
}
int main() {
	int m = 40, n = 10, k = 1,hour,min,second,ms;
	printf("�����뵱ǰʱ��(��ʽ:hour:min:second)��");
	scanf("%d %d %d", &hour, &min, &second);
	system("cls");
	print1();
	print(hour,1);
	print(min,2);
	while (1) {
		print(second,3);
		second++;
		if (second == 60) {
			second = 0;
			min++;
			print(second,3);
			print(min, 2);
		}
		if (min == 60) {
			hour++;
			min = 0;
			print(min, 2);
			print(hour, 1);
		}
		if (hour == 24){
			hour = 0;
			print(hour,1);
		}
		Sleep(978);
	}
	for (int i = 0; i < 10; i++)
		puts(" ");
}

