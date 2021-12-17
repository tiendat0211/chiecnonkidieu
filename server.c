#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> 
#include <arpa/inet.h>
#include <time.h>
#include <ctype.h>

#include "user.h"
#include "handle.h"
#include "question.h"

#define MAXLINE 200
#define MAX_CNN 50
#define SA struct sockaddr

void Dangnhap(int connfd, Node head, char *username, char *password){
    Data newData;
    int position=checkUsername(head,username);
    if(position >= 0){
        if(checkPassword(head,username,password)==1){
            send(connfd, "1", 100, 0); //dang nhap thanh cong
            newData = createData(username,password,"1");
            updateAt(head,position,newData);
            writeFile(head,"user.txt");
        }else send(connfd, "-1", 100, 0); //mat khau sai
    }else send(connfd, "0", 100, 0);// khong tim thay tai khoan
}

void Dangxuat(int connfd, Node head, char *username, char *password){
    Data newData;
    int position=checkUsername(head,username);
    if(position >= 0){
        newData = createData(username,password,"0");
        updateAt(head,position,newData);
        writeFile(head,"user.txt");
        send(connfd, "1", 100, 0); //dang xuat thanh cong
    }
}

void Dangky(int connfd, Node head, char *username, char *password, char *isSignIn){
    Data data;
    if(checkUsername(head,username) >= 0){
        send(connfd, "-1", 100, 0);// da ton tai tai khoan
    }else{
        data = createData(username,password,isSignIn);
        head = addTail(head, data);
        writeFile(head,"user.txt");
        send(connfd, "1", 100, 0);// dang ky thanh cong
    }
}


void Choi(int connfd, Quiz qhead, int sumquiz, char *request){
    char buffer[MAXLINE + 1]="\0";
    int count=0;
    int position = 0;
    char s[10]="\0";
    Question d;
    int random=0;
    char hidden[50]="\0";
    
    if(strcmp(request,"1#")==0){
        random = getRandom(-2,sumquiz);
        d = getDataQuiz(qhead,random);
        strcpy(hidden,d.answer);
        hiddenAnswer(hidden);
        strcat(buffer,d.question);
        strcat(buffer,"#");
        strcat(buffer,hidden);
        strcat(buffer,"#");
        strcat(buffer,"bat dau");
        strcat(buffer,"#");
        send(connfd,buffer,strlen(buffer),0);// gui cau hoi
    }else{
        char question[100]="\0";
        char answer[100]="\0";
        CutRequest(request,question,answer);
        position = checkQuiz(qhead,question);
        d = getDataQuiz(qhead,position);
        strcpy(hidden,d.answer);
        hiddenAnswer(hidden);
        if(strlen(answer)>1){
            if(strcmp(answer,d.answer)==0){
                strcat(buffer,d.question);
                strcat(buffer,"#");
                strcat(buffer,d.answer);
                strcat(buffer,"#");
                strcat(buffer,"100");
                strcat(buffer,"#");
                send(connfd,buffer,strlen(buffer),0);//gui ket qua cuoi cung chinh xac
            }else{
                strcat(buffer,d.question);
                strcat(buffer,"#");
                strcat(buffer,hidden);
                strcat(buffer,"#");
                strcat(buffer,"-100");
                strcat(buffer,"#");
                send(connfd,buffer,strlen(buffer),0);//gui ket qua cuoi cung sai
            }
        }else{
            count = checkAnswer(d.answer,answer,hidden);
            sprintf(s,"%d\n",count);
            strcat(buffer,d.question);
            strcat(buffer,"#");
            strcat(buffer,hidden);
            strcat(buffer,"#");
            strcat(buffer,s);
            strcat(buffer,"#");
            send(connfd,buffer,strlen(buffer),0);//gui so chu giong
        }
    }
     

}


void HandleDataFromClient(int connfd,Node head, Quiz qhead,int sumquiz){
    while(1){
        int n;
        char data[MAXLINE]="\0";
        char username[MAXLINE]="\0";
        char password[MAXLINE]="\0";
        char isSignIn[MAXLINE]="\0";
        char request[MAXLINE]="\0";
        n = recv(connfd, data, 1000, 0);
        data[n] = '\0';
        printf("Data: ");
        printf("%s\n",data);
        char *c = strtok(data, ":");
        //printf("%s\n",c);
        if (strcmp(c,"Dang nhap")==0){
            c = strtok(NULL, " ");
            strcpy(username,c);
            c = strtok(NULL, " ");
            strcpy(password,c);
            Dangnhap(connfd,head,username,password);
        }else if(strcmp(c,"Dang ky")==0){
            c = strtok(NULL, " ");
            strcpy(username,c);
            c = strtok(NULL, " ");
            strcpy(password,c);
            c = strtok(NULL, " ");
            strcpy(isSignIn,c);
            Dangky(connfd,head,username,password,isSignIn);
        }else if(strcmp(c,"Dang xuat")==0){
            c = strtok(NULL, " ");
            strcpy(username,c);
            c = strtok(NULL, " ");
            strcpy(password,c);
            Dangxuat(connfd,head,username,password);
        }else if (strcmp(c,"Choi")==0){
            c = strtok(NULL, "@");
            strcpy(request,c);
            Choi(connfd,qhead,sumquiz,request);
        }
    } 
}

int main(int argc, char* argv[]){
    int sockfd,connfd,sumquiz;
    socklen_t len;
    pid_t childpid;
    
    struct sockaddr_in serverAddr, clientAddr;

        // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&serverAddr, sizeof(serverAddr));
   
    // assign IP, PORT
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(atoi(argv[1]));
   
    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&serverAddr, sizeof(serverAddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");
   
    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");

    //char fileName[] = "user.txt";
	Node uhead = setup("user.txt");
    Quiz qhead = readfile("question.txt");
    sumquiz = sumQuiz(qhead);
    //printList(head);
    //printQuiz(qhead);
    //printf("%d\n",sumquiz);
    while(1){
        len = sizeof(clientAddr); 
    
        // Accept the data packet from client and verification
        connfd = accept(sockfd, (SA*)&clientAddr, &len);
        if (connfd < 0) {
            printf("server accept failed...\n");
            exit(0);
        }
        else printf("server accept the client...\n");


        if((childpid  = fork())==0){
            close(sockfd);

            HandleDataFromClient(connfd,uhead,qhead,sumquiz);
            
        }
        
    }
    close(connfd);
}