#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 60
void Hanoi1(int n,char x,char y, char z);
void Hanoi2(int n,char x,char y, char z);
void PrintHanoi(int no,char from,char to);
typedef struct
{
	char x;
	char y;
	char z;
	int flag;	//标识，为1时表示需要将大问题分解，为0时表示已经变成最小的问题，可以直接移动盘子
	int num;	//当前圆盘数
}Stack;

int main()
{
	int n;
	int i = 1;
	printf("请输入移动圆盘的个数：\n");
	scanf("%d",&n);
	printf("汉诺塔的递归实现：\n");
	Hanoi1(n,'X','Y','Z');
	printf("汉诺塔的非递归实现：\n");
	Hanoi2(n,'A','B','C');

	return 0;
}

void Hanoi1(int n, char x, char y, char z)	//从x移到z，y作辅助
{
	if(1 == n)
		PrintHanoi(n,x,z);
	else
	{
		Hanoi1(n-1,x,z,y);
		PrintHanoi(n,x,y);
		Hanoi1(n-1,y,x,z);
	}
}

void Hanoi2(int n, char x, char y, char z)
{
	int top=1, x1, y1, z1, m;
	Stack s[MAXSIZE];
	s[top].num = n;
	s[top].flag = 1;
	s[top].x = x;
	s[top].y = y;
	s[top].z = z;
	while(top > 0)
	{
		if(s[top].flag == 1)
		{
			//退栈hanoi(n,x,y,z)，相当于在递归函数中将实参传递给形参
			m = s[top].num;
			x1 = s[top].x;
			y1 = s[top].y;
			z1 = s[top].z;
			top--;
			//将hanoi(n-1,x,z,y)入栈，相当于在递归函数中第一个调用函数，将编号
			//为1~n-1的圆盘从塔座x移动到y，z作为辅助塔座
			top++;
			s[top].num = m-1;
			s[top].flag = 1;
			s[top].x = y1;
			s[top].y = x1;
			s[top].z = z1;
			//将第n个圆盘从x移动到z
			top++;
			s[top].num = m;
			s[top].flag = 0;
			s[top].x = x1;
			s[top].y = z1;
			//将hanoi(n-1,y,x,z)入栈，相当于在递归函数中第一个递归调用函数，将编号
			//为1~n-1的圆盘从塔座y移动到z，x作为辅助塔座
			top++;
			s[top].num = m-1;
			s[top].flag = 1;
			s[top].x = x1;
			s[top].y = z1;
			s[top].z = y1;
 		}
		while(top>0 && (s[top].flag==0 || s[top].num==1))
		{
			if(top>0 && s[top].flag == 0)//将第n个盘子从x移动到z，并退栈
			{
				PrintHanoi(s[top].num, s[top].x, s[top].y);
				top--;
			}
			if(top>0 && s[top].num==1)//将第1个盘子从x移动到z，并退栈
			{
				PrintHanoi(s[top].num,s[top].x,s[top].z);
				top--;
			}
		}
	}
}

void PrintHanoi(int no, char from, char to)
{
	printf("将第%d个圆盘从塔座%c移动到%c\n",no,from,to);
}