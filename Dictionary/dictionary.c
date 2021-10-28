#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "function.h"

//本文件的主函数
void fakemain(char name[])
{
    struct entry ent[10000];
    int numofwords = 0, choose;
    char FILEPATH[30] = "new_dictionary.txt";
    search(FILEPATH, ent, &numofwords);
    UI(&numofwords, ent, FILEPATH, &choose, name);
    return;
}

//查询有多少个词条的功能函数
void search(char filepath[], struct entry ent[], int *numofwords)
{
    FILE *fp;
    fp = fopen(filepath, "a+");
    if (fp != NULL)
    {
        while (!feof(fp))
        {
            fscanf(fp, "%s %s", &ent[*numofwords].english, &ent[*numofwords].chinese);
            (*numofwords)++;
        }
    }
    else
    {
        printf("\033[;31;5m文件读取失败！！！ \033[0m\n");
    }
    fclose(fp);
}

//英译汉功能函数
void E2C(int *numofwords, struct entry ent[])
{
    char key[20];
    while (1)
    {
        printf("请输入要查询的词(输入0000退出查询)：");
        scanf("%s", key);
        if (strcmp(key, "0000") == 0)
        {
            return;
        }
        int flag = 0;
        for (int i = 0; i < *numofwords; i++)
        {
            if (strcmp(key, ent[i].english) == 0)
            {
                printf("\033[;33;5m\"%s\" 的中文释义为：%s\033[0m\n", ent[i].english, ent[i].chinese);
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            printf("\033[;31;5m查无此词!!!\033[0m\n");
        }
    }
}

//汉译英功能函数
void C2E(int *numofwords, struct entry ent[])
{
    char key[20];
    while (1)
    {
        printf("请输入要查询的词(输入0000退出查询):");
        scanf("%s", key);
        if (strcmp(key, "0000") == 0)
        {
            return;
        }
        int flag = 0;
        for (int i = 0; i < *numofwords; i++)
        {
            if (strstr(ent[i].chinese, key) != NULL)
            {
                printf("\033[;33;5m\"%s\" 对应的英文是：\"%s\"\033[0m\n", ent[i].chinese, ent[i].english);
                flag++;
            }
        }
        if (flag == 0)
        {
            printf("\033[;31;5m查无此词!!!\033[0m\n");
        }
    }
}

//删除词条功能函数
void deleteentry(int *numofwords, struct entry ent[], char filepath[])
{
    char key[20];
    printf("请输入要删去的词(输入0000退出删除):");
    scanf("%s", key);
    if (strcmp(key, "0000") == 0)
    {
        return;
    }
    int flag = 0;
    for (int i = 0; i < *numofwords; i++)
    {
        if (strcmp(key, ent[i].english) == 0)
        {
            for (int j = i; j < (*numofwords) - 1; j++)
            {
                ent[j] = ent[j + 1];
            }
            (*numofwords)--;
            FILE *fp;
            fp = fopen(filepath, "w+");
            if (fp != NULL)
            {
                for (int k = 0; k < (*numofwords) - 1; k++)
                {
                    fprintf(fp, "%s %s\n", ent[k].english, ent[k].chinese);
                }
                fprintf(fp, "%s %s", ent[*numofwords].english, ent[*numofwords].chinese);
                printf("\033[;33;5m词条删除成功!\033[0m\n");
            }
            else
            {
                printf("文件读取失败\n");
            }
            fclose(fp);
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        printf("\033[;31;5m查无此词!!!\033[0m\n");
    }
}

//用户操作界面
void UI(int *numofwords, struct entry ent[], char filepath[], int *choose, char name[])
{
    /*操作界面*/
    printf("\n\033[;33;5m*************************************************\033[0m\n");
    printf("\033[;33;5m*                欢迎使用电子词典               *\033[0m\n");
    printf("\033[;33;5m*************************************************\033[0m\n");
    printf("\033[;33;5m*     1.英译汉      2.汉译英     3.删除词条     *\033[0m\n");
    printf("\033[;33;5m*     4.添加词条    5.修改词条   6.背单词       *\033[0m\n");
    printf("\033[;33;5m*               7. 保 存 并 退 出               *\033[0m\n");
    printf("\033[;33;5m*************************************************\033[0m\n");
    printf("\033[;33;5m当前字典一共用%d个单词\033[0m\n", *numofwords);

    //用户输入选择
    printf("请输入：");
    scanf("%d", &(*choose));
    switch (*choose)
    {
    case 1:
        E2C(&(*numofwords), ent);
        UI(&(*numofwords), ent, filepath, &(*choose), name);
        break;
    case 2:
        C2E(&(*numofwords), ent);
        UI(&(*numofwords), ent, filepath, &(*choose), name);
        break;
    case 3:
        deleteentry(&(*numofwords), ent, filepath);
        UI(&(*numofwords), ent, filepath, &(*choose), name);
        break;
    case 4:
        addentry(&(*numofwords), ent, filepath);
        UI(&(*numofwords), ent, filepath, &(*choose), name);
        break;
    case 5:
        modientry(&(*numofwords), ent, filepath);
        UI(&(*numofwords), ent, filepath, &(*choose), name);
        break;
    case 6:reciteword(name,user,ent,&numofuser);
        UI(&(*numofwords), ent, filepath, &(*choose), name);
        break;
    case 7:printf("\033[;31;5m        保存成功,欢迎再次使用!\033[0m\n");
        break;
    default:
        printf("\033[;31;5m输入错误，请重新输入!!!\033[0m\n");
        UI(&(*numofwords), ent, filepath, &(*choose), name);
        break;
    }
    return;
}

//添加词条功能函数
void addentry(int *numofwords, struct entry ent[], char filepath[])
{
    char keye[20], keyc[20];
    printf("请输入要添加的单词(输入0000退出添加):");
    scanf("%s", &keye);
    if (strcmp(keye, "0000") == 0)
    {
        return;
    }
    for (int i = 0; i < *numofwords; i++)
    {
        if (strcmp(ent[i].english, keye) == 0)
        {
            printf("该词已在单词库中！\n");
            return;
        }
    }
    printf("请输入中文释义:");
    scanf("%s", &keyc);
    int flag = 0, tmp;
    for (int i = 0; i < *numofwords; i++)
    {
        if (strcmp(keye, ent[i].english) > 0)
        {
            tmp = i;
        }
        else
        {
            break;
        }
    }
    for (int j = *numofwords - 1; j > tmp; j--)
    {
        ent[j + 1] = ent[j];
    }
    strcpy(ent[tmp + 1].english,keye);
    strcpy(ent[tmp + 1].chinese,keyc);
    (*numofwords)++;
    FILE *fp;
    fp = fopen(filepath, "w");
    if (fp != NULL)
    {
        for (int k = 0; k < (*numofwords) - 1; k++)
        {
            fprintf(fp, "%s %s\n", ent[k].english, ent[k].chinese);
        }
        fprintf(fp, "%s %s", ent[*numofwords - 1].english, ent[*numofwords - 1].chinese);
    }
    else
    {
        printf("文件打开失败\n");
    }
    fclose(fp);
    printf("\033[;33;5m添加成功！！！\033[0m\n");
    flag = 1;
    if (flag == 0)
    {
        printf("添加失败!!!\n");
    }
}

//修改词条功能函数
void modientry(int *numofwords, struct entry ent[], char filepath[])
{
    char key[20], keye[20], keyc[20];
    FILE *fp;
    int flag = 0, tmp;
    do
    {
        printf("请输入要修改的单词(退出修改请输入0000):");
        scanf("%s", key);
        if (strcmp(key, "0000") == 0)
        {
            return;
        }
        for (int i = 0; i < *numofwords; i++)
        {
            if (strcmp(key, ent[i].english) == 0)
            {
                flag = 1;
                for (int j = i; j < (*numofwords) - 1; j++)
                {
                    ent[j] = ent[j + 1];
                }
                (*numofwords)--;
                FILE *fp;
                fp = fopen(filepath, "w");
                if (fp != NULL)
                {
                    for (int k = 0; k < (*numofwords) - 1; k++)
                    {
                        fprintf(fp, "%s %s\n", ent[k].english, ent[k].chinese);
                    }
                    fprintf(fp, "%s %s", ent[*numofwords].english, ent[*numofwords].chinese);
                    break;
                }
            }
        }
        if (flag == 0)
        {
            printf("\033[;31;5m查无此词！！！\033[0m\n");
        }
    } while (!flag);
    printf("请输入修改后的英文和中文(其间请用空格或换行隔开):\n");
    scanf("%s", keye);
    scanf("%s", keyc);
    for (int i = 0; i < *numofwords; i++)
    {
        if (strcmp(ent[i].english, keye) == 0)
        {
            printf("\033[;31;5m该词已在单词库中！\033[0m\n");
            return;
        }
    }
    for (int i = 0; i < *numofwords; i++)
    {
        if (strcmp(keye, ent[i].english) > 0)
        {
            tmp = i;
        }
        else
        {
            break;
        }
    }
    for (int j = *numofwords - 1; j > tmp; j--)
    {
        ent[j + 1] = ent[j];
    }
    strcpy(ent[tmp + 1].english, keye);
    strcpy(ent[tmp + 1].chinese, keyc);
    (*numofwords)++;
    fp = fopen(filepath, "w");
    if (fp != NULL)
    {
        for (int k = 0; k < (*numofwords) - 1; k++)
        {
            fprintf(fp, "%s %s\n", ent[k].english, ent[k].chinese);
        }
        fprintf(fp, "%s %s", ent[*numofwords - 1].english, ent[*numofwords - 1].chinese);
        printf("\033[;33;5m修改完成!\033[0m\n");
    }
    else
    {
        printf("文件打开失败\n");
        return;
    }
    fclose(fp);
}

//背单词功能函数
void reciteword(char name[],struct userlist user[],struct entry ent[],int *numofuser)
{
    int n, choice, station, m;
    FILE *fp;
    for (int i = 0; i < *numofuser; i++)
    {
        if (strcmp(user[i].name, name) == 0)
        {
            station = user[i].numofmemwd;
            m = i;
            printf("\033[;35;5m     您已经背了%d个单词了，继续加油哦~('.')~\033[0m\n", user[i].numofmemwd);
        }
    }
    printf("\n\033[;34;5m*************************************\033[0m\n");
    printf("\033[;34;5m*      1.背新单词    2.复习单词     *\033[0m\n");
    printf("\033[;34;5m*************************************\033[0m\n");
    printf("请输入：");
    scanf("%d", &choice);
    switch (choice)
    {
        case 1:
        {
            printf("请输入这次要背的单词数：");
            scanf("%d", &n);
            for (int i = 0; i < n; i++)
            {
                printf("\033[;33;5m   %s %s\033[0m\n", ent[station + i].english, ent[station + i].chinese);
            }
            printf("\033[;33;5m你是最棒的！~('o')~\033[0m\n");
            user[m].numofmemwd += n;
            fp = fopen("user.txt", "w");
            if (fp != NULL)
            {
                for (int k = 0; k < (*numofuser)-1; k++)
                {
                    fprintf(fp, "%s %s %d\n", user[k].name, user[k].pwd, user[k].numofmemwd);
                }
                fprintf(fp, "%s %s %d", user[*numofuser - 1].name, user[*numofuser - 1].pwd, user[*numofuser - 1].numofmemwd);
            }
                else
            {
                printf("\033[;31;5m文件读取失败！！！ \033[0m\n");
            }   
            fclose(fp);
        }
            break;
        case 2:
        {
            printf("请输入这次要复习的单词数：");
            scanf("%d", &n);
            for (int i = 0; i < n; i++)
            {
                printf("\033[;33;5m   %s %s\033[0m\n", ent[station - i - 1].english, ent[station - i - 1].chinese);
            }
            printf("\033[;33;5m你是最棒的！~('o')~\033[0m\n");
        }
            break;
        default:printf("\033[;31;5m输入错误，请重新输入!!!\033[0m\n");
            reciteword(name,user,ent,&(*numofuser));
            break;
    }

}