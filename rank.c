#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "rank.h"

Rank createDataR(char *username, int score) {
  Rank data;
  strcpy(data.username, username);
  data.score = score;
  return data;
}

URank createNodeR(Rank data) {
  URank temp;
  temp = (URank)malloc(sizeof(struct Link));
  temp->next = NULL;
  temp->data = data;
  return temp;
}

URank initR() {
  URank head;
  head = NULL;
  return head;
}

URank addHeadR(URank head, Rank data) {
  URank temp = createNodeR(data); 
  if(head == NULL) {
    head = temp;
  }else{
    temp->next = head;
    head = temp;
  }
  return head;
}

URank addTailR(URank head, Rank data) {
  URank temp,p;
  temp = createNodeR(data);
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

URank getNodeR(URank head, int index) {
  int k = 0;
  URank p = head;
  while(p->next != NULL && k != index) {
    ++k;
    p = p->next;
  }
  return p;
}

Rank getDataR(URank head, int index) {
  int k = 0;
  URank p = head;
  while(p->next != NULL && k != index) {
    ++k;
    p = p->next;
  }
  return p->data;
}

void writef(Rank data, char *fileName) {
  FILE *f = fopen(fileName, "a");
  if (f == NULL) {
    exit(0);
  }

  fprintf(f, "%s \t %d\n", data.username,data.score);
  
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

    URank head = initR();
  
    while(fscanf(f,"%s %d\n",username,&score) != EOF){
        data = createDataR(username,score);
        head = addTailR(head, data);
    }
  fclose(f);
  return head;
}

void printRank(URank head){
  system("clear");
  printf("========================================================================\n");
  printf("                         Chiec non ki dieu                              \n");
  printf("========================================================================\n");
  printf("                                                                        \n");
  printf("                                                                        \n");
  printf("\t \t \t Bang xep hang \t \t \t \t \t \n");
  printf("                                                                        \n");
  printf("                                                                        \n");
  URank p = head;
  int idx = 1;
  while(NULL!=p&&idx<=10){
    printf("\t \t \t %d.%s: ",idx,p->data.username);
    printf("%d\t \t \t \t \t \n",p->data.score);
    p = p->next;
    idx++;
  }
  printf("                                                                        \n");
  printf("                                                                        \n");
  printf("========================================================================\n");
  printf("\n");
}

void bubbleSort(URank start)
{
    int swapped, i;
    URank ptr1;
    URank lptr = NULL;
  
    /* Checking for empty list */
    if (start == NULL)
        return;
  
    do
    {
        swapped = 0;
        ptr1 = start;
  
        while (ptr1->next != lptr)
        {
            if (ptr1->data.score < ptr1->next->data.score)
            { 
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}
  
/* function to swap data of two nodes a and b*/
void swap(URank a, URank b)
{
    Rank temp = a->data;
    a->data = b->data;
    b->data = temp;
}

void writeFR(URank head, char *fileName) {
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