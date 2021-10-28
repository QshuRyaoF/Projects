#include<stdio.h> 
#ifndef function_h

#define function_h

#define MAXC 20
#define MAXE 20
#define total 10000

struct entry
{
    char english[MAXE+1]; //key 
    char chinese[MAXC+1];
    struct entry *next;
};
struct userlist
{
    char name[10];
    char pwd[20];
    int numofmemwd;
};

struct userlist user[1000];
int numofuser=0;

/*函数声明*/
void search(char filepath[],struct entry ent[],int *numofwords);
void E2C(int *numofwords,struct entry ent[]);
void C2E(int *numofwords,struct entry ent[]);
void deleteentry(int *numofwords,struct entry ent[],char filepath[]);
void UI(int *numofwords,struct entry ent[],char filepath[],int *choose,char name[]);
void addentry(int *numofwords,struct entry ent[],char filepath[]);
void modientry(int *numofwords,struct entry ent[],char filepath[]);
void fakemain(char name[]);
void read(struct userlist user[],int *numofuser,char filename[]);
void sign_in(int *numofuser,char filename[],struct userlist user[]);
void login(int *numofuser,struct userlist user[]);
void reciteword(char name[],struct userlist user[],struct entry ent[],int *numofuser);

#endif