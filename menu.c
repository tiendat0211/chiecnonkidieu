#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> 
#include <arpa/inet.h>
#include <stdbool.h>

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
    char sumuser[10]="\0";
    char name[MAXLINE + 1]="\0";
    char round[MAXLINE + 1]="\0";
    int countround = 1;
    int check = 1;
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
                strcat(buffer,"Choi:");
                strcat(buffer,username);
                strcat(buffer,"#");
                send(sockfd,buffer,strlen(buffer),0);
                do{
                    n = recv(sockfd, receiveLine, MAXLINE, 0);
                    receiveLine[n] = '\0'; //null terminate 
                    CutWait(receiveLine,sumuser,name,request);
                    int a = atoi(sumuser);
                    if(strcmp(request,"Doi")==0){
                        printf("Hay doi %d nguoi tham gia phong\n",(3-a));
                    }else if(strcmp(request,"OK")==0){
                        printf("Phong da du nguoi\n");
                        do{
                            strcpy(buffer,"\0");
                            strcat(buffer,"San sang:");
                            sprintf(round,"%d",countround);
                            strcat(buffer,round);
                            send(sockfd,buffer,strlen(buffer),0);
                            do{
                                n = recv(sockfd, receiveLine, MAXLINE, 0);
                                receiveLine[n] = '\0'; //null terminate 
                                CutQuiz(receiveLine,question,answer,request,name);
                                if(strcmp(name,username)==0){
                                    //while(1){
                                        if(strcmp(request,"100")==0){
                                            printf("Dap an cuoi cung chinh xac\n");
                                            break;
                                        }else if(strcmp(request,"-100")==0){
                                            printf("Dap an cuoi cung sai\n");
                                            
                                        }else if(strcmp(request,"10")==0){
                                            printf("Hay nhap cau tra loi cua ban\n");
                                        }else if(strcmp(request,"0")==0){
                                            printf("Ban khong tra loi chinh xac chu cai nao\n");
                                            
                                        }else{
                                            printf("So chu giong: %s\n",request);
                                        }

                                        printf("\n");
                                        strcpy(buffer,"\0");
                                        strcpy(answer,"\0");
                                        EnterAnswer(answer);
                                        strcat(buffer,"Tra loi:");
                                        strcat(buffer,question);
                                        strcat(buffer,"#");
                                        strcat(buffer,answer);
                                        strcat(buffer,"#");
                                        strcat(buffer,username);
                                        strcat(buffer,"#@");
                                        send(sockfd,buffer,strlen(buffer),0);
                                        
                                    //}
                                }else{
                                    if(strcmp(request,"100")==0){
                                        printf("%s tra loi dap an cuoi cung chinh xac\n",name);
                                        break;
                                    }else if(strcmp(request,"-100")==0){
                                        printf("%s tra loi dap an cuoi cung sai\n",name);
                                    }else if(strcmp(request,"10")==0){
                                        printf("\n");
                                    }else if(strcmp(request,"0")==0){
                                        printf("Khong tra loi chinh xac chu cai nao\n");
                                    }else{
                                        printf("%s: So chu giong: %s\n",name,request);
                                    }
                                    printf("Hay doi den luot cua ban\n");
                                }
                                
                            }while(strcmp(request,"100")!=0);
                            countround++;//next round
                        }while(countround<=3);  
                        if(countround == 4) check = 0;
                    }
                }while(check!=0);
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
                    menuPlay(sockfd,username,password);
                    sleep(2);
                    break;             
                }else if(strcmp(receiveLine,"-1") == 0){
                    printf("Sai mat khau\n");
                    sleep(2);
                }else if(strcmp(receiveLine,"0") == 0){
                    printf("Khong tim thay tai khoan\n");
                    sleep(2);
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
                    check = strcmp(password,checkpassword);
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
                    }else{
                         printf("Mat khau nhap lai bi sai\n");
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
