#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "function.h"

//���ļ���������
void fakemain(char name[])
{
    struct entry ent[10000];
    int numofwords = 0, choose;
    char FILEPATH[30] = "new_dictionary.txt";
    search(FILEPATH, ent, &numofwords);
    UI(&numofwords, ent, FILEPATH, &choose, name);
    return;
}

//��ѯ�ж��ٸ������Ĺ��ܺ���
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
        printf("\033[;31;5m�ļ���ȡʧ�ܣ����� \033[0m\n");
    }
    fclose(fp);
}

//Ӣ�뺺���ܺ���
void E2C(int *numofwords, struct entry ent[])
{
    char key[20];
    while (1)
    {
        printf("������Ҫ��ѯ�Ĵ�(����0000�˳���ѯ)��");
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
                printf("\033[;33;5m\"%s\" ����������Ϊ��%s\033[0m\n", ent[i].english, ent[i].chinese);
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            printf("\033[;31;5m���޴˴�!!!\033[0m\n");
        }
    }
}

//����Ӣ���ܺ���
void C2E(int *numofwords, struct entry ent[])
{
    char key[20];
    while (1)
    {
        printf("������Ҫ��ѯ�Ĵ�(����0000�˳���ѯ):");
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
                printf("\033[;33;5m\"%s\" ��Ӧ��Ӣ���ǣ�\"%s\"\033[0m\n", ent[i].chinese, ent[i].english);
                flag++;
            }
        }
        if (flag == 0)
        {
            printf("\033[;31;5m���޴˴�!!!\033[0m\n");
        }
    }
}

//ɾ���������ܺ���
void deleteentry(int *numofwords, struct entry ent[], char filepath[])
{
    char key[20];
    printf("������Ҫɾȥ�Ĵ�(����0000�˳�ɾ��):");
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
                printf("\033[;33;5m����ɾ���ɹ�!\033[0m\n");
            }
            else
            {
                printf("�ļ���ȡʧ��\n");
            }
            fclose(fp);
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        printf("\033[;31;5m���޴˴�!!!\033[0m\n");
    }
}

//�û���������
void UI(int *numofwords, struct entry ent[], char filepath[], int *choose, char name[])
{
    /*��������*/
    printf("\n\033[;33;5m*************************************************\033[0m\n");
    printf("\033[;33;5m*                ��ӭʹ�õ��Ӵʵ�               *\033[0m\n");
    printf("\033[;33;5m*************************************************\033[0m\n");
    printf("\033[;33;5m*     1.Ӣ�뺺      2.����Ӣ     3.ɾ������     *\033[0m\n");
    printf("\033[;33;5m*     4.��Ӵ���    5.�޸Ĵ���   6.������       *\033[0m\n");
    printf("\033[;33;5m*               7. �� �� �� �� ��               *\033[0m\n");
    printf("\033[;33;5m*************************************************\033[0m\n");
    printf("\033[;33;5m��ǰ�ֵ�һ����%d������\033[0m\n", *numofwords);

    //�û�����ѡ��
    printf("�����룺");
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
    case 7:printf("\033[;31;5m        ����ɹ�,��ӭ�ٴ�ʹ��!\033[0m\n");
        break;
    default:
        printf("\033[;31;5m�����������������!!!\033[0m\n");
        UI(&(*numofwords), ent, filepath, &(*choose), name);
        break;
    }
    return;
}

//��Ӵ������ܺ���
void addentry(int *numofwords, struct entry ent[], char filepath[])
{
    char keye[20], keyc[20];
    printf("������Ҫ��ӵĵ���(����0000�˳����):");
    scanf("%s", &keye);
    if (strcmp(keye, "0000") == 0)
    {
        return;
    }
    for (int i = 0; i < *numofwords; i++)
    {
        if (strcmp(ent[i].english, keye) == 0)
        {
            printf("�ô����ڵ��ʿ��У�\n");
            return;
        }
    }
    printf("��������������:");
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
        printf("�ļ���ʧ��\n");
    }
    fclose(fp);
    printf("\033[;33;5m��ӳɹ�������\033[0m\n");
    flag = 1;
    if (flag == 0)
    {
        printf("���ʧ��!!!\n");
    }
}

//�޸Ĵ������ܺ���
void modientry(int *numofwords, struct entry ent[], char filepath[])
{
    char key[20], keye[20], keyc[20];
    FILE *fp;
    int flag = 0, tmp;
    do
    {
        printf("������Ҫ�޸ĵĵ���(�˳��޸�������0000):");
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
            printf("\033[;31;5m���޴˴ʣ�����\033[0m\n");
        }
    } while (!flag);
    printf("�������޸ĺ��Ӣ�ĺ�����(������ÿո���и���):\n");
    scanf("%s", keye);
    scanf("%s", keyc);
    for (int i = 0; i < *numofwords; i++)
    {
        if (strcmp(ent[i].english, keye) == 0)
        {
            printf("\033[;31;5m�ô����ڵ��ʿ��У�\033[0m\n");
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
        printf("\033[;33;5m�޸����!\033[0m\n");
    }
    else
    {
        printf("�ļ���ʧ��\n");
        return;
    }
    fclose(fp);
}

//�����ʹ��ܺ���
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
            printf("\033[;35;5m     ���Ѿ�����%d�������ˣ���������Ŷ~('.')~\033[0m\n", user[i].numofmemwd);
        }
    }
    printf("\n\033[;34;5m*************************************\033[0m\n");
    printf("\033[;34;5m*      1.���µ���    2.��ϰ����     *\033[0m\n");
    printf("\033[;34;5m*************************************\033[0m\n");
    printf("�����룺");
    scanf("%d", &choice);
    switch (choice)
    {
        case 1:
        {
            printf("���������Ҫ���ĵ�������");
            scanf("%d", &n);
            for (int i = 0; i < n; i++)
            {
                printf("\033[;33;5m   %s %s\033[0m\n", ent[station + i].english, ent[station + i].chinese);
            }
            printf("\033[;33;5m��������ģ�~('o')~\033[0m\n");
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
                printf("\033[;31;5m�ļ���ȡʧ�ܣ����� \033[0m\n");
            }   
            fclose(fp);
        }
            break;
        case 2:
        {
            printf("���������Ҫ��ϰ�ĵ�������");
            scanf("%d", &n);
            for (int i = 0; i < n; i++)
            {
                printf("\033[;33;5m   %s %s\033[0m\n", ent[station - i - 1].english, ent[station - i - 1].chinese);
            }
            printf("\033[;33;5m��������ģ�~('o')~\033[0m\n");
        }
            break;
        default:printf("\033[;31;5m�����������������!!!\033[0m\n");
            reciteword(name,user,ent,&(*numofuser));
            break;
    }

}