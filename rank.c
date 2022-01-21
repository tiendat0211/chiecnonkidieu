#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "rank.h"

Rank createData(char *username, int score) {
  Rank data;
  strcpy(data.username, username);
  data.score = score;
  return data;
}

URank createNode(Rank data) {
  URank temp;
  temp = (URank)malloc(sizeof(struct Link));
  temp->next = NULL;
  temp->data = data;
  return temp;
}

URank init() {
  URank head;
  head = NULL;
  return head;
}

URank addHead(URank head, Rank data) {
  URank temp = createNode(data); 
  if(head == NULL) {
    head = temp;
  }else{
    temp->next = head;
    head = temp;
  }
  return head;
}

URank addTail(URank head, Rank data) {
  URank temp,p;
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

URank getNode(URank head, int index) {
  int k = 0;
  URank p = head;
  while(p->next != NULL && k != index) {
    ++k;
    p = p->next;
  }
  return p;
}

Rank getData(URank head, int index) {
  int k = 0;
  URank p = head;
  while(p->next != NULL && k != index) {
    ++k;
    p = p->next;
  }
  return p->data;
}

void writeFile(URank head, char *fileName) {
  FILE *f = fopen(fileName, "w");
  if (f == NULL) {
    exit(0);
  }

  URank p;
  for(p = head; p != NULL; p = p->next) {
    fprintf(f, "%s \t %d\n", p->data.username,p->data.score);
  }
  fclose(f);
}

URank readf(char *fileName) {
    char username[50];
    int score;

    Rank data;
  FILE *f = fopen(fileName, "r");
  if (f == NULL) {
    printf("Can\'t read input file!\n");
    exit(0);
  }

    URank head = init();
  
    while(fscanf(f,"%s %d\n",username,&score) != EOF){
        data = createData(username,score);
        head = addTail(head, data);
    }
  fclose(f);
  return head;
}

void printRank(URank head){
  system("clear");
  printf("==========================================================================\n");
  printf("=                          Chiec non ki dieu                             =\n");
  printf("==========================================================================\n");
  printf("=                                                                        =\n");
  printf("=                                                                        =\n");
  printf("= \t \t \t Bang xep hang \t \t \t \t \t =\n");
  printf("=                                                                        =\n");
  printf("=                                                                        =\n");
  URank p = head;
  int idx = 1;
  while(NULL!=p){
    printf("= \t \t \t %d.%s: ",idx,p->data.username);
    printf("%d\t \t \t \t \t =\n",p->data.score);
    p = p->next;
    idx++;
  }
  printf("=                                                                        =\n");
  printf("=                                                                        =\n");
  printf("==========================================================================\n");
  printf("\n");
}