#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<dos.h>
#include<conio.h>
int gdriver=DETECT,gmode,x1=0,y1=0,x2,y2,k=0,c,a,i=0;
int bufx[150],bufy[150],dist=7,delayspeed=100,size,d;
int rndx,rndy,tail=2,dash=0;
int life=5;
FILE *f;
int choice;
struct highscore{
	int hscore;
	char name[30];
};
struct highscore hs;
void statusbar();
void highscore(int s){
	f=fopen("highscore.DAT","wb+");
	fread(&hs,sizeof(hs),1,f);
	if(hs.hscore<(s-2)*4){
		hs.hscore=(s-2)*4;
		cleardevice();
		gotoxy(20,6);
		printf("CONGRATS ! you set a new high score");
		gotoxy(20,8);
		printf("Enter your name : ");
		scanf("%s",&hs.name);
		fseek(f,ftell(f)-sizeof(hs),0);
		fwrite(&hs,sizeof(hs),1,f);
	}
}
void randomnumber(){
	int i,j;
	randomize();
	i=random(10000)%40;
	i=i*dist;
	j=random(10000)%40;
	j=j*dist;
	rndx=i;
	rndy=j;
}
	void checkcollision(int x1,int y1){
		int i;
		for(i=0;i<=size;i++){
			if(bufx[i]==x1&&bufy[i]==y1)dash=1;
		}
		if(x1<0||x1>=400||y1<0||y1>400)dash=1;
		if(dash){
			highscore(size);
			if(--life<0)exit(0);
			sound(700);
			delay(300);
			nosound();
			if(size>25)life++;
			size=tail;
			cleardevice();
		}
		statusbar();
	}
	void checkcapture(int x1,int y1){
		int i;
		if(x1==rndx&&y1==rndy){
			size++;
			sound(500);
			delay(100);
			randomnumber();
		}
		setfillstyle(11,14);
		bar3d(rndx,rndy,rndx+dist,rndy+dist,0,0);
	}
void move(int a){
	while(!kbhit()){
		if(!dash){
			k=k++%size;
			i++;
			setfillstyle(1,7);
			bar3d(x1,y1,x1+dist,y1+dist,0,0);
			if(i>=size){
				setfillstyle(0,0);
				setcolor(0);
				bar3d(bufx[k],bufy[k],bufx[k]+dist,bufy[k]+dist,0,0);
				bufx[k]=x1;
				bufy[k]=y1;
				setcolor(15);
				checkcapture(x1,y1);
			}
			else{
				bufx[1]=x1;
				bufy[1]=x2;
			}
			if(a==1)x1+=dist;
			if(a==2)x1-=dist;
			if(a==3)y1+=dist;
			if(a==4)y1-=dist;
			checkcollision(x1,y1);
			setfillstyle(1,14);
			bar3d(x1,y1,x1+dist,y1+dist,0,0);
			sound(300);
			delay(delayspeed);
			nosound();
			delay(delayspeed);
		}
	}
 }
void statusbar(){
	char s[10];
	s[1]=life;
	setlinestyle(0,0,3);
	setcolor(RED);
	rectangle(0,0,400,400);
	setfillstyle(1,BLUE);
	floodfill(10,10,RED);
	gotoxy(55,2);
	printf("Life: %d score:%d",life,(size-2)*4);
	gotoxy(55,5);
	printf("Down: ");
	putchar(31);
	printf("\tUp: ");
	putchar(30);
	gotoxy(55,6);
	printf("Right: ");
	putchar(16);
	printf("\tLeft: ");
	putchar(17);
	gotoxy(55,8);
	printf("HIGHSCORE");
	f=fopen("highscore.DAT","rb+");
	rewind(f);
	fread(&hs,sizeof(hs),1,f);
	gotoxy(55,10);
	printf("Name : %s",hs.name);
	gotoxy(55,11);
	printf("High score : %d",hs.hscore);
	fclose(f);
}
void main(){
	initgraph(&gdriver,&gmode,"c:\\tc\\bgi");
	size=tail;
	cleardevice();
	setbkcolor(GREEN);
	gotoxy(10,5);
	printf("Enter the speed:\n");
	gotoxy(10,7);
	printf("1.for slowest\n");
	gotoxy(10,9);
	printf("2.for slower\n");
	gotoxy(10,11);
	printf("3.for slow\n");
	gotoxy(10,13);
	printf("4.for normal\n");
	gotoxy(10,15);
	printf("5.for fast\n");
	gotoxy(10,17);
	printf("6.for faster\n");
	gotoxy(10,19);
	printf("7.for fastest\n");
	gotoxy(10,21);
	scanf("%d",&choice);
	switch(choice){
		case1:delayspeed=250;break;
		case2:delayspeed=200;break;
		case3:delayspeed=160;break;
		case4:delayspeed=90;break;
		case5:delayspeed=60;break;
		case6:delayspeed=40;break;
		case7:delayspeed=0;break;
	};
	cleardevice();
	randomnumber();
	bar3d(rndx,rndy,rndx+dist,rndy+dist,0,0);
	statusbar();
	while((c=getch())!='\033'){
		if(c=='\115')a=1;
		if(c=='\113')a=2;
		if(c=='\120')a=3;
		if(c=='\110')a=4;
		dash=0;
		move(a);
	}

}