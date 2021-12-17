#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> 
#include <arpa/inet.h>

#include "menu.h"
#include "handle.h"

#define MAXLINE 250

void menuPlay(int sockfd, char *username, char *password){
    char a[2];
    int option,n;
    char receiveLine[MAXLINE + 1];
    char buffer[MAXLINE + 1]="\0";
    char question[MAXLINE + 1]="\0";
    char answer[MAXLINE + 1]="\0";
    char request[MAXLINE + 1]="\0";
    do{
        //system("clear");
        printf("\n\n=========CHIEC NON KI DIEU=========\n\n");
        printf("Chao mung %s den voi tro choi\n", username);
        printf("1. Choi\n");
        printf("2. Dang xuat\n");
        printf("Lua chon cua ban: ");
        //scanf("%[^\n]s",a);
        gets(a);
        option = atoi(a);
        switch (option)
        {
            case 1:
                //system("clear");
                strcpy(buffer,"\0");
                strcat(buffer,"Choi:1#@");
                send(sockfd,buffer,strlen(buffer),0);
                n = recv(sockfd, receiveLine, MAXLINE, 0);
                receiveLine[n] = '\0'; //null terminate 
                CutQuiz(receiveLine,question,answer,request); 
                if(strcmp(request,"bat dau")==0){
                    while(1){
                        strcpy(buffer,"\0");
                        strcpy(answer,"\0");
                        EnterAnswer(answer);
                        strcat(buffer,"Choi:");
                        strcat(buffer,question);
                        strcat(buffer,"#");
                        strcat(buffer,answer);
                        strcat(buffer,"#@");
                        send(sockfd,buffer,strlen(buffer),0);
                        n = recv(sockfd, receiveLine, MAXLINE, 0);
                        receiveLine[n] = '\0'; //null terminate 
                        CutQuiz(receiveLine,question,answer,request); 
                        if(strcmp(request,"100")==0){
                            printf("Ban tra loi chinh xac\n");
                            break;
                        }else if(strcmp(request,"-100")==0){
                            printf("Ban tra loi sai\n");
                        }else{
                            printf("So chu dung: %s\n",request);
                        }
                    }
                }
            break;
            case 2:
                strcpy(buffer,"\0");
                strcat(buffer,"Dang xuat:");
                strcat(buffer,username);
                strcat(buffer," ");
                strcat(buffer,password);
                send(sockfd,buffer,strlen(buffer),0);
                n = recv(sockfd, receiveLine, MAXLINE, 0);
                receiveLine[n] = '\0'; //null terminate  
                if(strcmp(receiveLine,"1") == 0){
                    printf("Dang xuat thanh cong\n");
                }
            break;
            default: 
                printf("Chon sai moi chon lai\n");
                break;
        }
    }while(option !=2);

}


void menuLogin(int sockfd){
    char a[2];
    int n,option;
    char receiveLine[MAXLINE + 1];
    do{
        system("clear");
        printf("=========CHIEC NON KI DIEU=========\n\n");
        printf("1. Dang nhap\n");
        printf("2. Dang ki\n");
        printf("3. Thoat\n");
        printf("Lua chon cua ban: ");
        //scanf("%[^\n]s",a);
        gets(a);
        option = atoi(a);
        switch (option)
        {
            case 1:
            while (1) { 
                char buffer[MAXLINE + 1]="\0";
                char username[10] = "\0";
                char password[10] = "\0";
                EnterUsername(username);
                EnterPassword(password);
                strcat(buffer,"Dang nhap:");
                strcat(buffer,username);
                strcat(buffer," ");
                strcat(buffer,password);
                send(sockfd,buffer,strlen(buffer),0);
                n = recv(sockfd, receiveLine, MAXLINE, 0);
                receiveLine[n] = '\0'; //null terminate  
                //printf("%s\n",receiveLine);
                if(strcmp(receiveLine,"1") == 0){
                    printf("Dang nhap thanh cong\n");
                    menuPlay(sockfd,username,password);
                    break;             
                }else if(strcmp(receiveLine,"-1") == 0){
                    printf("Sai mat khau\n");
                }else if(strcmp(receiveLine,"0") == 0){
                    printf("Khong tim thay tai khoan\n");
                }
            } 
                break;    
            case 2:
                while (1) { 
                    char buffer[MAXLINE + 1]="\0";
                    char username[10] = "\0";
                    char password[10] = "\0";
                    char checkpassword[10] = "\0";
                    int check = 0;
                    EnterUsername(username);
                    EnterPassword(password);
                    PasswordAgain(checkpassword);
                    strcat(buffer,"Dang ky:");
                    strcat(buffer,username);
                    strcat(buffer," ");
                    strcat(buffer,password);
                    strcat(buffer," 0");
                    if(check == 0){
                        send(sockfd, buffer, strlen(buffer), 0);
                        n = recv(sockfd, receiveLine, MAXLINE, 0);
                        receiveLine[n] = '\0'; //null terminate 
                        if(strcmp(receiveLine,"1")==0){
                            printf("Dang ki thanh cong\n");
                            break;
                        }else if(strcmp(receiveLine,"-1")==0){
                            printf("Da ton tai nguoi dung nay\n");
                        } 
                    }
                }
                break;
                case 3:
                break;      
            default:
                printf("Chon sai moi chon lai\n");
                break;
        }
    }while (option != 3);
    printf("====BYE BYE====\n\n");
}
