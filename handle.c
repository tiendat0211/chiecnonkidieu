#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "handle.h"

#define MAXLINE 250


void EnterUsername(char * s){
    printf(" \t Ten dang nhap : ");
    //scanf("%[^\n]s",s);
    gets(s);

}


void EnterPassword1(char * s){
    printf(" \t Nhap mat khau : ");
    //scanf("%[^\n]s",s);
    gets(s);
    printf("                                                                        \n");
    printf("                                                                        \n");
    printf("========================================================================\n");
}

void EnterPassword2(char * s){
    printf(" \t Nhap mat khau : ");
    //scanf("%[^\n]s",s);
    gets(s);
}

void PasswordAgain(char * s){
    printf(" \t Nhap lai mat khau : ");
    //scanf("%[^\n]s",s);
    gets(s);
    printf("                                                                        \n");
    printf("                                                                        \n");
    printf("========================================================================\n");

}

void EnterAnswer(char * s){
    printf(" \t Nhap cau tra loi : ");
    gets(s);
}

int getRandom(int max,int min){
    srand((unsigned int)time(NULL));
    return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

void CutScore(char* s){
    char username[50]="\0";
    char score[50]="\0";
    char*c;
    c = strtok(s," ");
    strcpy(username,c);
    c = strtok(NULL," ");
    strcpy(score,c);
    printf(" \t \t \t      %s: %s\n",username,score);
}

void CutQuiz(char *s,char *question, char *answer,char *request,char*name1,char*name2,int round,char* username){
    char*c;
    char user_score1[100]="\0";
    char user_score2[100]="\0";
    char user_score3[100]="\0";
    c = strtok(s,"#");
    strcpy(question,c);
    c= strtok(NULL,"#");
    strcpy(answer,c);
    c= strtok(NULL,"#");
    strcpy(request,c);
    c= strtok(NULL,"#");
    strcpy(name1,c);
    c= strtok(NULL,"#");
    strcpy(name2,c);
    c= strtok(NULL,"#");
    strcpy(user_score1,c);
    
    c= strtok(NULL,"#");
    strcpy(user_score2,c);
    
    c= strtok(NULL,"#");
    strcpy(user_score3,c);
    system("clear");
    printf("========================================================================\n");
    printf("                          Chiec non ki dieu                             \n");
    printf("========================================================================\n");
    printf("\n");
    printf("\t \t \t Ten nguoi choi: %s\n",username);
    printf("\n");
    printf("\t \t \t      Vong %d\n",round);
    printf("\n");
    printf(" \t \t \t Diem so hien tai \n\n");
    CutScore(user_score1);
    CutScore(user_score2);
    CutScore(user_score3);
    printf("\n");
    printf(" \t \t \t Luot nay cua: %s\n\n",name1);
    printf("Cau hoi: %s\t \n",question);
    printf("\n");
    printf(" \t \t \t Dap an: %s \n",answer);
    printf("\n");
     
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

void CutFinal(char *s){
    char*c;
    char user_score1[100]="\0";
    char user_score2[100]="\0";
    char user_score3[100]="\0";

    c= strtok(s,"#");
    strcpy(user_score1,c);
    
    c= strtok(NULL,"#");
    strcpy(user_score2,c);
    
    c= strtok(NULL,"#");
    strcpy(user_score3,c);

    system("clear");
    printf("========================================================================\n");
    printf("                          Chiec non ki dieu                             \n");
    printf("========================================================================\n");
    printf("\n");
    printf("\n");
    printf(" \t \t \t Ket qua cuoi cung \n\n");
    CutScore(user_score1);
    CutScore(user_score2);
    CutScore(user_score3);
    printf("\n");
    printf("\n");
    printf("========================================================================\n");
}

