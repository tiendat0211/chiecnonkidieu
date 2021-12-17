#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "user.h"


Data createData(char *username, char *password, char *isSignIn) {
  Data data;
  strcpy(data.username, username);
  strcpy(data.password, password);
  strcpy(data.isSignIn, isSignIn);
  return data;
}

Node createNode(Data data) {
  Node temp;
  temp = (Node)malloc(sizeof(struct User));
  temp->next = NULL;
  temp->data = data;
  return temp;
}

Node init() {
  Node head;
  head = NULL;
  return head;
}

Node addHead(Node head, Data data) {
  Node temp = createNode(data); 
  if(head == NULL) {
    head = temp;
  }else{
    temp->next = head;
    head = temp;
  }
  return head;
}

Node addTail(Node head, Data data) {
  Node temp,p;
  temp = createNode(data);
  if(head == NULL) {
    head = temp;
  }
  else{
    p = head;
    while(p->next != NULL) {
      p = p->next;
    }
    p->next = temp;
  }
  return head;
}

Node getNode(Node head, int index) {
  int k = 0;
  Node p = head;
  while(p->next != NULL && k != index) {
    ++k;
    p = p->next;
  }
  return p;
}

Data getData(Node head, int index) {
  int k = 0;
  Node p = head;
  while(p->next != NULL && k != index) {
    ++k;
    p = p->next;
  }
  return p->data;
}



int checkUsername(Node head, char *name) {
  int position = 0;
  for(Node p = head; p != NULL; p = p->next) {
    if(strcmp(p->data.username, name) == 0) {
      return position;
    }
    ++position;
  }
  return -1;
}

void destroy(Node head) {
  Node tmp;
  while (head != NULL) {
    tmp = head;
    head = head->next;
    free(tmp);
  }
}

void writeFile(Node head, char *fileName) {
  FILE *f = fopen(fileName, "w");
  if (f == NULL) {
    exit(0);
  }

  Node p;
  for(p = head; p != NULL; p = p->next) {
    fprintf(f, "%s\t%s\t%s\n", p->data.username, p->data.password, p->data.isSignIn);
  }
  fclose(f);
}

Node updateAt(Node head, int index, Data newData) {
  int k = 0;
  Node p = head;
  while(p->next != NULL && k != index) {
    ++k;
    p = p->next;
  }
  p->data = newData;
  return head;
}

Node setup(char *fileName) {
    char username[50],password[50],isSignIn[2];

    Data data;
  FILE *f = fopen(fileName, "r");
  if (f == NULL) {
    printf("Can\'t read input file!\n");
    exit(0);
  }

    Node head = init();
  
    while(fscanf(f,"%s %s %s\n",username,password,isSignIn) != EOF){
        data = createData(username,password,isSignIn);
        head = addTail(head, data);
    }
  fclose(f);
  return head;
}

void printList(Node head){
    printf("List account:\n");
    Node p = head;
    while(NULL!=p){
        printf("%s,",p->data.username);
        printf("%s,",p->data.password);
        printf("%s\n",p->data.isSignIn);
        p = p->next;
    }
    printf("\n");
}

int checkPassword(Node head, char*username, char* password){
    Data d;
    int position=checkUsername(head,username);
    if(position>=0){
        d = getData(head,position);
        if(strcmp(d.password,password)==0) return 1;
        else return -1;
    }else return 0;
}

