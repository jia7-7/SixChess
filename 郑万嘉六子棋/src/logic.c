#include "head.h"
void startmap()
{
	for(int i=0;i<15;i++)
		for(int j=0;j<15;j++)
			map[i][j]='.';
}
bool checkmove(int x,int y)
{
	if(x<0||x>14||y<0||y>14)
	{
		printf("数字超过范围，请重新输入0到14的数字");
		return 0; 
	}
	if(map[x][y]!='.')
	{
		printf("该位置已有棋子，请重新输入坐标");
		return 0; 
	}
	if(cur==1)
		map[x][y]='X';
	else
		map[x][y]='O'; 
	char temp[20];
	if(cur==1)
		sprintf(temp,"X(%d,%d)",x,y);
	else
		sprintf(temp,"O(%d,%d)",x,y);
	strcat(history,temp); 
	movecnt++;
	return 1;
}
bool checkwin(int x,int y)
{
	int cnt=1;
	char tmp=map[x][y];
	for(int i=1;i<=5;i++)//向右 
	{
		if(y+i<=14&&map[x][y+i]==tmp)
			cnt++;
		else
			break;
	}
	for(int i=1;i<=5;i++)//向左 
	{
		if(y-i>=0&&map[x][y-i]==tmp)
			cnt++;
		else
			break;
	}
	if(cnt>=6)
		return 1;
	cnt=1;
	for(int i=1;i<=5;i++)//向下 
	{
		if(x+i<=14&&map[x+i][y]==tmp)
			cnt++;
		else
		 	break;
	}
	for(int i=1;i<=5;i++)//向上 
	{
		if(x-i>=0&&map[x-i][y]==tmp)
			cnt++;
		else
			break;
	}
	if(cnt>=6)
		return 1;
	cnt=1;
	for(int i=1;i<=5;i++)//右下对角线 
	{
		if(x+i<=14&&y+i<=14&&map[x+i][y+i]==tmp)
			cnt++;
		else
			break;
	}
	for(int i=1;i<=5;i++)
	{
		if(x-i>=0&&y-i>=0&&map[x-i][y-i]==tmp)
			cnt++;
		else
			break;
	}
	if(cnt>=6)
		return 1;
	cnt=1;
	for(int i=1;i<=5;i++)//右上对角线 
	{
		if(x-i>=0&&y+i<=14&&map[x-i][y+i]==tmp)
			cnt++;
		else
			break;
	}
	for(int i=1;i<=5;i++)
	{
		if(x+i<=14&&y-i>=0&&map[x+i][y-i]==tmp)
			cnt++;
		else
			break;
	}
	if(cnt>=6)
		return 1;
	return 0;
}
