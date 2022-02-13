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
#include "rank.h"

#define MAXLINE 1000

void menuPlay(int sockfd, char *username, char *password){
    char a[2];
    char b[2]="\0";
    char quay[2]="\0";
    int option,n;
    int score = 0;
    char guidiem[50] = "\0";
    char receiveLine[MAXLINE + 1];
    char buffer[MAXLINE + 1]="\0";
    char question[MAXLINE + 1]="\0";
    char answer[MAXLINE + 1]="\0";
    char request[MAXLINE + 1]="\0";
    char sumuser[10]="\0";
    char name1[MAXLINE + 1]="\0";
    char name2[MAXLINE + 1]="\0";
    char round[MAXLINE + 1]="\0";
    char mess[MAXLINE + 1]="\0";
    char dapan[MAXLINE + 1]="\0";
    int countround = 1;
    int check = 1;
    int failed = 0;
    int vongquay[10]={50,100,200,500,-1,50,100,200,500,1000};
    do{
        system("clear");
        printf("========================================================================\n");
        printf("                          Chiec non ki dieu                             \n");
        printf("========================================================================\n");
        printf("                                                                        \n");
        printf("                                                                        \n");
        printf("\t \t \t1.Choi \t \t \t \t \t \n");
        printf("\t \t \t2.Xem bang xep hang \t \t \t \t \n");
        printf("\t \t \t3.Dang xuat \t \t \t \t \t \n");
        if(strcmp(mess,"\0")!=0){
            printf("                                                                        \n");
            printf("                                                                        \n");
            printf(" \t \t \t %s \t \t \t =\n",mess);
        }
        printf("                                                                        \n");
        printf("                                                                        \n");
        printf("========================================================================\n");
        printf(" \t Lua chon cua ban: ");
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
                    CutWait(receiveLine,sumuser,name1,request);
                    int a = atoi(sumuser);
                    if(strcmp(request,"Doi")==0){
                        system("clear");
                        printf("========================================================================\n");
                        printf("                          Chiec non ki dieu                             \n");
                        printf("========================================================================\n");
                        printf("                                                                        \n");
                        printf("                                                                        \n");
                        printf("\t \t Ban vua tham gia phong \t \t \t \t \n");
                        printf("\t \t Hay doi %d nguoi tham gia phong \t \t \t \n",(3-a));
                    }else if(strcmp(request,"OK")==0){
                        printf("\n");
                        printf("\t \t Phong da du nguoi \t \t \t \t \t \n");
                        sleep(2);
                        do{
                            strcpy(buffer,"\0");
                            strcat(buffer,"San sang:");
                            sprintf(round,"%d",countround);
                            strcat(buffer,round);
                            strcat(buffer,"#");
                            strcat(buffer,username);
                            strcat(buffer,"#");
                            send(sockfd,buffer,strlen(buffer),0);
                            while(1){     
                                n = recv(sockfd, receiveLine, MAXLINE, 0);
                                receiveLine[n] = '\0'; //null terminate 
                                //printf("%s\n",receiveLine);
                                CutQuiz(receiveLine,question,answer,request,name1,name2,countround,username,dapan);
                                if(strcmp(username,name1)==0){
                                        printf("\n");
                                        printf("\t Ban con %d luot tra loi\n",3-failed);
                                        if(failed < 3){
                                            if(strcmp(request,"1")==0){
                                                    system("clear");
                                                    printf("========================================================================\n");
                                                    printf("                          Chiec non ki dieu                             \n");
                                                    printf("========================================================================\n");
                                                    printf("\n");
                                                    printf("\n");
                                                    printf("\t \t \t      Vong %d\n",countround);
                                                    printf("\n");
                                                    printf("Cau hoi: %s\n",question);
                                                    printf("\n");
                                                    printf("\t \t Dap an cuoi cung: %s\n",dapan);
                                                    printf("\n");
                                                    printf("An mot phim bat ky de tiep tuc...");
                                                    gets(b);
                                                break;
                                            }else if(strcmp(request,"-100")==0){
                                                printf("\t %s: Dap an cuoi cung sai\n",name2);
                                            }else if(strcmp(request,"10")==0){
                                                printf("\n");
                                            }else if(strcmp(request,"0")==0){
                                                printf("\t %s: khong tra loi chinh xac chu cai nao\n",name2);
                                            }else if(strcmp(request,"-1000")==0){
                                                printf("\t Tat ca da het luot doan\n");
                                                printf("\n");
                                                printf("\t \t Dap an cuoi cung: %s",dapan);
                                                printf("An mot phim bat ky de tiep tuc...");
                                                gets(b);
                                                break;
                                            }else{
                                                printf("\t Ban vua danh duoc so diem: %s\n",request);
                                            }
                                            printf("\n");

                                            printf("An mot phim bat ky de quay...");
                                            gets(quay);
                                            score = getRandom(-2,9);
                                            
                                            for(int i=0;i<10;i++){
                                                if(score == i) score = vongquay[i];
                                            }
                                            if(score==1){
                                                printf("Ban quay vao o: Them luot\n");
                                                printf("\n");
                                                strcpy(buffer,"\0");
                                                strcpy(answer,"\0");
                                                EnterAnswer(answer);
                                                strcat(buffer,"Tra loi:");
                                                strcat(buffer,question);
                                                strcat(buffer,"#");

                                                if(strcmp(answer,"\0")!=0){
                                                    strcat(buffer,answer);
                                                }else strcat(buffer,"0");

                                                strcat(buffer,"#");
                                                strcat(buffer,username);
                                                strcat(buffer,"#");
                                                strcat(buffer,"0");
                                                strcat(buffer,"#@");
                                                send(sockfd,buffer,strlen(buffer),0);
                                                failed--;
                                            }else if(score==-1){
                                                printf("Ban quay vao o: Mat luot\n");
                                                strcpy(buffer,"\0");
                                                strcpy(answer,"\0");
                                                strcat(buffer,"Tra loi:");
                                                strcat(buffer,question);
                                                strcat(buffer,"#");
                                                strcat(buffer,"0");
                                                strcat(buffer,"#");
                                                strcat(buffer,username);
                                                strcat(buffer,"#");
                                                strcat(buffer,"0");
                                                strcat(buffer,"#@");
                                                send(sockfd,buffer,strlen(buffer),0);
                                                sleep(1);
                                            }else{
                                                printf("Ban quay vao o: %d diem\n",score);
                                                printf("\n");
                                                sprintf(guidiem,"%d",score);
                                                strcpy(buffer,"\0");
                                                strcpy(answer,"\0");
                                                EnterAnswer(answer);
                                                strcat(buffer,"Tra loi:");
                                                strcat(buffer,question);
                                                strcat(buffer,"#");

                                                if(strcmp(answer,"\0")!=0){
                                                    strcat(buffer,answer);
                                                }else strcat(buffer,"0");
                                                
                                                strcat(buffer,"#");
                                                strcat(buffer,username);
                                                strcat(buffer,"#");
                                                strcat(buffer,guidiem);
                                                strcat(buffer,"#@");
                                                send(sockfd,buffer,strlen(buffer),0);
                                            }  
                                        }else if(failed>=3){
                                            printf("%d\n",failed);
                                            if(strcmp(request,"-1000")==0) {
                                                printf("\t Tat ca da het luot doan\n");
                                                break;
                                            }
                                            else{
                                                strcpy(buffer,"\0");
                                                strcat(buffer,"Het luot:");
                                                strcat(buffer,username);
                                                strcat(buffer,"#");
                                                strcat(buffer,question);
                                                strcat(buffer,"#@");
                                                send(sockfd,buffer,strlen(buffer),0);
                                                break;
                                            }
                                        }
                                    //}
                                }else if(strcmp(username,name2)==0){
                                    if(strcmp(request,"1")==0){
                                        system("clear");
                                        printf("========================================================================\n");
                                        printf("                          Chiec non ki dieu                             \n");
                                        printf("========================================================================\n");
                                        printf("\n");
                                        printf("\n");
                                        printf("\t \t \t      Vong %d\n",countround);
                                        printf("\n");
                                        printf("\t %s: Dap an cuoi cung chinh xac\n",name1);
                                        printf("\n");
                                        printf("Cau hoi: %s\n",question);
                                        printf("\n");
                                        printf("\t \t Dap an cuoi cung: %s\n",dapan);
                                        printf("\n");
                                        printf("An mot phim bat ky de tiep tuc...");
                                        gets(b);
                                        break;
                                    }else if(strcmp(request,"-100")==0){
                                        printf("\t %s: Dap an cuoi cung sai\n",name2);
                                        failed++;
                                    }else if(strcmp(request,"10")==0){
                                        printf("\n");
                                    }else if(strcmp(request,"0")==0){
                                        printf("\t %s: khong tra loi chinh xac chu cai nao\n",name2);
                                        failed++;
                                    }else if(strcmp(request,"-1000")==0){
                                        printf("\t Tat ca da het luot doan\n");
                                        sleep(2);
                                        break;
                                    }else{
                                        printf("\t %s: Danh duoc so diem: %s\n",name1,request);
                                    }
                                    printf("\t Hay doi den luot cua ban\n");
                                }else if(strcmp(username,name2)!=0 && strcmp(username,name1)!=0){
                                    if(strcmp(request,"1")==0){
                                        system("clear");
                                        printf("========================================================================\n");
                                        printf("                          Chiec non ki dieu                             \n");
                                        printf("========================================================================\n");
                                        printf("\n");
                                        printf("\n");
                                        printf("\t \t \t      Vong %d\n",countround);
                                        printf("\n");
                                        printf("\t %s: Dap an cuoi cung chinh xac\n",name1);
                                        printf("\n");
                                        printf("Cau hoi: %s\n",question);
                                        printf("\n");
                                        printf("\t \t Dap an cuoi cung: %s\n",dapan);
                                        printf("\n");
                                        printf("An mot phim bat ky de tiep tuc...");
                                        gets(b);
                                        break;
                                    }else if(strcmp(request,"-100")==0){
                                        printf("\t %s: Dap an cuoi cung sai\n",name2);
                                        
                                    }else if(strcmp(request,"10")==0){
                                        printf("\n");
                                    }else if(strcmp(request,"0")==0){
                                        printf("\t %s: khong tra loi chinh xac chu cai nao\n",name2);
                                        
                                    }else if(strcmp(request,"-1000")==0){
                                        printf("\t Tat ca da het luot doan\n");
                                        sleep(2);
                                        break;
                                    }else{
                                        printf("\t %s: Danh duoc so diem: %s\n",name1,request);
                                    }
                                    printf("\t Hay doi den luot cua ban\n");
                                }  
                            }
                            failed = 0;
                            countround++;//next round
                        
                        }while(countround<=3);  
                        if(countround == 4) check = 0;
                    }else if(strcmp(request,"Het cho")==0){
                        printf("\t \t Phong da day nguoi choi\n");
                        printf("\n");
                        printf("\t \t Ban co muon vao xem khong(C/K).... ");
                        gets(b);
                        if(strcmp(b,"c")==0||strcmp(b,"C")==0||strcmp(b,"co")==0||strcmp(b,"Co")==0){
                            strcpy(buffer,"\0");
                            strcat(buffer,"San sang:");
                            sprintf(round,"%d",countround);
                            strcat(buffer,round);
                            strcat(buffer,"#");
                            strcat(buffer,username);
                            strcat(buffer,"#");
                            send(sockfd,buffer,strlen(buffer),0);
                            while(1){     
                                n = recv(sockfd, receiveLine, MAXLINE, 0);
                                receiveLine[n] = '\0'; //null terminate 
                                CutQuiz(receiveLine,question,answer,request,name1,name2,countround,username,dapan);
                                if(strcmp(request,"1")==0){
                                    system("clear");
                                    printf("========================================================================\n");
                                    printf("                          Chiec non ki dieu                             \n");
                                    printf("========================================================================\n");
                                    printf("\n");
                                    printf("\n");
                                    printf("\t \t \t      Vong %d\n",countround);
                                    printf("\n");
                                    printf("\t %s: Dap an cuoi cung chinh xac\n",name1);
                                    printf("\n");
                                    printf("Cau hoi: %s\n",question);
                                    printf("\n");
                                    printf("\t \t Dap an cuoi cung: %s\n",dapan);
                                    printf("\n");
                                    printf("An mot phim bat ky de tiep tuc...");
                                    gets(b);
                                    break;
                                }else if(strcmp(request,"-100")==0){
                                    printf("\t %s: Dap an cuoi cung sai\n",name2);
                                            
                                }else if(strcmp(request,"10")==0){
                                    printf("\n");
                                }else if(strcmp(request,"0")==0){
                                    printf("\t %s: khong tra loi chinh xac chu cai nao\n",name2);
                                            
                                }else if(strcmp(request,"-1000")==0){
                                    printf("\t Tat ca da het luot doan\n");
                                    sleep(2);
                                    break;
                                }else{
                                    printf("\t %s: Danh duoc so diem: %s\n",name1,request);
                                }
                            }
                        }else{
                            printf("\t Cam on ban!!\n");
                            menuLogin(sockfd);
                        }
                    }
                }while(check!=0);

                strcpy(buffer,"\0");
                strcat(buffer,"Ket thuc:");
                send(sockfd,buffer,strlen(buffer),0);
                n = recv(sockfd, receiveLine, MAXLINE, 0);
                receiveLine[n] = '\0';
                CutFinal(receiveLine);
                printf("\t Nhan phim bat ki de thoat... \t");
                gets(b);

                strcpy(buffer,"\0");
                strcat(buffer,"Reset:");
                strcat(buffer,username);
                strcat(buffer," ");
                strcat(buffer,password);
                strcat(buffer," ");
                send(sockfd,buffer,strlen(buffer),0);
                n = recv(sockfd, receiveLine, MAXLINE, 0);
                receiveLine[n] = '\0';
                if(strcmp(receiveLine,"Reset")==0){
                    //reset all
                    countround=1;
                    failed = 0;
                    check = 1;
                }
            break;
            case 2:
                strcpy(buffer,"\0");
                strcat(buffer,"Xem xep hang:");
                send(sockfd,buffer,strlen(buffer),0);
                n = recv(sockfd, receiveLine, 1000, 0);
                receiveLine[n] = '\0'; //null terminate  
                CutRank(receiveLine);
                printf("\t Nhan phim bat ki de quay lai... \t");
                gets(b);
            break;
            case 3:
                strcpy(buffer,"\0");
                strcat(buffer,"Dang xuat:");
                strcat(buffer,username);
                strcat(buffer," ");
                strcat(buffer,password);
                send(sockfd,buffer,strlen(buffer),0);
                n = recv(sockfd, receiveLine, MAXLINE, 0);
                receiveLine[n] = '\0'; //null terminate  
                if(strcmp(receiveLine,"1") == 0){
                    strcpy(mess,"Ban da dang xuat thanh cong");
                }
            break;
            default: 
                strcpy(mess,"Chon sai!! Moi chon lai");
            break;
        }
    }while(option !=3);

}


void menuLogin(int sockfd){
    char a[2];
    int n,option;
    char receiveLine[MAXLINE + 1];
    char mess[MAXLINE +1]="\0";
    do{
        system("clear");
        printf("========================================================================\n");
        printf("                             Chiec non ki dieu                          \n");
        printf("========================================================================\n");
        printf("                                                                        \n");
        printf("                                                                        \n");
        printf("\t \t \t \t1.Dang nhap \t \t \t \t \n");
        printf("\t \t \t \t2.Dang ky \t \t \t \t \n");
        printf("\t \t \t \t3.Thoat \t \t \t \t \n");
        if(strcmp(mess,"\0")!=0){
            printf("                                                                        \n");
            printf("                                                                        \n");
            printf(" \t \t \t %s \t \t \t \n",mess);
        }
        printf("                                                                        \n");
        printf("                                                                        \n");
        printf("========================================================================\n");
        printf(" \t Lua chon cua ban: ");
        //scanf("%[^\n]s",a);
        gets(a);
        printf(" \t =\n");
        option = atoi(a);
        switch (option)
        {
            case 1:
            strcpy(mess,"\0");
            while (1) { 
                system("clear");
                printf("========================================================================\n");
                printf("                             Chiec non ki dieu                          \n");
                printf("========================================================================\n");
                printf("                                                                        \n");
                printf("                                                                        \n");
                printf("\t \t \t \t Dang nhap \t \t \t \t \n");
                if(strcmp(mess,"\0")!=0){
                    printf("                                                                        \n");
                    printf("                                                                        \n");
                    printf(" \t \t \t %s \t \t \t \n",mess);
                }
                printf("                                                                        \n");
                printf("                                                                        \n");
                char buffer[MAXLINE + 1]="\0";
                char username[10] = "\0";
                char password[10] = "\0";
                EnterUsername(username);
                EnterPassword1(password);
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
                    strcpy(mess,"Mat khau khong chinh xac");
                    sleep(2);
                    
                }else if(strcmp(receiveLine,"0") == 0){
                    strcpy(mess,"Khong tim thay tai khoan");
                    sleep(2);
                }
            } 
                break;    
            case 2:
                strcpy(mess,"\0");
                while (1) { 
                    system("clear");
                    printf("========================================================================\n");
                    printf("                             Chiec non ki dieu                          \n");
                    printf("=========================================================================\n");
                    printf("                                                                        \n");
                    printf("                                                                        \n");
                    printf("\t \t \t \t Dang ky \t \t \t \t \n");
                    if(strcmp(mess,"\0")!=0){
                        printf("                                                                        \n");
                        printf("                                                                        \n");
                        printf(" \t \t \t %s \t \t \t \n",mess);
                    }
                    printf("                                                                        \n");
                    printf("                                                                        \n");
                    char buffer[MAXLINE + 1]="\0";
                    char username[10] = "\0";
                    char password[10] = "\0";
                    char checkpassword[10] = "\0";
                    int check = 0;
                    EnterUsername(username);
                    EnterPassword2(password);
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
                            strcpy(mess,"Ban da dang ky thanh cong");
                            sleep(2);
                            break;
                        }else if(strcmp(receiveLine,"-1")==0){
                            strcpy(mess,"Da ton tai nguoi dung nay");
                            sleep(2);
                        } 
                    }else{
                        strcpy(mess,"Nhap lai mat khau sai   ");
                        sleep(2);
                    }
                }
                break;
                case 3:
                break;      
            default:
                strcpy(mess,"Chon sai!! Moi chon lai");
                break;
        }
    }while (option != 3);
    printf("====BYE BYE====\n\n");
}

void display(){
    
}
