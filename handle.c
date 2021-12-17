#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "handle.h"
#include "user.h"

#define MAXLINE 250


void EnterUsername(char * s){
    printf("Ten dang nhap : ");
    //scanf("%[^\n]s",s);
    gets(s);
    if(strcmp(s,"\0")==0) exit(1);
}


void EnterPassword(char * s){
    printf("Nhap mat khau : ");
    //scanf("%[^\n]s",s);
    gets(s);
    if(strcmp(s,"\0")==0) exit(1);
}

void PasswordAgain(char * s){
    printf("Nhap lai mat khau : ");
    //scanf("%[^\n]s",s);
    gets(s);
    if(strcmp(s,"\0")==0) exit(1);
}

void EnterAnswer(char * s){
    printf("Nhap cau tra loi : ");
    gets(s);
    //scanf("%[^\n]s",s);
    //fgets(s,sizeof(s),stdin);
    if(strcmp(s,"\0")==0) exit(1);
}

int getRandom(int max,int min){
    srand((unsigned int)time(NULL));
    return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

void hiddenAnswer(char *s){
    for(int i =0; i<strlen(s);i++){
        if(isalpha(s[i])!=0) s[i]='*';
    }
}

void CutQuiz(char *s,char *question, char *answer, char *request){
    char*c;
    c = strtok(s,"#");
    strcpy(question,c);
    c= strtok(NULL,"#");
    strcpy(answer,c);
    c= strtok(NULL,"#");
    strcpy(request,c);
    printf("Cau hoi: %s\n",question);
    printf("Dap an: %s\n",answer);
}

void CutRequest(char *s,char *question, char *answer){
    char*c;
    c = strtok(s,"#");
    strcpy(question,c);
    c= strtok(NULL,"#");
    strcpy(answer,c);
}



int checkAnswer(char *s,char *request, char *hidden){
    int count=0;
    for(int i =0; i<strlen(s);i++){
        if(s[i]==request[0]) {
            hidden[i]=request[0];
            count++;
        }
    }
    return count;
}
