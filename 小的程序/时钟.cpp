#include <stdio.h>
#include <windows.h>
#include <time.h>
#define XHOUR 40 //打印小时的起始x坐标，即a，g交点横坐标
#define YHOUR 27
#define HOUR 1  //小时
#define MIN 2    //分钟
#define SECOND 3  //秒
#define SIZE 4
//颜色设置
void color(int c){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); //颜色设置
	//注：SetConsoleTextAttribute是一个API（应用程序编程接口）
}
void gotoxy(int x, int y) {
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
	SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
}
/*				b
			 a     c
				g   
			 f     d
				e
*/
void preprint(int num,int x,int y) {//num:打印的数字;
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
void print(int nums, int mode) {//nums:打印的数;mode:1是小时，2是分钟，3是秒;isprint:是打印还是删除（即打印空格，而不是空字符）
	color(6); //颜色设置为土黄色
	int x, y;//坐标变量
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
	printf("请输入当前时间(格式:hour:min:second)：");
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

