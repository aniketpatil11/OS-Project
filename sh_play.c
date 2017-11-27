#include "sh_play.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char mat[3][3];
void print()
{
	int i=0,j=0;
	for(i=0;i<3;i++)
	{	for(j=0;j<3;j++)
			printf("%c|",mat[i][j]);
		printf("\n");
	}
}
int check()
{
	if((mat[0][0]=='x' && mat[0][1]=='x'&& mat[0][2]=='x')||(mat[1][0]=='x' && mat[1][1]=='x'&& mat[1][2]=='x')||(mat[2][0]=='x' && mat[2][1]=='x'&& mat[2][1]=='x')||
		(mat[0][0]=='x' && mat[1][0]=='x'&& mat[2][0]=='x')||(mat[0][0]=='x' && mat[1][1]=='x'&& mat[2][2]=='x')||(mat[0][2]=='x' && mat[1][1]=='x'&& mat[2][0]=='x')||(mat[0][1]=='x' && mat[1][1]=='x'&& mat[2][1]=='x')||(mat[0][2]=='x' && mat[1][2]=='x'&& mat[2][2]=='x'))
	return 1;
	if((mat[0][0]=='o' && mat[0][1]=='o'&& mat[0][2]=='o')||(mat[1][0]=='o' && mat[1][1]=='o'&& mat[1][2]=='o')||(mat[2][0]=='o' && mat[2][1]=='o'&& mat[2][1]=='o')||
		(mat[0][0]=='o' && mat[1][0]=='o'&& mat[2][0]=='o')||(mat[0][0]=='o' && mat[1][1]=='o'&& mat[2][2]=='o')||(mat[0][2]=='o' && mat[1][1]=='o'&& mat[2][0]=='o')||(mat[0][1]=='o' && mat[1][1]=='o'&& mat[2][1]=='o')||(mat[0][2]=='o' && mat[1][2]=='o'&& mat[2][2]=='o'))
	return 2;
return 0;
}
int move(int ch,char player)
{
	int i,j,c=0,flag=0;//printf("%d\n",ch);
	if(player=='x')
	{if(ch<1 || ch>9){printf("Invalid move");return -1;}
	//int i=0,j=0,c=0;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			c++;
		if(c==ch){flag=1;break;}
		}
		if(flag==1)break;
	}
	if(mat[i][j] != ' '){printf("Position occupied");return -1;}
	mat[i][j]=player;}
	else 
	{ 
		for(i=0;i<3;i++)
		{
		for(j=0;j<3;j++)
		{
			c++;
		if(c==ch){flag=1;break;}
		}
		if(flag==1)break;
		}
	if(mat[i][j] != ' '){return -1;}
	mat[i][j]='o';
	}
	return 1;
}
int sh_play(char **args)
{
	int ch,res,i,j;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			mat[i][j]=' ';
	int stat=-1;
	while(1)
	{
		print();stat=-1;
		while(stat==-1)
		{
			printf("Enter cell number\n");
			scanf("%d",&ch);
			stat=move(ch,'x');
		}
		stat=-1;
		res=check();
		if(res==1){print();printf("You won\n");break;}
		while(stat==-1)
		{
			ch=rand()%9;
			stat=move(ch,'o');
		}
		printf("I choose %d\n",ch);
		res=check();
		if(res==2){printf("You lost\n");break;}
	}
return 1;
}
