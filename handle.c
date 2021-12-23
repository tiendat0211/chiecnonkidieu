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




void CutQuiz(char *s,char *question, char *answer,char *request,char*name){
    char*c;
    c = strtok(s,"#");
    strcpy(question,c);
    c= strtok(NULL,"#");
    strcpy(answer,c);
    c= strtok(NULL,"#");
    strcpy(request,c);
    c= strtok(NULL,"#");
    strcpy(name,c);
    printf("Cau hoi: %s\n",question);
    printf("Dap an: %s\n",answer);
    printf("Luot nay cua: %s\n\n",name);
}

void CutRequest(char *s,char *question, char *answer,char* username){
    char*c;
    c = strtok(s,"#");
    strcpy(question,c);
    c= strtok(NULL,"#");
    strcpy(answer,c);
    c= strtok(NULL,"#");
    strcpy(username,c);
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


void CutWait(char *s,char *sumuser,char*username,char *request){
    char*c;
    c = strtok(s,":");
    strcpy(request,c);
    c= strtok(NULL,"#");
    strcpy(sumuser,c);
    c= strtok(NULL,"#");
    strcpy(username,c);
    printf("%s vua tham gia choi\n",username);
    printf("So luong nguoi choi: %s\n",sumuser);
   
}

int nextplayer(int a){
    if(a==3) return 1;
    if(a==1) return 2;
    if(a==2) return 3;
}

void Updatehidden(char*hidden,char *a,char*answer){
    for(int i =0;i<strlen(answer);i++){
        if(answer[i]== a[0] ) hidden[i]=a[0];
    }
}