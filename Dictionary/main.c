#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include "function.h"
#include "dictionary.c"  


int main(int argc,char **argv)
{
    printf("\033[;36;5m ******************************************** \033[0m\n");
    printf("\033[;36;5m *               ���Ӵʵ���Ŀ               * \033[0m\n");
    printf("\033[;36;5m ******************************************** \033[0m\n");
    printf("\033[;36;5m *     1. ע��     2. ��¼     3. �˳�      * \033[0m\n");
    printf("\033[;36;5m ******************************************** \033[0m\n");
    int choice,flag;
    char FILENAME[20]="user.txt";
    read(user,&numofuser,FILENAME);
    printf("�����룺");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:sign_in(&numofuser,FILENAME,user);
        break;
    case 2:login(&numofuser,user);
        break;
    case 3:printf("\033[;31;5m   �����˳�����ӭ���ٴ�ʹ�ã�  \033[0m\n");
        break;
    default:printf("\033[;31;5m   ����������������룡����  \033[0m\n");
        break;
    }

    return 0;
}

//ͳ�ƺ���
void read(struct userlist user[],int *numofuser,char filename[]){
    FILE *fp;
    fp=fopen(filename,"r");
    if(fp!=NULL){
        while(!feof(fp)){
            fscanf(fp,"%s %s %d",&user[*numofuser].name,&user[*numofuser].pwd,&user[*numofuser].numofmemwd);
            (*numofuser)++;
        }
    }else{
        printf("\033[;31;5m�ļ���ȡʧ�ܣ����� \033[0m\n");
    }
    fclose(fp);
}

//ע�ắ��
void sign_in(int *numofuser,char filename[],struct userlist user[]){
    char keyn[10],keyp1[20],keyp2[20];
    printf("�û�����");
    scanf("%s",&keyn);
    for(int i=0;i<*numofuser;i++){
        if(strcmp(user[i].name,keyn)==0){
            printf("\033[;31;5m    ���û��Ѿ�ע��,���¼��\033[0m\n");
            sign_in(&(*numofuser),filename,user);
            return;
        }
    }
    printf("��  �룺");
    int i = 0;
    char c;
	while (1)
	{
		//getch()���������һ�������Ժ��������û�����ĳ���ַ�ʱ�������Զ���ȡ�����谴�س�
		//������;���ӿ���̨��ȡһ���ַ���������ʾ����Ļ��
		c = getch();
        //�������Esc�������˳�
        if((c-48) == (-21)){
            printf("\n\033[;31;1m      �˳��ɹ���     \033[0m\n");
                return;
        }
		//windowsƽ̨�°��»س���ENTER�������������ת���ַ� \r\n�����getch����13(\r)��
		//				��'\n���ĵ�ת���ַ��޷���ȡ������޷�ͨ���ж�'\n'�ķ�ʽ�������룬
		//����ͨ����ȡ��һ��ת���ַ������жϽ�������
		if (c == '\r')//���»س���ʱ�������룬�˳�
		{
			keyp1[i] = '\0';
			break;
		}
		if (c == '\b')//�����˸��ʱ����Backsapce)
		{
			//��û����������ʱ�������������Ϊ��ʱ���������κβ���
			//����������벻Ϊ��ʱ������ʾ���ַ������˸�
			if (i > 0) 
			{ 
				i--;
				//����ʾ���ַ������˸�����\b֮�����һ���ո�
				printf("\b \b");
						
				keyp1[i] = '\0';//�޸�������ַ�
				continue;
			}
		}
		else//û�������س���ʱ���˸��ʱ����ȡ���������洢���ַ���password��
		{
			printf("*");	//������������ڿ���̨��ʾ*��
			keyp1[i] = c;//�洢������ַ�		
			if (i < 20) i++;
            else break;
		}
	}
    printf("\n");
	if (i > 0) ;
	else  printf("���������Ϊ��");
    printf("��ȷ������");
    int j = 0;
    char d;
	while (1)
	{
		d = getch();
        if((d-48) == (-21)){
            printf("\n\033[;31;1m      �˳��ɹ���     \033[0m\n");
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
	else  printf("���������Ϊ��");
    if(strcmp(keyp1,keyp2)!=0){
        printf("\033[;31;5m   �����������벻һ�£�����������! \033[0m\n");
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
        printf("�ļ���ʧ��\n");
    }
    fclose(fp);
    printf("\n\033[;31;5m      %s,��ϲ����ע��ɹ�\033[0m\n",keyn);
    printf("�����µ�¼��\n");
    login(&(*numofuser),user);
    flag=1;      
    if(flag==0){
        printf("\033[;31;5mע��ʧ��!!!\033[0m\n");
    }
}

//��¼����
void login(int *numofuser,struct userlist user[]){
    char keyn[10],keyp[20];
    while(1){
        printf("�û�����");
        scanf("%s",keyn);
        printf("��  �룺");
        int i = 0,flag=0;
        char c;
	    while (1)
	    {
		    c = getch();
            if((c-48) == (-21)){
                printf("\n\033[;31;1m      �˳��ɹ���     \033[0m\n");
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
	    else  printf("���������Ϊ��");
        for(int i=0;i<*numofuser;i++){
            if(strcmp(keyn,user[i].name)==0&&strcmp(keyp,user[i].pwd)==0){
                printf("\n\033[;31;1m      %s,��ϲ������¼�ɹ�! \033[0m\n",keyn);
                flag=1;
                fakemain(user[i].name);
                return;
            }
        }
        if(flag==0){
            printf("\033[;31;5m     �û����������������������!!! \033[0m\n");
        
        }
    } 
}