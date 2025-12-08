#include "head.h"
void savefile()
{
	FILE *file=fopen("result.txt","a");
	if(file==NULL)
	{
		printf("保存失败！\n");
		return;
	}
	fprintf(file,"%s 步数:%d 棋谱:%s\n",result,movecnt,history);
	fclose(file);
	printf("记录已保存！\n");
	saveCSV();
}
void showresult()
{
	printf("\n=========== 历史记录 ===========\n");
	FILE *file=fopen("result.txt","r");
	if(file==NULL)
	{
		printf("还没有任何记录！\n");
		printf("================================\n");
        return;
	}
	char l[100];
	int count=0;
	while(fgets(l,sizeof(l),file)!=NULL)
	{
		count++;
		printf("%d.%s",count,l);
	}
	fclose(file);
	printf("================================\n");
}
void saveCSV() {
    FILE *file=fopen("csvresult.csv", "a");  
    if (file==NULL) 
	{
        printf("创建CSV文件失败！\n");
        return;
    }     
    if(total==1)//表头 
    	fprintf(file, "游戏编号,结果,步数,棋谱\n"); 
    fprintf(file, "%d,%s,%d,%s\n", total, result, movecnt, history);
    fclose(file);
    printf("对局信息已保存为CSV格式！\n");
}

void showCSV() {
    printf("\n=========== CSV格式对局信息 ===========\n");
    FILE *file = fopen("csvresult.csv", "r");
    if (file == NULL) {
        printf("没有找到CSV格式的对局记录！\n");
        printf("=====================================\n");
        return;
    }
    char l[200];
    int count = 0;
    while (fgets(l, sizeof(l), file) != NULL) {
        count++;
        printf("%s", l);
    }
    fclose(file);
    printf("总共 %d 条记录\n", count-1);//减去表头那一行 
    printf("=====================================\n");
}
void huifang() {
    printf("\n=========== 对局回放 ===========\n");
    
    FILE *file=fopen("result.txt", "r");
    if (file==NULL) 
	{
        printf("没有找到对局记录！\n");
        return;
    }
    char l[200];
    int count=0;
    while (fgets(l, sizeof(l), file)!=NULL) 
	{
        count++;
        printf("%d. %s", count, l);
    }
    if (count==0) 
	{
        printf("没有可回放的对局！\n");
        fclose(file);
        return;
    }
    fclose(file);
    
    int choice;
    printf("\n请选择要回放的对局编号 (1-%d): ", count);
    scanf("%d", &choice);
    
    if (choice<1||choice>count) 
	{
        printf("无效的选择！\n");
        return;
    }
    
    
    file = fopen("result.txt", "r");
    for (int i=1;i<=choice;i++) 
	{
        fgets(l, sizeof(l), file);
    }
    fclose(file);
    
    char *index=strstr(l, "棋谱:");
    if (index==NULL) 
	{
        printf("无法找到棋谱信息！\n");
        return;
    }
    index+=5; // 跳过"棋谱:"
    
    printf("\n开始回放，按回车逐步查看...\n");
    
    char rmap[15][15];
    for (int i=0;i<15; i++) 
	{
        for (int j=0;j<15;j++) 
            rmap[i][j] = '.';
    }
    
    int step = 0;
    int x,y;
	while (*index&&*index!='\n') 
	{
	    char p=*index;
	    index+=2; // 移动到数字 
        if (sscanf(index,"%d,%d",&x,&y)==2) 
		{
            rmap[x][y] = p;
            step++;
            printf("\n步骤 %d: %c(%d,%d)\n", step, p, x, y);
            printf(" ");
            for (int i=0;i<15;i++)
                printf("%2d", i);
            printf("\n");
            for (int i=0;i<15;i++) 
			{
                printf("%2d", i);
                for (int j=0;j<15;j++)
                    printf("%c ", rmap[i][j]);
                printf("\n");
            }
            printf("按回车继续...");
            getchar(); // 消耗之前输入的回车
            getchar(); // 等待用户按回车
        	}
       		// 找到下一个 ')' 并跳过
        	index = strchr(index, ')');
        	index++;
	}
    
    printf("\n回放结束！\n");
}
