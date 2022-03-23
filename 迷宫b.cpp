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
	int left=0,right=600,up=0,under=600;//�Թ�������
	char s[]="->",a[]="��" ;
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

int home_show()		//��ʼҳ��
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
		fillrectangle(1*60,0*60,(1+1)*60,(0+1)*60);//���
		fillrectangle(9*60,8*60,(9+1)*60,(8+1)*60);//����

		setfillcolor(RED);
		settextcolor(RGB(255, 255, 17));    //����������ɫ
		settextstyle(60,0, "΢���ź�");   //���������,��(��)��,��(��)��,������
		outtextxy(750,60,"�Թ�");

			setfillcolor(RED);
		settextcolor(RGB(255, 255, 17));    //����������ɫ
		settextstyle(30,0, "΢���ź�");   //���������,��(��)��,��(��)��,������
		outtextxy(700,150,"1.ջѰ���Թ�·��");
			setfillcolor(RED);
		settextcolor(RGB(255, 255, 17));    //����������ɫ
		settextstyle(30,0, "΢���ź�");   //���������,��(��)��,��(��)��,������
		outtextxy(700,250,"2.Ѱ���Թ�����·��");
			setfillcolor(RED);
		//setbkcolor(GREEN);
		settextcolor(RGB(255, 255, 17));    //����������ɫ
		settextstyle(30,0, "΢���ź�");   //���������,��(��)��,��(��)��,������
		outtextxy(700,350,"3.���������Թ�");
			setfillcolor(RED);
	
		_getch();
		do
		{
		char s[10];
		InputBox(s, 10, "�� 0 �Ƴ�","��ѡ��˵����:");

		// ���û�����ת��Ϊ����
		sscanf(s, "%d", &choice);
		}while(choice>3||choice<0);//�ж��Ƿ�������ȷ
	closegraph();
	return choice;
}
//-----------ջʵ��------------

typedef struct
{
	int i;				//��ǰ������к�
	int j;				//��ǰ������к�
	int di;				//di����һ�������ڷ�λ�ķ�λ��
} Box;
typedef struct
{
	Box data[MaxSize];	//��ŷ���
    int top;			//ջ��ָ��
} StType;				//����ջ����

void InitStack(StType *&s)		//��ʼ��ջ
{	s=(StType *)malloc(sizeof(StType));
	s->top=-1;
}
void DestroyStack(StType *&s)	//����ջ
{
	free(s);
}
bool StackEmpty(StType *s)		//�ж�ջ�Ƿ�Ϊ��
{
	return(s->top==-1);
}
bool Push(StType *&s,Box e)	//��ջԪ��e
{
	if (s->top==MaxSize-1)
		return false;
	s->top++;
	s->data[s->top]=e;
	return true;
}
bool Pop(StType *&s,Box &e)	//��ջԪ��e
{
	if (s->top==-1)	
		return false;
	e=s->data[s->top];
	s->top--;
	return true;
}
bool GetTop(StType *s,Box &e)	//ȡջ��Ԫ��e
{
	if (s->top==-1)	
		return false;
	e=s->data[s->top];
	return true;
}
bool mgpath(int xi=1,int yi=1,int xe=8,int ye=8)	//���·��Ϊ:(xi,yi)->(xe,ye)
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
		fillrectangle(1*60,0*60,(1+1)*60,(0+1)*60);//���
		fillrectangle(9*60,8*60,(9+1)*60,(8+1)*60);//����

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

				
					//��������
				settextcolor(RGB(255, 255, 17));    //����������ɫ
				settextstyle(30,0, "΢���ź�");   //���������,��(��)��,��(��)��,������
				outtextxy(720,0,"�Թ�·�����£�");
				settextstyle(25, 18, _T("����"));

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
DestroyStack(st);			//����ջ
	return false;			//��ʾû�п���·��,����false
}
//============�ݹ�ʵ����Ӧ·��========================================
struct migong
{
    int i;      //·��������
    int j;      //·��������
    int di;     //����ֵ��ʼΪ-1��0,1,2,3�ֱ��ʾ�ĸ�Ҫ���ҵķ���
}Stack[MaxSize],Path[MaxSize];      //����ջ�ʹ�����·��������
 
int top= -1;     //ջ��ָ�룬��ʼֵΪ-1
int count= 1;    //·��������
int minlen=0;     //���·������
 
void mgpath2() //·��Ϊ:(1,1)->(M,N)
{     initgraph(width,high); 
    int i,j,di,nextfound,k;
	int min[100]={0},mins[100];	//���·��
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
		fillrectangle(1*60,0*60,(1+1)*60,(0+1)*60);//���
		fillrectangle(9*60,8*60,(9+1)*60,(8+1)*60);//����
	//��ʼ����ջ
    top++;
	Stack[top].i=1;
	Stack[top].j=1;
	Stack[top].di=-1;  //�õ�ĳ�ʼ����ֵ-1����ʾ��û���ҹ��Ӵ˳���������4������
    mg[1][1]=-1;     //-1��ʾ�ýڵ�λ�ý�ջ��(�����������������ʾ)
    while(top> -1) //ջ����ʱѭ��
	{  		
		for(i=0;i<10;i++)
				for(j=0;j<10;j++)
				{if(mg[i][j]==0)
					{setfillcolor(GREEN);	fillrectangle(j*60,i*60,(j+1)*60,(i+1)*60);}
					}
				fillrectangle(1*60,1*60,(1+1)*60,(1+1)*60);
		//1 -----��ȡջ��
        i=Stack[top].i;
		j=Stack[top].j;
		di=Stack[top].di;  //ջ��Ԫ�صĲ��ҷ���
		//z=0;
		//2 -----����ҵ��˳��ڣ�M,N�������������·��������ջ�����µ�ջ������ֵȡ����ǰ�Ĳ��ҷ���
        if(i==8 && j==8) 
		{       
			int m=0,y=1;minlen++;
			for(k=0;k<=top;k++) //���·��
			{
				int a,b;
				a=Stack[k+1].i-Stack[k].i;
				b=Stack[k+1].j-Stack[k].j;
			setfillcolor(RED);
			if(k>0)	line(Stack[k-1].j*60+30,Stack[k-1].i*60+30,Stack[k].j*60+30,Stack[k].i*60+30);	
			fillcircle(Stack[k].j*60+30,Stack[k].i*60+30,20);
			mins[k]=Stack[k].i;

			//��������
				settextcolor(RGB(255, 255, 17));    //����������ɫ
				settextstyle(30,0, "΢���ź�");   //���������,��(��)��,��(��)��,������
				outtextxy(720,0,"�Թ�·�����£�");
				settextstyle(25, 18, _T("����"));

				outtextxy(620+m*150,0+y*40,40);
				outtextxy(650+m*150,0+y*40,Stack[k].i+48);
				outtextxy(680+m*150,0+y*40,",");
				outtextxy(700+m*150,0+y*40,Stack[k].j+48);
				outtextxy(720+m*150,0+y*40,41);
				outtextxy(730+m*150,0+y*40,s);	m++;//�����������
				if(m==2){y++;m=0;}

			Sleep(40);
			setfillcolor(YELLOW);
			fillcircle(Stack[k].j*60+30,Stack[k].i*60+30,20);
			
	       }		
			if(top+1<minlen) //�Ƚ�������·��
			{       
                for(int n=0;n<=top;n++)  
				{
                    Path[n]=Stack[n]; //�������·��
				}
                minlen=top+1;
            }
		
    

            mg[Stack[top].i][Stack[top].j]=0;   //0��ʾ�ø�λ�ñ�Ϊ����·���Ŀ��߽��
			setfillcolor(BLACK);	solidrectangle(610,20,1000,800);//������һ��·��������
			//��Ԫ�س�ջ
            top--;
			di=Stack[top].di;  //��¼��һ�εĲ��ҷ���Ϊ��ջ���ĵĲ��ҷ���	
        }
	
		//3 -------�ڵ�ǰջ���Ļ������ҵ���һ�����߽ڵ㣬�����ǰջ����4�����������ˣ�����ջ���µ�ջ��
        nextfound=0;
        while(di<8 && nextfound==0) //����һ�����߽��
		{     
            di++; //��һ�����ҷ���
            switch(di) //������һ�����ҷ��������
			{
                case 0:	i=Stack[top].i-1;	j=Stack[top].j;		break;   //����
                case 1:	i=Stack[top].i;		j=Stack[top].j+1;	break;   //�ұ�
                case 2:	i=Stack[top].i+1;	j=Stack[top].j;		break;   //����
                case 3:	i=Stack[top].i;		j=Stack[top].j-1;	break;   //���
            }
            if(mg[i][j]==0)  //�����һ�����߽ڵ�û�н�ջ�������findΪ1��ʾ�ҵ�����һ�����߽ڵ�
			{
                nextfound=1;
			}
        }
 
        if(nextfound == 1) //�ӵ�ǰջ�����ҵ�����һ�����߽��
		{      
            Stack[top].di=di;   //����ջ��Ԫ�ص�diֵΪ���µĲ��ҷ���
			
			//��һ�����߽���ջ
            top++;
            Stack[top].i=i;
            Stack[top].j=j;
            Stack[top].di=-1;
            mg[i][j]=-1;
        }
		else  //�����ǰջ����4�������Ѿ�������
		{
            mg[Stack[top].i][Stack[top].j]=0;   //0��ʾ�ø�λ�ñ�Ϊ����·���Ŀ��߽��
            top--;  //��ǰջ���Ѿ������꣬������ջ
        }
    }
	int n=0,y=1,m=0;

	outtextxy(720,0,"���·�����£�");
	//getch();
	do	//for(int n=0,y=1,m=0;n<minlen;)
	{
	
			setfillcolor(YELLOW);
			if(n>0)	line(Path[n-1].j*60+30,Path[n-1].i*60+30,Path[n].j*60+30,Path[n].i*60+30);	
			fillcircle(Path[n].j*60+30,Path[n].i*60+30,20);
				settextstyle(25, 18, _T("����"));
			
				outtextxy(620+m*150,0+y*40,40);
				outtextxy(650+m*150,0+y*40,Path[n].i+48);
				outtextxy(680+m*150,0+y*40,",");
				outtextxy(700+m*150,0+y*40,Path[n].j+48);
				outtextxy(720+m*150,0+y*40,41);
				if(Path[n].j==8&&Path[n].i==8)break;
					else
				outtextxy(730+m*150,0+y*40,s);	m++;//�����������
				if(m==2){y++;m=0;}
			n++;
    }while(n<minlen||Path[n].j==8&&Path[n].i==8);
		
}
//==============================================
int main()
{
	mciSendString("open bkmusic.mp3 alias bkmusic",NULL,0,NULL);
	mciSendString("play bkmusic repeat",NULL,0,NULL);
	int choice;//��¼ѡ��
	initgraph(width,high);
	SetConsoleTitle("�Թ�");	
	do
	{
		choice=home_show();//��ҳ�棬���ڻ�ȡ�û�ѡ��
		switch(choice)//����ѡ�������Ӧ����
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