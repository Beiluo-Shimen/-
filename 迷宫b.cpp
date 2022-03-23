#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<graphics.h>
#include<conio.h>
#pragma comment(lib,"Winmm.lib")
#define MaxSize 100
#define width 1000
#define high 600
	int left=0,right=600,up=0,under=600;//迷宫的四周
	char s[]="->",a[]="，" ;
	int mg[10][10]=
{	
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,1,0,0,0,1,0,1},
	{1,0,0,1,0,0,0,1,0,1},
	{1,0,0,0,0,1,1,1,0,1},
	{1,0,1,1,1,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,1},
	{1,0,1,0,0,0,1,0,0,1},
	{1,0,1,1,1,0,1,1,0,1},
	{1,1,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}
};

int home_show()		//开始页面
{initgraph(width,high);
	setfillcolor(GREEN);
	fillrectangle(0,0,600,600);

	int choice,i,j;

	for(i=1;i<10;i++)
		line(left,up+i*60,right,up+i*60);
	for(j=1;j<10;j++)
		line(j*60,0,j*60,600);
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
		{if(mg[i][j]==1)
		{setfillcolor(RED);	fillrectangle(j*60,i*60,(j+1)*60,(i+1)*60);}
		}
		setfillcolor(RGB(52,222,220));
		fillrectangle(1*60,0*60,(1+1)*60,(0+1)*60);//入口
		fillrectangle(9*60,8*60,(9+1)*60,(8+1)*60);//出口

		setfillcolor(RED);
		settextcolor(RGB(255, 255, 17));    //设置字体颜色
		settextstyle(60,0, "微软雅黑");   //设置字体的,宽(粗)度,高(长)度,和字体
		outtextxy(750,60,"迷宫");

			setfillcolor(RED);
		settextcolor(RGB(255, 255, 17));    //设置字体颜色
		settextstyle(30,0, "微软雅黑");   //设置字体的,宽(粗)度,高(长)度,和字体
		outtextxy(700,150,"1.栈寻找迷宫路径");
			setfillcolor(RED);
		settextcolor(RGB(255, 255, 17));    //设置字体颜色
		settextstyle(30,0, "微软雅黑");   //设置字体的,宽(粗)度,高(长)度,和字体
		outtextxy(700,250,"2.寻找迷宫所有路径");
			setfillcolor(RED);
		//setbkcolor(GREEN);
		settextcolor(RGB(255, 255, 17));    //设置字体颜色
		settextstyle(30,0, "微软雅黑");   //设置字体的,宽(粗)度,高(长)度,和字体
		outtextxy(700,350,"3.重新设置迷宫");
			setfillcolor(RED);
	
		_getch();
		do
		{
		char s[10];
		InputBox(s, 10, "按 0 推出","请选择菜单编号:");

		// 将用户输入转换为数字
		sscanf(s, "%d", &choice);
		}while(choice>3||choice<0);//判断是否输入正确
	closegraph();
	return choice;
}
//-----------栈实现------------

typedef struct
{
	int i;				//当前方块的行号
	int j;				//当前方块的列号
	int di;				//di是下一可走相邻方位的方位号
} Box;
typedef struct
{
	Box data[MaxSize];	//存放方块
    int top;			//栈顶指针
} StType;				//定义栈类型

void InitStack(StType *&s)		//初始化栈
{	s=(StType *)malloc(sizeof(StType));
	s->top=-1;
}
void DestroyStack(StType *&s)	//销毁栈
{
	free(s);
}
bool StackEmpty(StType *s)		//判断栈是否为空
{
	return(s->top==-1);
}
bool Push(StType *&s,Box e)	//进栈元素e
{
	if (s->top==MaxSize-1)
		return false;
	s->top++;
	s->data[s->top]=e;
	return true;
}
bool Pop(StType *&s,Box &e)	//出栈元素e
{
	if (s->top==-1)	
		return false;
	e=s->data[s->top];
	s->top--;
	return true;
}
bool GetTop(StType *s,Box &e)	//取栈顶元素e
{
	if (s->top==-1)	
		return false;
	e=s->data[s->top];
	return true;
}
bool mgpath(int xi=1,int yi=1,int xe=8,int ye=8)	//求解路径为:(xi,yi)->(xe,ye)
{
	initgraph(width,high);
	setfillcolor(GREEN);
	fillrectangle(0,0,600,600);

	Box path[MaxSize],e;
	int i,j,di,i1,j1,k;
	bool find;

	StType *st;
	InitStack(st);
	
		for(i=0;i<10;i++)
		line(left,up+i*60,right,up+i*60);
	for(j=0;j<10;j++)
		line(j*60,0,j*60,600);
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
		{if(mg[i][j]==1)
		{setfillcolor(RED);	fillrectangle(j*60,i*60,(j+1)*60,(i+1)*60);}
		}
		setfillcolor(RGB(52,222,220));
		fillrectangle(1*60,0*60,(1+1)*60,(0+1)*60);//入口
		fillrectangle(9*60,8*60,(9+1)*60,(8+1)*60);//出口

	e.i=xi;e.j=yi;e.di=-1;
	Push(st,e);
	mg[xi][yi]=-1;
	while(!StackEmpty(st))
	{
		GetTop(st,e);
		i=e.i;j=e.j;di=e.di;
		if(i==xe&&j==ye)
		{
			k=0;
			while(!StackEmpty(st))
			{
				Pop(st,e);
				path[k++]=e;
			}
			int y=1,m=0;
			while(k>=1)
			{	k--;
			setfillcolor(YELLOW);
			setlinecolor(RGB(0,0,200));
			if(k>=1) line(path[k-1].j*60+30,path[k-1].i*60+30,path[k].j*60+30,path[k].i*60+30);	
			fillcircle(path[k].j*60+30,path[k].i*60+30,20);

				
					//坐标的输出
				settextcolor(RGB(255, 255, 17));    //设置字体颜色
				settextstyle(30,0, "微软雅黑");   //设置字体的,宽(粗)度,高(长)度,和字体
				outtextxy(720,0,"迷宫路径如下：");
				settextstyle(25, 18, _T("宋体"));

				outtextxy(620+m*150,0+y*40,40);
				outtextxy(650+m*150,0+y*40,path[k].i+48);
				outtextxy(680+m*150,0+y*40,a);
				outtextxy(700+m*150,0+y*40,path[k].j+48);
				outtextxy(720+m*150,0+y*40,41);
				if(k>=1) outtextxy(730+m*150,0+y*40,s);
				m++;
				if(m==2){y++;m=0;}

				Sleep(100); mg[path[k].i][path[k].j]=0;
			
			}
			DestroyStack(st);getch();
			return true;
		}
		find=false;
		while(di<4&&!find)
		{
			di++;
			switch(di)
			{
			case 0:i1=i-1;j1=j;break;
			case 1:i1=i;j1=j+1;break;
			case 2:i1=i+1;j1=j;break;
			case 3:i1=i;j1=j-1;break;
			}
			if(mg[i1][j1]==0)find=true;
		}
		if(find)
		{
			st->data[st->top].di=di;
			e.i=i1;e.j=j1;e.di=-1;
			Push(st,e);
			mg[i1][j1]=-1;
		}
		else
		{Pop(st,e);
		mg[e.i][e.j]=0;
		}

	}
DestroyStack(st);			//销毁栈
	return false;			//表示没有可走路径,返回false
}
//============递归实现相应路径========================================
struct migong
{
    int i;      //路径横坐标
    int j;      //路径纵坐标
    int di;     //方向值初始为-1，0,1,2,3分别表示四个要查找的方向
}Stack[MaxSize],Path[MaxSize];      //定义栈和存放最短路径的数组
 
int top= -1;     //栈顶指针，初始值为-1
int count= 1;    //路径数计数
int minlen=0;     //最短路径长度
 
void mgpath2() //路径为:(1,1)->(M,N)
{     initgraph(width,high); 
    int i,j,di,nextfound,k;
	int min[100]={0},mins[100];	//最短路径
	//setlinecolor(BLACK);
	for(i=0;i<10;i++)
		line(left,up+i*60,right,up+i*60);
	for(j=0;j<10;j++)
		line(j*60,0,j*60,600);
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
		{if(mg[i][j]==1)
		{setfillcolor(RED);	fillrectangle(j*60,i*60,(j+1)*60,(i+1)*60);}
		}
		setfillcolor(RGB(52,222,220));
		fillrectangle(1*60,0*60,(1+1)*60,(0+1)*60);//入口
		fillrectangle(9*60,8*60,(9+1)*60,(8+1)*60);//出口
	//初始结点进栈
    top++;
	Stack[top].i=1;
	Stack[top].j=1;
	Stack[top].di=-1;  //该点的初始方向值-1，表示还没查找过从此出发的其他4个方向
    mg[1][1]=-1;     //-1表示该节点位置进栈过(最好用其他数组来标示)
    while(top> -1) //栈不空时循环
	{  		
		for(i=0;i<10;i++)
				for(j=0;j<10;j++)
				{if(mg[i][j]==0)
					{setfillcolor(GREEN);	fillrectangle(j*60,i*60,(j+1)*60,(i+1)*60);}
					}
				fillrectangle(1*60,1*60,(1+1)*60,(1+1)*60);
		//1 -----获取栈顶
        i=Stack[top].i;
		j=Stack[top].j;
		di=Stack[top].di;  //栈顶元素的查找方向
		//z=0;
		//2 -----如果找到了出口（M,N），则输出查找路径，并退栈，用新的栈顶方向值取代当前的查找方向
        if(i==8 && j==8) 
		{       
			int m=0,y=1;minlen++;
			for(k=0;k<=top;k++) //输出路径
			{
				int a,b;
				a=Stack[k+1].i-Stack[k].i;
				b=Stack[k+1].j-Stack[k].j;
			setfillcolor(RED);
			if(k>0)	line(Stack[k-1].j*60+30,Stack[k-1].i*60+30,Stack[k].j*60+30,Stack[k].i*60+30);	
			fillcircle(Stack[k].j*60+30,Stack[k].i*60+30,20);
			mins[k]=Stack[k].i;

			//坐标的输出
				settextcolor(RGB(255, 255, 17));    //设置字体颜色
				settextstyle(30,0, "微软雅黑");   //设置字体的,宽(粗)度,高(长)度,和字体
				outtextxy(720,0,"迷宫路径如下：");
				settextstyle(25, 18, _T("宋体"));

				outtextxy(620+m*150,0+y*40,40);
				outtextxy(650+m*150,0+y*40,Stack[k].i+48);
				outtextxy(680+m*150,0+y*40,",");
				outtextxy(700+m*150,0+y*40,Stack[k].j+48);
				outtextxy(720+m*150,0+y*40,41);
				outtextxy(730+m*150,0+y*40,s);	m++;//输出个数计算
				if(m==2){y++;m=0;}

			Sleep(40);
			setfillcolor(YELLOW);
			fillcircle(Stack[k].j*60+30,Stack[k].i*60+30,20);
			
	       }		
			if(top+1<minlen) //比较输出最短路径
			{       
                for(int n=0;n<=top;n++)  
				{
                    Path[n]=Stack[n]; //保存最短路径
				}
                minlen=top+1;
            }
		
    

            mg[Stack[top].i][Stack[top].j]=0;   //0表示让该位置变为其他路径的可走结点
			setfillcolor(BLACK);	solidrectangle(610,20,1000,800);//覆盖上一条路径的坐标
			//让元素出栈
            top--;
			di=Stack[top].di;  //记录下一次的查找方向为新栈顶的的查找方向	
        }
	
		//3 -------在当前栈顶的基础上找到下一个可走节点，如果当前栈顶的4个方向都走完了，则退栈找新的栈顶
        nextfound=0;
        while(di<8 && nextfound==0) //找下一个可走结点
		{     
            di++; //下一个查找方向
            switch(di) //计算下一个查找方向的坐标
			{
                case 0:	i=Stack[top].i-1;	j=Stack[top].j;		break;   //上面
                case 1:	i=Stack[top].i;		j=Stack[top].j+1;	break;   //右边
                case 2:	i=Stack[top].i+1;	j=Stack[top].j;		break;   //下面
                case 3:	i=Stack[top].i;		j=Stack[top].j-1;	break;   //左边
            }
            if(mg[i][j]==0)  //如果下一个可走节点没有进栈过，标记find为1表示找到了下一个可走节点
			{
                nextfound=1;
			}
        }
 
        if(nextfound == 1) //从当前栈顶上找到了下一个可走结点
		{      
            Stack[top].di=di;   //更新栈顶元素的di值为最新的查找方向
			
			//下一个可走结点进栈
            top++;
            Stack[top].i=i;
            Stack[top].j=j;
            Stack[top].di=-1;
            mg[i][j]=-1;
        }
		else  //如果当前栈顶的4个方向都已经查找完
		{
            mg[Stack[top].i][Stack[top].j]=0;   //0表示让该位置变为其他路径的可走结点
            top--;  //当前栈顶已经查找完，让它出栈
        }
    }
	int n=0,y=1,m=0;

	outtextxy(720,0,"最短路径如下：");
	//getch();
	do	//for(int n=0,y=1,m=0;n<minlen;)
	{
	
			setfillcolor(YELLOW);
			if(n>0)	line(Path[n-1].j*60+30,Path[n-1].i*60+30,Path[n].j*60+30,Path[n].i*60+30);	
			fillcircle(Path[n].j*60+30,Path[n].i*60+30,20);
				settextstyle(25, 18, _T("宋体"));
			
				outtextxy(620+m*150,0+y*40,40);
				outtextxy(650+m*150,0+y*40,Path[n].i+48);
				outtextxy(680+m*150,0+y*40,",");
				outtextxy(700+m*150,0+y*40,Path[n].j+48);
				outtextxy(720+m*150,0+y*40,41);
				if(Path[n].j==8&&Path[n].i==8)break;
					else
				outtextxy(730+m*150,0+y*40,s);	m++;//输出个数计算
				if(m==2){y++;m=0;}
			n++;
    }while(n<minlen||Path[n].j==8&&Path[n].i==8);
		
}
//==============================================
int main()
{
	mciSendString("open bkmusic.mp3 alias bkmusic",NULL,0,NULL);
	mciSendString("play bkmusic repeat",NULL,0,NULL);
	int choice;//记录选择
	initgraph(width,high);
	SetConsoleTitle("迷宫");	
	do
	{
		choice=home_show();//主页面，用于获取用户选择
		switch(choice)//根据选择进入相应功能
		{
		case 1:   
				mgpath(1,1,8,8);
				break;     
		case 2:   			
		mgpath2();
				_getch();
			break;  
		case 3:   
			int i=1,j=1;
			do{
					for(i=1;i<9;i++)
						for(j=1;j<9;j++)
						mg[i][j]=rand()%2;Sleep(300);
				}while(!mgpath(1,1,8,8));		
			break;   
	
			}
	}while(choice!=0);
	mciSendString("close bkmusic",NULL,0,NULL);
	closegraph();
	return 0;
}