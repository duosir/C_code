#include<stdio.h>
#include<Windows.h>
#include<stdlib.h> 
#include<conio.h> 
//可根据COL,ROW设计贪吃蛇游戏区域的大小。 
#define COL 60 //方框双列数,注意一个■占实际两列，姑且叫做一个“双列”吧！若此处改变 system("mode con cols=2*COL lines=ROW+4"); //设置cmd窗口的大小,也得变。 
#define ROW 35 //方框行数 
#define KONG 0 
#define WALL 1
#define FOOD 2  
#define BODY 3
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define LA 10 //难度，值越小难度越大 
#define LB 60 
#define LC 100 
//食物：●蛇身/墙   ■光标在第一列，"指针"在第二列 
//比如假设[]是一个身体的一节■，若 x=body_x[head]，y=body_y[head],则（x,y)是]的坐标。
//而若要打印[], 应该gotoxy(x-1,y). 打印。
//另外state[x1][y1]对应gotoxy(y1,x1),因为数组第x1是行号，而gotoxy第一个参数是列号。 
struct SnakeBody{//蛇身 
	int body_x[COL*ROW];//蛇身横坐标 
	int body_y[COL*ROW]; 
	int head;//头“指针 ” 
	int tail;//“尾指针 ” 
	int fx;//方向 
}Snake;
char start,sp,tip[3][40]={"长按方向键加速！","梦是少年的梦，蛇是虚幻之蛇...","加油，干饭人！^_^"};
long long grade,recordgrade;
int state[ROW][2*COL],die,speed,tipi=0,first=1; //记录方框每个格子的状态，WALL表示是墙，BODY表示身体)，KONG表示为0，FOOD表示食物可以走。 
//state[ROW][2*COL]，不是 state[2*ROW][COL]，否则state[1][5.6.7] 都是1. 
void color(int c);
void gotoxy(int x, int y) ;
void record_file(int read);//传1是打印最高分，传0则是更新最高分 
void initial();
void initialSnake();
void randFood();
void move(int x,int y);
int Clik();
void run();
int main(){
	system("title 贪吃蛇"); //设置窗口的名字
	system("mode con cols=120 lines=39"); //设置窗口的大小 
	do{
		initial();//初始界面 
		initialSnake();
		randFood();
		gotoxy(2,4);
		color(6) ; //蛇是黄色 
		run(); 
		system("cls");
		gotoxy(COL-10,ROW/2-4);
		printf("您本次得分为：%lld分",grade);
		record_file(0);
		gotoxy(COL-6,ROW/2);
		printf("返回(b):");
		do{
			scanf("%c",&sp);
			if(sp=='b'||sp=='B')
				break;
		} while(1);
	}
	while(1);
}
void color(int c){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); 
}
void gotoxy(int x, int y) {
    COORD pos = {x,y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
    SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
}
void record_file(int read){
	if(read){
		FILE* f;
		if(speed==LA)
			f=fopen("recordA.txt","r");
		else if(speed==LB)
			f=fopen("recordB.txt","r");
		else
			f=fopen("recordC.txt","r");
		if(f==NULL){//如果没有文件就创建，并赋初始值0 
			if(speed==LA)
				f=fopen("recordA.txt","w");
			else if(speed==LB)
				f=fopen("recordB.txt","w");
			else
				f=fopen("recordC.txt","w");
			fprintf(f,"%lld",0);
			recordgrade=0;
			fclose(f);
		}
		else{
			fscanf(f,"%lld",&recordgrade);
			fclose(f);
			gotoxy(44,25);
		}
	} 
	else if(grade>recordgrade){
		gotoxy(COL-20,ROW/2-2);
		printf("恭喜玩家打破纪录！记录更新为:%lld分",grade);
		recordgrade=grade; 
		FILE* f;
		if(speed==LA)
			f=fopen("recordA.txt","w");//覆盖方式写入
		else if(speed==LB)
			f=fopen("recordB.txt","w");
		else
			f=fopen("recordC.txt","w"); 
		fprintf(f,"%lld",recordgrade);//不用加&，否则写的是地址。 
		fclose(f);
	}
}
void initial(){
	system("cls");
	color(4);
	die=0,grade=0,speed=0,tipi=0;
	if(first){
		gotoxy(COL-10,ROW/2);
		printf("选择难度(a/b/c):");
		do{
			scanf("%c",&sp);
			if(sp=='c'||sp=='C')
				speed=LC;
			else if(sp=='b'||sp=='B')
				speed=LB;
			else if(sp=='a'||sp=='A')
				speed=LA;
		} while(speed==0);
		gotoxy(COL-8,ROW/2+2);
		printf("开始游戏(y/n):");
		do{
			scanf("%c",&start);
			if(start=='n'||start=='N')
				exit(0);
		} while(start!='y'&&start!='Y');
		first=0; 
	}
	else{
		do{
			gotoxy(COL-8,ROW/2);
			printf("再来一局(y/n):");
			scanf("%c",&start);
			if(start=='n'||start=='N')
				exit(0);
		} while(start!='y'&&start!='Y');
		gotoxy(COL-10,ROW/2+2);
		printf("选择难度(a/b/c):");
		do{
			scanf("%c",&sp);
			if(sp=='c'||sp=='C')
				speed=LC;
			else if(sp=='b'||sp=='B')
				speed=LB;
			else if(sp=='a'||sp=='A')
				speed=LA;
		} while(speed==0);
	}
	system("cls");
	for(int i=0;i<ROW;i++)
		for(int j=0;j<2*COL;j++)
			state[i][j]=KONG; 
	for(int i=0;i<ROW;i++){
		for(int j=0;j<2*COL;j++){
			if(i==0||i==ROW-1||j<=1||j>=2*COL-2){//注意()内的条件j<=1||j>=2*COL-2,j==1和j==2*COL-1不打印空格，
			//因为第一双列和最后一双列是墙，每个双列都是前一个列打印‘■’。所以第2列和最后1列就不打印空格了 
				if(j%2==0){
					state[i][j]=WALL;
					state[i][j+1]=WALL;  
					printf("■");
				}
			}
			else
				printf(" ");
		}
	}
	gotoxy(0,ROW);
	printf("得分:");
	gotoxy(5,ROW);
	printf("%lld分",grade); 
	record_file(1);
	gotoxy(COL,ROW);
	printf("最高分:%lld分",recordgrade);
}
void initialSnake(){
	color(6);
	gotoxy(2,4);
	printf("■");
	Snake.body_x[0]=3;
	Snake.body_y[0]=4;
	state[4][2]=WALL;
	state[4][3]=WALL;
	Snake.head =0;
	Snake.tail =0;
	Snake.fx=RIGHT; //初始化向右走 
}
void randFood(){
	color(4); 
	int x,y;
	do{
		x=rand()%(2*COL-1);
		y=rand()%(ROW-1);
	}while(state[y][x]==BODY||state[y][x]==FOOD||state[y][x]==WALL||x%2);//前一个条件是判断是否生成在蛇身或墙内，后一个则限定x只能是2的倍数，因为这样 
	gotoxy(x,y);
	printf("●");
	state[y][x]=FOOD; 
	state[y][x+1]=FOOD; 
	color(6) ;
}
int Clik(){ 
	int t=1000;
	while(t--){
		if(kbhit())//长按方向键可以加速（因为加速了return)。 
			return 1;
	}
	return 0;//没有按键，方向继续
}
void move(int x,int y){
	Sleep(speed);//难度ABC实现。 
	int to_x=Snake.body_x[Snake.head]+2*x,to_y=Snake.body_y[Snake.head]+y;//to_x是头指针的x,不是光标的 
	gotoxy(to_x-1,to_y);//光标跳转到下一个位置 
	Snake.head=(Snake.head+1)%(COL*ROW);//更新头指针 
	Snake.body_x[Snake.head]=to_x;//更新头坐标 
	Snake.body_y[Snake.head]=to_y; 
	printf("■");
	if(state[to_y][to_x]==WALL||state[to_y][to_x-1]==WALL){//是墙或身体 ,注意是-1不是-x； 
		die=1;
		return;
	}
	else if(state[to_y][to_x]==FOOD||state[to_y][to_x-1]==FOOD){//吃到食物，更新分数
		grade+=5;
		gotoxy(5,ROW);
		printf("%lld分",grade); 
		randFood();
		if(tipi==0){
			gotoxy(COL/2,ROW+1);
			printf("                                              ");
			gotoxy(COL/2,ROW+1);
			printf("%s",tip[rand()%3]); 
			tipi=5;
		}
		tipi--;	
	}
	else{//是空
		state[Snake.body_y[Snake.tail]][Snake.body_x[Snake.tail]]=KONG; //更新尾巴 处的状态 
		state[Snake.body_y[Snake.tail]][Snake.body_x[Snake.tail]-1]=KONG;
		gotoxy(Snake.body_x[Snake.tail]-1,Snake.body_y[Snake.tail]);	//尾巴变成空格 
		printf(" ");
		gotoxy(Snake.body_x[Snake.tail],Snake.body_y [Snake.tail]);
		printf(" ");
		Snake.tail=(Snake.tail+1)%(COL*ROW);//更新尾指针 
	}
	state[to_y][to_x]=BODY;//更新前进的头的状态 
	state[to_y][to_x-1]=BODY;
	gotoxy(to_x-1,to_y);
}
void run(){
	while(1){
		if(die)
			break;
		int k=0,key;
		k=Clik();
		if(k!=0){//获得按键 
			key=getch();
			Snake.fx=key;
		}
		if(Snake.fx==UP)
				move(0,-1);
		else if(Snake.fx==DOWN)
				move(0,1);
		else if(Snake.fx==LEFT)
				move(-1,0);
		else if(Snake.fx==RIGHT)
				move(1,0);
	}
}
