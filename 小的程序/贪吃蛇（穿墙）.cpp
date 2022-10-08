#include<stdio.h>
#include<Windows.h>
#include<stdlib.h> 
#include<conio.h> 
#define COL 45 //����˫����,ע��һ����ռʵ�����У����ҽ���һ����˫�С��ɣ����˴��ı� system("mode con cols=2*COL lines=ROW+2"); //����cmd���ڵĴ�С,Ҳ�ñ䡣 
#define ROW 25 //�������� 
#define ROWK ROW+2
#define KONG 0 
#define WALL 1 
#define FOOD 2 
#define BODY 3 
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define LA 1 //�Ѷȣ�ֵԽС�Ѷ�Խ�� 
#define LB 20 
#define LC 40 
//ʳ�������/ǽ   ������ڵ�һ�У�ָ���ڵڶ��� 
//�������[]��һ�������һ�ڡ����� x=body_x[head]��y=body_y[head],��x,y)��]�����ꡣ
//����Ҫ��ӡ[], Ӧ��gotoxy(x-1,y). ��ӡ��
//����state[x1][y1]��Ӧgotoxy(y1,x1),��Ϊ�����x1���кţ���gotoxy��һ���������кš� 
struct SnakeBody{//���� 
	int body_x[COL*ROW];//��������� 
	int body_y[COL*ROW]; 
	int head;//ͷ 
	int tail;//β 
	int fx;//���� 
}Snake; 
int first=1;
char start,sp;
long long grade,recordgrade; 
int state[ROW][2*COL],die,speed; //��¼����ÿ�����ӵ�״̬��WALL��ʾ��ǽ��BODY��ʾ���壬KONG��ʾΪ0��FOOD��ʾʳ������ߡ� 
//state[ROW][2*COL]������ state[2*ROW][COL]������state[1][5.6.7] ����1. 
void color(int c);
void gotoxy(int x, int y) ;
void record_file(int read);//��1�Ǵ�ӡ��¼����0���Ǹ��¼�¼ 
void initial();
void initialSnake();
void randFood();
void move(int x,int y);
int Clik();
int keyJudge(int key);
void run();
int main(){
	system("title ̰����"); //���ô��ڵ�����
	system("mode con cols=90 lines=27"); //���ô��ڵĴ�С 
	do{
		initial();//��ʼ���� 
		initialSnake();
		randFood();
		gotoxy(2,4);
		color(6) ; //���ǻ�ɫ 
		run(); 
		system("cls");
		gotoxy(COL-4,ROW/2-3);
		printf("�����ε÷�Ϊ��%lld��",grade);
		record_file(0);
		gotoxy(COL-4,ROW/2);
		printf("����(b):");
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
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ��׼����豸���
    SetConsoleCursorPosition(hOut, pos);//���������ֱ���ָ���ĸ����壬����λ��
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
		if(f==NULL){//���û���ļ��ʹ�����������ʼֵ0 
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
		}
	} 
	else if(grade>recordgrade){
		gotoxy(COL-10,ROW/2-2);
		printf("��ϲ��Ҵ��Ƽ�¼����¼����Ϊ:%lld��",grade);
		recordgrade=grade; 
		FILE* f;
		if(speed==LA)
			f=fopen("recordA.txt","w");//���Ƿ�ʽд��
		else if(speed==LB)
			f=fopen("recordB.txt","w");
		else
			f=fopen("recordC.txt","w"); 
		fprintf(f,"%lld",recordgrade);//���ü�&������д���ǵ�ַ�� 
		fclose(f);
	}
}
void initial(){
	system("cls");
	color(4);
	die=0,grade=0,speed=0;
	if(first){
		gotoxy(COL-4,ROW/2);
		printf("ѡ���Ѷ�(a/b/c):");
		do{
			scanf("%c",&sp);
			if(sp=='c'||sp=='C')
				speed=LC;
			else if(sp=='b'||sp=='B')
				speed=LB;
			else if(sp=='a'||sp=='A')
				speed=LA;
		} while(speed==0);
		gotoxy(COL-4,ROW/2+2);
		printf("��ʼ��Ϸ(y/n):");
		do{
			scanf("%c",&start);
			if(start=='n'||start=='N')
				exit(0);
		} while(start!='y'&&start!='Y');
		first=0; 
	}
	else{
		do{
			gotoxy(COL-4,ROW/2);
			printf("����һ��(y/n):");
			scanf("%c",&start);
			if(start=='n'||start=='N')
				exit(0);
		} while(start!='y'&&start!='Y');
		gotoxy(COL-4,ROW/2+2);
		printf("ѡ���Ѷ�(a/b/c):");
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
			if(i==0||i==ROW-1||j<=1||j>=2*COL-2){//ע��()�ڵ�����j<=1||j>=2*COL-2,j==1��j==2*COL-1����ӡ�ո�
			//��Ϊ��һ˫�к����һ˫����ǽ��ÿ��˫�ж���ǰһ���д�ӡ�����������Ե�2�к����1�оͲ���ӡ�ո��� 
				if(j%2==0){
					state[i][j]=WALL;
					state[i][j+1]=WALL;  
					printf("��");
				}
			}
			else
				printf(" ");
		}
	}
	gotoxy(0,ROW);
	printf("�÷�:");
	gotoxy(6,ROW);
	printf("%lld��",grade); 
	record_file(1);
	gotoxy(COL*2-20,ROW);
	printf("��¼:%lld��",recordgrade);
}
void initialSnake(){
	color(6);
	gotoxy(2,4);
	printf("��");
	Snake.body_x[0]=3;
	Snake.body_y[0]=4;
	state[4][2]=WALL;
	state[4][3]=WALL;
	Snake.head =0;
	Snake.tail =0;
	Snake.fx=RIGHT; //��ʼ�������� 
}
void randFood(){
	color(4); 
	int x,y;
	do{
		x=rand()%(2*COL-1);
		y=rand()%(ROW-1);
	}while(state[y][x]==FOOD||state[y][x]==WALL||x%2);//ǰһ���������ж��Ƿ������������ǽ�ڣ���һ�����޶�xֻ����2�ı�������Ϊ���� 
	gotoxy(x,y);
	printf("��");
	state[y][x]=FOOD; 
	state[y][x+1]=FOOD; 
	color(6) ;
}
int Clik(){ 
	int t=800;//�����м���Ч���� 
	while(t--){
		if(kbhit())
			return 1;
	}
	return 0;//û�а������������
}
int keyJudge(int key){//�ж�����ķ�����Ƿ�ı�ԭ���� 
	if(key==UP&&Snake.fx==DOWN||key==DOWN&&Snake.fx==UP||key==LEFT&&Snake.fx==RIGHT||key==RIGHT&&Snake.fx==LEFT)
		return 0;
	return 1;
}
void move(int x,int y){
	Sleep(speed);
	int to_x=Snake.body_x[Snake.head]+2*x,to_y=Snake.body_y[Snake.head]+y;//to_x��ͷָ���x,���ǹ��� 
	gotoxy(to_x-1,to_y);//�����ת����һ��λ��[ 
	if(state[to_y][to_x]==BODY||state[to_y][to_x-1]==BODY){//������ ,ע����-1����-x�� 
		die=1;
		Sleep(2000);//����������2�뷴Ӧʱ�䡣 
		return;
	}
	else if(state[to_y][to_x]==FOOD||state[to_y][to_x-1]==FOOD){//�Ե�ʳ����·���
		grade+=10;
		gotoxy(5,ROW);
		printf("%lld��",grade); 
		//gotoxy(to_x-1,to_y);//��ת����
		randFood(); 	
	}
	else{//�ǿջ�ǽ 
		state[Snake.body_y[Snake.tail]][Snake.body_x[Snake.tail]]=KONG; //����β�� ����״̬ 
		state[Snake.body_y[Snake.tail]][Snake.body_x[Snake.tail]-1]=KONG;
		gotoxy(Snake.body_x[Snake.tail]-1,Snake.body_y[Snake.tail]);	//β�ͱ�ɿո� 
		printf(" ");
		gotoxy(Snake.body_x[Snake.tail],Snake.body_y [Snake.tail]);
		printf(" ");
		Snake.tail=(Snake.tail+1)%(COL*ROW);//����βָ�� 
		if(state[to_y][to_x]==WALL||state[to_y][to_x-1]==WALL){ //��ǽ ,��ǽ,ע����-1����-x�� 
			if(Snake.fx==UP)
				to_y=ROW-2;
			else if(Snake.fx==DOWN){ 
				to_y=1;
			}
			else if(Snake.fx==LEFT){
				to_x=2*COL-3;
			}
			else if(Snake.fx==RIGHT){
				to_x=3;
			}
		} 
	}
	Snake.head=(Snake.head+1)%(COL*ROW);//����ͷָ�� 
	Snake.body_x[Snake.head]=to_x;//����ͷ���� 
	Snake.body_y[Snake.head]=to_y; 
	gotoxy(to_x-1,to_y);
	printf("��");
	state[to_y][to_x]=BODY;//����ǰ����ͷ��״̬ 
	state[to_y][to_x-1]=BODY;
	gotoxy(to_x-1,to_y);
//	if(grade>=30){
//		system("cls");
//		for(int i=0;i<ROW;i++){
//			for(int j=0;j<2*COL;j++)
//				printf("%d",state[i][j]);
//		}
//		while(1){
//			
//		}
//	} 
}
void run(){
	while(1){
		if(die)
			break;
		int k=0,key;
		k=Clik();
		if(k!=0){//��ð��� 
			int key1=getch() ;
			key=getch();
			if(key!=Snake.fx&&keyJudge(key))
				Snake.fx =key;
		}
		if(Snake.fx==UP)
				move(0,-1);
		else if(Snake.fx==DOWN)
				move(0,1);
		else if(Snake.fx==LEFT)
				move(-1,0);
		else if(Snake.fx==RIGHT){
				move(1,0);
		}
	}
}
