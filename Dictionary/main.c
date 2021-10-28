#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include "function.h"
#include "dictionary.c"  


int main(int argc,char **argv)
{
    printf("\033[;36;5m ******************************************** \033[0m\n");
    printf("\033[;36;5m *               电子词典项目               * \033[0m\n");
    printf("\033[;36;5m ******************************************** \033[0m\n");
    printf("\033[;36;5m *     1. 注册     2. 登录     3. 退出      * \033[0m\n");
    printf("\033[;36;5m ******************************************** \033[0m\n");
    int choice,flag;
    char FILENAME[20]="user.txt";
    read(user,&numofuser,FILENAME);
    printf("请输入：");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:sign_in(&numofuser,FILENAME,user);
        break;
    case 2:login(&numofuser,user);
        break;
    case 3:printf("\033[;31;5m   即将退出，欢迎您再次使用！  \033[0m\n");
        break;
    default:printf("\033[;31;5m   输入错误，请重新输入！！！  \033[0m\n");
        break;
    }

    return 0;
}

//统计函数
void read(struct userlist user[],int *numofuser,char filename[]){
    FILE *fp;
    fp=fopen(filename,"r");
    if(fp!=NULL){
        while(!feof(fp)){
            fscanf(fp,"%s %s %d",&user[*numofuser].name,&user[*numofuser].pwd,&user[*numofuser].numofmemwd);
            (*numofuser)++;
        }
    }else{
        printf("\033[;31;5m文件读取失败！！！ \033[0m\n");
    }
    fclose(fp);
}

//注册函数
void sign_in(int *numofuser,char filename[],struct userlist user[]){
    char keyn[10],keyp1[20],keyp2[20];
    printf("用户名：");
    scanf("%s",&keyn);
    for(int i=0;i<*numofuser;i++){
        if(strcmp(user[i].name,keyn)==0){
            printf("\033[;31;5m    该用户已经注册,请登录！\033[0m\n");
            sign_in(&(*numofuser),filename,user);
            return;
        }
    }
    printf("密  码：");
    int i = 0;
    char c;
	while (1)
	{
		//getch()这个函数是一个不回显函数，当用户按下某个字符时，函数自动读取，无需按回车
		//函数用途：从控制台读取一个字符，但不显示在屏幕上
		c = getch();
        //如果按下Esc键可以退出
        if((c-48) == (-21)){
            printf("\n\033[;31;1m      退出成功！     \033[0m\n");
                return;
        }
		//windows平台下按下回车（ENTER）键会产生两个转义字符 \r\n，因此getch返回13(\r)，
		//				而'\n‘的的转义字符无法读取，因此无法通过判断'\n'的方式结束输入，
		//可以通过读取第一个转义字符进行判断结束输入
		if (c == '\r')//按下回车键时结束输入，退出
		{
			keyp1[i] = '\0';
			break;
		}
		if (c == '\b')//遇到退格键时（←Backsapce)
		{
			//当没有输入密码时，即输入的密码为空时，不进行任何操作
			//即输入的密码不为空时，对显示的字符进行退格
			if (i > 0) 
			{ 
				i--;
				//对显示的字符进行退格，两个\b之间存在一个空格
				printf("\b \b");
						
				keyp1[i] = '\0';//修改输入的字符
				continue;
			}
		}
		else//没有遇到回车键时和退格键时，读取输入的密码存储在字符串password中
		{
			printf("*");	//对输入的密码在控制台显示*号
			keyp1[i] = c;//存储输入的字符		
			if (i < 20) i++;
            else break;
		}
	}
    printf("\n");
	if (i > 0) ;
	else  printf("输入的密码为空");
    printf("请确认密码");
    int j = 0;
    char d;
	while (1)
	{
		d = getch();
        if((d-48) == (-21)){
            printf("\n\033[;31;1m      退出成功！     \033[0m\n");
            return;
        }
		if (d == '\r')
		{
			keyp2[j] = '\0';
			break;
		}
		if (d == '\b')
		{
			if (j > 0) 
			{ 
				j--;
				printf("\b \b");	
				keyp2[j] = '\0';
				continue;
			}
		}
		else
		{
			printf("*");
			keyp2[j] = d;	
			if (j < 20) j++;
            else break;
		}
	}
     
	printf("\n");
	if (j > 0) ;
	else  printf("输入的密码为空");
    if(strcmp(keyp1,keyp2)!=0){
        printf("\033[;31;5m   两次输入密码不一致，请重新输入! \033[0m\n");
        sign_in(&(*numofuser),filename,user);
    }
    int flag=0;   
    strcpy(user[*numofuser].name,keyn);
    strcpy(user[*numofuser].pwd,keyp1);
    user[*numofuser].numofmemwd=0;
    (*numofuser)++;
    FILE *fp;
    fp=fopen(filename,"w");
    if(fp!=NULL){
        for(int k=0;k<(*numofuser)-1;k++){
            fprintf(fp,"%s %s %d\n",user[k].name,user[k].pwd,user[k].numofmemwd);
        }
        fprintf(fp,"%s %s %d",user[*numofuser-1].name,user[*numofuser-1].pwd,user[*numofuser-1].numofmemwd);
    }else{
        printf("文件打开失败\n");
    }
    fclose(fp);
    printf("\n\033[;31;5m      %s,恭喜您，注册成功\033[0m\n",keyn);
    printf("请重新登录！\n");
    login(&(*numofuser),user);
    flag=1;      
    if(flag==0){
        printf("\033[;31;5m注册失败!!!\033[0m\n");
    }
}

//登录函数
void login(int *numofuser,struct userlist user[]){
    char keyn[10],keyp[20];
    while(1){
        printf("用户名：");
        scanf("%s",keyn);
        printf("密  码：");
        int i = 0,flag=0;
        char c;
	    while (1)
	    {
		    c = getch();
            if((c-48) == (-21)){
                printf("\n\033[;31;1m      退出成功！     \033[0m\n");
                return;
            }
		    if (c == '\r')
		    {
			    keyp[i] = '\0';
			    break;
		    }
		    if (c == '\b')
		    {
			    if (i > 0) 
			    { 
				    i--;
				    printf("\b \b");	
				    keyp[i] = '\0';
				    continue;
			    }
		    }
		    else
		    {
			    printf("*");
			    keyp[i] = c;	
			    if (i < 20) i++;
                else break;
		    }
	    }
	    printf("\n");
	    if (i > 0) ;
	    else  printf("输入的密码为空");
        for(int i=0;i<*numofuser;i++){
            if(strcmp(keyn,user[i].name)==0&&strcmp(keyp,user[i].pwd)==0){
                printf("\n\033[;31;1m      %s,恭喜您，登录成功! \033[0m\n",keyn);
                flag=1;
                fakemain(user[i].name);
                return;
            }
        }
        if(flag==0){
            printf("\033[;31;5m     用户名或密码错误，请重新输入!!! \033[0m\n");
        
        }
    } 
}