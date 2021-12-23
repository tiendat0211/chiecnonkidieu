#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/stat.h>
#include <syslog.h>
#include <time.h>
#include <arpa/inet.h>
#include <errno.h>

#include "user.h"
#include "handle.h"
#include "question.h"

#define MAXLINE 200
#define MAXCN 12
#define SA struct sockaddr

int idplayer[100];
Data player[4];
int playerturn=1;

void Dangnhap(int connfd, Node head, char *username, char *password){
    int position=checkUsername(head,username);
    if(position >= 0){
        if(checkPassword(head,username,password)==1){
            send(connfd, "1", 100, 0);
        }else send(connfd, "-1", 100, 0); //mat khau sai
    }else send(connfd, "0", 100, 0);// khong tim thay tai khoan
}

void Dangxuat(int connfd, Node head, char *username, char *password){
    Data newData;
    int position=checkUsername(head,username);
    if(position >= 0){
        newData = createData(username,password,0,0,0,0);
        updateAt(head,position,newData);
        writeFile(head,"user.txt");
        send(connfd, "1", 100, 0); //dang xuat thanh cong
    }
}

void Dangky(int connfd, Node head, char *username, char *password){
    Data data;
    if(checkUsername(head,username) >= 0){
        send(connfd, "-1", 100, 0);// da ton tai tai khoan
    }else{
        data = createData(username,password,0,0,0,0);
        head = addTail(head, data);
        writeFile(head,"user.txt");
        send(connfd, "1", 100, 0);// dang ky thanh cong
    }
}

void Sansang(int connfd,Quiz qhead, Question question[],char*request){
    char buffer[MAXLINE + 1]="\0";
        int round = atoi(request);
        strcat(buffer,question[round-1].question);
        strcat(buffer,"#");
        strcat(buffer,question[round-1].hidden);
        strcat(buffer,"#"); 
        strcat(buffer,"10#");
        strcat(buffer,player[playerturn].username);
        strcat(buffer,"#");
        send(connfd, buffer, strlen(buffer), 0);//gui cau hoi
    

}


void Choi(int connfd,char*username,Node head){
    char buffer[MAXLINE + 1]="\0";
    char numuser[5];
    Data newData;
    int position=checkUsername(head,username);
    newData = getData(head, position);
    newData.isSignIn=1;
    reset(newData);
    updateAt(head,position,newData);
    writeFile(head,"user.txt");
    int count = sumSingin(head);
    idplayer[count]=connfd;
    //printf("%d\n",count);
    sprintf(numuser,"%d",count);

    if(count<3){
        player[count]=newData;
        printf("%s\n",player[count].username);
        strcat(buffer,"Doi:");
        strcat(buffer,numuser);
        strcat(buffer,"#");
        strcat(buffer,username);
        strcat(buffer,"#");
        printf("%s\n",buffer);
        for(int i=1 ; i<=count ; i++){
            send(idplayer[i], buffer, strlen(buffer), 0);
        }
       
    }else if(count==3){
        player[count]=newData;
        printf("%s\n",player[count].username);
        strcat(buffer,"OK:");
        strcat(buffer,numuser);
        strcat(buffer,"#");
        strcat(buffer,username);
        strcat(buffer,"#");
        for(int i=1 ; i<=count ; i++){
            send(idplayer[i], buffer, strlen(buffer), 0);
        }
    }else if(count>3){
        strcat(buffer,"Het cho:");
        for(int i=4 ; i<=count ; i++){
            send(idplayer[i], buffer, strlen(buffer), 0);
        }
    }

}

void Traloi( Quiz qhead, char *request, Node head){
    char buffer[MAXLINE + 1]="\0";
    char question[100]="\0";
    char username[100]="\0";
    char answer[100]="\0";
    char temp[100]="\0";
   
    Question d;
    int count;
    int sumuser = sumSingin(head);
    
    char s[10]="\0";
    CutRequest(request,question,answer,username);
    //lay thong tin user
    Data data;
    int idx =checkUsername(head,username);
    data = getData(head, idx);

    //lay cau hoi
    int position = checkQuiz(qhead,question);
    d = getDataQuiz(qhead,position);


    if(strlen(answer)>1){
        if(strcmp(answer,d.answer)==0){
            data.score+=1000;
            updateAt(head,idx,data);
            writeFile(head,"user.txt");

            strcat(buffer,d.question);
            strcat(buffer,"#");
            strcat(buffer,d.answer);
            strcat(buffer,"#");
            strcat(buffer,"100");
            strcat(buffer,"#");
            strcat(buffer,player[playerturn].username);
            strcat(buffer,"#");
            for(int i=1 ; i<=sumuser ; i++){
                send(idplayer[i], buffer, strlen(buffer), 0);//gui ket qua cuoi cung chinh xac
            }
        }else{

            data.sumfalse+=1;
            updateAt(head,idx,data);
            writeFile(head,"user.txt");
            
            playerturn = nextplayer(playerturn);

            strcat(buffer,d.question);
            strcat(buffer,"#");
            strcat(buffer,d.hidden);
            strcat(buffer,"#");
            strcat(buffer,"-100");
            strcat(buffer,"#");
            strcat(buffer,player[playerturn].username);
            strcat(buffer,"#");
            for(int i=1 ; i<=sumuser ; i++){
                send(idplayer[i], buffer, strlen(buffer), 0);//gui ket qua cuoi cung sai
            }
            
        }
    }else{
        count = checkAnswer(d.answer,answer,d.hidden);

        if(count > 0){
            data.score+=count*100;
            updateAt(head,idx,data);
            writeFile(head,"user.txt");
            
            strcpy(temp,answer);
            Updatehidden(d.hidden,temp,d.answer);
            updateQuizAt(qhead,position,d);

        }else{
            data.sumfalse+=1;
            updateAt(head,idx,data);
            writeFile(head,"user.txt");

            playerturn = nextplayer(playerturn);
        }
        
        sprintf(s,"%d",count);
        strcat(buffer,d.question);
        strcat(buffer,"#");
        strcat(buffer,d.hidden);
        strcat(buffer,"#");
        strcat(buffer,s);
        strcat(buffer,"#");
        strcat(buffer,player[playerturn].username);
        strcat(buffer,"#");
        for(int i=1 ; i<=sumuser ; i++){
            send(idplayer[i], buffer, strlen(buffer), 0);//gui so chu giong
        }
    }

}



void HandleDataFromClient(int connfd,Node head, Quiz qhead, Question question[]){
        int n;
        char data[MAXLINE]="\0";
        char username[MAXLINE]="\0";
        char password[MAXLINE]="\0";
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
            Dangky(connfd,head,username,password);
        }else if(strcmp(c,"Dang xuat")==0){
            c = strtok(NULL, " ");
            strcpy(username,c);
            c = strtok(NULL, " ");
            strcpy(password,c);
            Dangxuat(connfd,head,username,password);
        }else if (strcmp(c,"Choi")==0){
            c = strtok(NULL, "#");
            strcpy(username,c);
            Choi(connfd,username,head);
        }else if (strcmp(c,"San sang")==0){
            c = strtok(NULL, " ");
            strcpy(request,c);
           Sansang(connfd,qhead,question,request);
        }else if (strcmp(c,"Tra loi")==0){
            c = strtok(NULL, "@");
            strcpy(request,c);
            Traloi(qhead, request,head);
        }
}

int main(int argc, char* argv[]){
    int player,listenSocket = 0;
    fd_set master;
    int sin_size;
	struct sockaddr_in server,client_addr;
    int opt = 1; 
    int fdmax, i, rc;
    fd_set read_fds;
    FD_ZERO(&master);
    FD_ZERO(&read_fds);
    Question question[3];

    //tao socket
    // tao file mo ta soket
    if ((listenSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    }  
    //gan dia chi cho socket
    // gan cong port 8080 
    if (setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    server.sin_family = AF_INET; 
    server.sin_addr.s_addr = INADDR_ANY; 
    server.sin_port = htons( atoi(argv[1]) );  //gan cong la 8080   
    // bind 
    if (bind(listenSocket, (struct sockaddr *)&server, sizeof(server))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    }
    //listen, chi dinh socket lang nghe ket noi
    if (listen(listenSocket, MAXCN) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 

    FD_SET(listenSocket, &master);
    fdmax = listenSocket;

    // Set timeout
    struct timeval timeout;
    timeout.tv_sec  = 1000;  // after 1000 seconds will timeout
    timeout.tv_usec = 0;
    //Step 4: Communicate with clients

    //char fileName[] = "user.txt";
	Node uhead = setup("user.txt");
    Quiz qhead = readfile("question.txt");
    int sumquiz = sumQuiz(qhead);
    for(int i=0; i<3 ;i++){
        int random = getRandom(-2,sumquiz);
        question[i] = getDataQuiz(qhead,random);
        printf("%s#%s\n",question[i].question,question[i].answer);
        sleep(1);
    }
    
    //printList(uhead);
    //printQuiz(qhead);
    //printf("%d\n",sumquiz);
     while(1){
        FD_ZERO(&read_fds);
        read_fds = master;
        rc = select(fdmax + 1, &read_fds, NULL, NULL, &timeout);
        if( rc == -1){
            perror("select() error!\n");
            exit(-6);
        }
        else if (rc == 0){
            printf("select() timed out. End program.\n");
            exit(-5);
        }
        for(i = 0; i <= fdmax; i++){
            if(FD_ISSET(i, &read_fds)){
                if(i == listenSocket){
                    sin_size = sizeof(client_addr);
                    player = accept(listenSocket, (struct sockaddr*)&client_addr, &sin_size);
                    if(player == -1){
                        perror("accept error!\n");
                        exit(-7);
                    }
                    else{
                        FD_SET(player, &master);
                        if(player > fdmax)
                        fdmax = player;
                        printf("Got a connection from (%s , %d) with fd = %d\n", inet_ntoa(client_addr.sin_addr),
                        ntohs(client_addr.sin_port), player);
                    }
                }
                else{
                    HandleDataFromClient(i,uhead,qhead,question);
                }
            }
        }
    }

    close(listenSocket);
    return 0; 
}