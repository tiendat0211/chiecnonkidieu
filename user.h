#ifndef __USER_H__
#define __USER_H__

typedef struct {
  char username[100];
  char password[100];
  int isSignIn;
  int score;
}Data;

struct User{
  Data data;
  struct User*next;
};
typedef struct User *Node;

Data createData(char *username, char *password,int isSignIn,int score);
Node setup(char *fileName);
Node createNode(Data data);
Node init();
Node addHead(Node head, Data data);
Node addTail(Node head, Data data);
Node getNode(Node head, int index);
Data getData(Node head, int index);
Node updateAt(Node head, int index, Data newData);
int search(Node head, Data data);
int checkUsername(Node head, char *name);
void writeFile(Node head, char *fileName);
void destroy(Node head);
int checkPassword(Node head, char*username,char* password);
void printList(Node head);
int sumSingin(Node head);
void reset(Data data);
void userplay(Data play[]);
void getScore(Node head,char*username);

void swap(Data xp, Data yp);
void selectionSort(Data arr[], int n);


#endif
