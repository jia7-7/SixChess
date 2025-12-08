#include "head.h"
void printmap()
{
	printf("\n ");
	for(int i=0;i<15;i++)
		printf("%2d",i);
	printf("\n");
	for(int i=0;i<15;i++)
	{
		printf("%2d",i);
		for(int j=0;j<15;j++)
			printf("%c ",map[i][j]);
		printf("\n");
	}
}
void showscore()
{
	printf("\n============== 计分板 ==============\n");
    printf("总对局数: %d\n", total);
    printf("玩家1 (X) 胜利: %d 次\n", p1);
    printf("玩家2 (O) 胜利: %d 次\n", p2);
    printf("平局: %d 次\n", equal);
    printf("====================================\n\n");
}
void pvp()
{
	printf(" -------- 人人对战开始 --------\n");
	showscore();
	startmap();//重置棋盘
	cur=1;//初试为玩家1 
	movecnt=0;
	strcpy(history,"");//清空历史记录 
	bool end=false; 
	while(!end)
	{
		printmap();
		if(cur==1)
			printf("玩家1的回合，请输入坐标（x y）");
		else
			printf("玩家2的回合，请输入坐标（x y）");
		int x,y;
		if(scanf("%d %d",&x,&y)==2)//成功输入了两个数字
		{
			if(checkmove(x,y))
			{
				if(checkwin(x,y))
				{
					printmap();
					printf("恭喜玩家%d获胜\n",cur);
					total++;
					if(cur==1)
						p1++;
					else
						p2++;
					showscore();
					if(cur==1)
						strcpy(result,"玩家1获胜");
					else
						strcpy(result,"玩家2获胜");
					savefile();
					end=true;
				}
				else
				{
					if(cur==1)
						cur=2;
					else
						cur=1;
				}
			}
			else
			{
				while(getchar()!='\n');
			}	
		}	
		else
		{
			printf("输入格式错误！请重新输入");
			while(getchar()!='\n');
		}
		//平局判断 
		bool isequal = true;
        for(int i=0;i<15;i++) 
		{
            for(int j=0;j<15;j++) 
			{
                if(map[i][j]=='.') 
				{
                    isequal=false;
                    break;
                }
            }
        }
        if (isequal&&!end) {
            printmap();
            printf("平局！棋盘已满。\n");
            total++;
            equal++;
            showscore();
            strcpy(result,"平局");
            savefile();
            end=true;
        }
	}
}
int setlevel()
{
	int choice;
	while(1)
	{
		printf("\n=========== AI难度设置 ===========\n");
    	printf("1. 简单模式 \n");
   		printf("2. 困难模式 \n");
    	printf("请选择: ");
    	scanf("%d",&choice);	
    	if(choice==1||choice==2)
    	{
    		if(choice==1)
    		{
    			printf("已经设置为简单模式\n");
    			break;	
			}
    		else
    		{
    			printf("已经设置为困难模式\n");
    			break;
			}
		}
		else
			printf("无效选择，请重新输入1或2"); 
	}
	return choice;
    
}
void ai1()
{
	int x,y;
	x=rand()%15;
	y=rand()%15;
	int attemp=1;
	while(map[x][y]!='.')
	{
		x=rand()%15;
		y=rand()%15;
		attemp++;
		if(attemp>100)//防止一直找不到位置，直接顺序查找空位 
		{
			for(int i=0;i<15;i++)
			{
				for(int j=0;j<15;j++)
				{
					if(map[i][j]=='.')
					{
						map[i][j]='O';
						
						char temp[20];
						sprintf(temp,"O(%d,%d)",i,j);
						strcat(history,temp);
						movecnt++;
						printf("AI落子位置: (%d, %d)\n", i, j);
						return;
					}
				}
			}
		}
	}
	map[x][y]='O';
	char temp[20];
    sprintf(temp,"O(%d,%d)",x,y);
    strcat(history,temp);
    movecnt++;
    printf("AI落子位置: (%d,%d)\n", x, y);
}
int aipos(int x,int y,char player)//评估在该位置放player对player的价值 
{
	if(map[x][y]!='.')
		return 0;
	int score=0;
	int dir[4][2]={{0,1},{1,0},{1,1},{1,-1}};//四个方向 
	for(int d=0;d<4;d++)
	{
		int dx=dir[d][0];
		int dy=dir[d][1];
		// 正向检查
        int cnt=0;
        for (int i=1; i<=5;i++) 
		{
            int nx=x+dx*i;
            int ny=y+dy*i;
            if (nx>=0&&nx<15&&ny>=0&&ny<15) 
			{
                if (map[nx][ny]==player) 
					cnt++;
                else if (map[nx][ny] != '.') 
					break; // 遇到对方棋子或边界
            }
        }
        // 反向检查
        for (int i=1; i<=5;i++) 
		{
            int nx=x-dx*i;
            int ny=y-dy*i;
            if (nx>=0&&nx<15&&ny>=0&&ny<15) 
			{
                if (map[nx][ny]==player) 
					cnt++;
                else if (map[nx][ny] != '.') 
					break; // 遇到对方棋子或边界
            }
        }
        if(cnt>=5)
        	score+=10000;
        else if(cnt==4)
        	score+=1000;
        else if(cnt==3)
        	score+=100;
        else if(cnt==2)
        	score+=10;
        else if(cnt==1)
        	score+=1;
	}
	return score;
}
void ai2()
{
	int bestx=-1,besty=-1,bestscore=-1;
	//遍历每一个 
	for(int i=0;i<15;i++)
	{
		for(int j=0;j<15;j++)
		{
			if(map[i][j]=='.')
			{
				int jingong=aipos(i,j,'O');//ai想要进攻的评估得分 
				int fangshou=aipos(i,j,'X');//ai想要防守的评估得分
				int value=jingong+2*fangshou;//优先考虑防守 
				if(value>bestscore)
				{
					bestscore=value;
					bestx=i;
					besty=j;
				}
			}
		}
	}
	if(bestx!=-1&&besty!=-1)
	{
		map[bestx][besty]='O';
		char temp[20];
		sprintf(temp,"O(%d,%d)",bestx,besty);
		strcat(history,temp);
		movecnt++;
		printf("AI落子位置: (%d,%d)\n",bestx,besty);
	}
	else
		ai1();//找不到合适的位置就随即落子 
}
void pvc()
{
	printf(" -------- 人机对战开始 --------\n");
    printf("当前AI难度: %d\n", ailevel);
    showscore();
    startmap();
    cur=1;
    movecnt=0;
	strcpy(history,"");//清空历史记录 
    bool end=false;
    while(!end)
    {
    	printmap();
    	if(cur==1)
    	{
    		printf("你的回合（X），请输入坐标（x y）:");
    		int x,y;
    		if (scanf("%d %d", &x, &y) == 2) 
			{
                if (checkmove(x,y)) 
				{
                    if (checkwin(x,y)) 
					{
                        printmap();
                        printf("恭喜你获胜！\n");
                        total++;
                        p1++;
                        showscore();
                        strcpy(result,"玩家获胜");
                        savefile();
                        end=true;
                    } 
					else 
                        cur=2; // 切换到AI
                } 
				else 
                   while(getchar()!='\n');
        	}
        	else
			{
				printf("输入格式错误！请重新输入");
				while(getchar()!='\n');
			}
		}
		else
		{
			if(ailevel==1)
				ai1();
			else
				ai2();
			bool aiwin=false;
			//检查AI是否胜利 
			for(int i=0;i<15;i++)
			{
				for(int j=0;j<15;j++)
				{
					if(map[i][j]=='O'&&checkwin(i,j)==true)
					{
						aiwin=true;
						break;
					}
				}
			}
			if(aiwin)
			{
				printmap();
                printf("AI获胜！\n");
                total++;
                p2++;
                showscore();
                strcpy(result,"AI获胜");
                savefile();
                end=true;
			}
			else
				cur=1;
		}
		bool isequal = true;
        for(int i=0;i<15;i++) 
		{
            for(int j=0;j<15;j++) 
			{
                if(map[i][j]=='.') 
				{
                    isequal=false;
                    break;
                }
            }
        }
        if (isequal&&!end) {
            printmap();
            printf("平局！棋盘已满。\n");
            total++;
            equal++;
            showscore();
            strcpy(result,"平局");
            savefile();
            end=true;
        }
	}
}
