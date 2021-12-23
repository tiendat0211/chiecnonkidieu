#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "question.h"


Question createQuiz(char *question, char *answer,char* hidden) {
  Question data;
  strcpy(data.question, question);
  strcpy(data.answer, answer);
  strcpy(data.hidden, hidden);
  return data;
}

Quiz createNodeQuiz(Question data) {
  Quiz temp;
  temp = (Quiz)malloc(sizeof(struct Linkdist));
  temp->next = NULL;
  temp->data = data;
  return temp;
}

Quiz initQuiz() {
  Quiz head;
  head = NULL;
  return head;
}

Quiz addHeadQuiz(Quiz head, Question data) {
  Quiz temp = createNodeQuiz(data); 
  if(head == NULL) {
    head = temp;
  }else{
    temp->next = head;
    head = temp;
  }
  return head;
}

Quiz addTailQuiz(Quiz head, Question data) {
  Quiz temp,p;
  temp = createNodeQuiz(data);
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

Quiz getNodeQuiz(Quiz head, int index) {
  int k = 0;
  Quiz p = head;
  while(p->next != NULL && k != index) {
    ++k;
    p = p->next;
  }
  return p;
}

Question getDataQuiz(Quiz head, int index){
  int k = 0;
  Quiz p = head;
  while(p->next != NULL && k != index) {
    ++k;
    p = p->next;
  }
  return p->data;
}


void hiddenAnswer(char *s,char*temp){
  for(int i =0; i<strlen(s);i++){
      if(s[i] != ' ' ) temp[i]='*';
      else temp[i]=' ';
  }
  temp[strlen(s)] = '\0';
}

Quiz readfile(char *fileName) {
    char question[200],answer[100];
    char hidden[100]="\0";
    char buff[2000];
    char *c;
    Question data;
  FILE *f = fopen(fileName, "r");
  if (f == NULL) {
    printf("Can\'t read input file!\n");
    exit(0);
  }

    Quiz head = initQuiz();
  
    while(fgets(buff,1000,f) != NULL)
    {
        if(buff[strlen(buff) - 1]=='\n'){
          buff[strlen(buff) - 1] = '\n';
          c = strtok(buff,"#");
          strcpy(question,c);
          c = strtok(NULL,"#");
          strcpy(answer,c);strcpy(hidden,"\0");
          hiddenAnswer(answer,hidden);
        }
        data = createQuiz(question,answer,hidden);
        head = addTailQuiz(head, data);
    }
  fclose(f);
  return head;
}

void printQuiz(Quiz head){
    printf("List account:\n");
    Quiz p = head;
    while(NULL!=p){
        printf("%s,",p->data.question);
        printf("%s,",p->data.answer);
        printf("%s\n",p->data.hidden);
        p = p->next;
    }
    printf("\n");
}

int sumQuiz(Quiz head){
  int sum = 0;
  Quiz p = head;
  while(NULL!=p){
    p = p->next;
    sum++;
  }
  return sum;
}

int checkQuiz(Quiz head, char *s) {
  int position = 0;
  for(Quiz p = head; p != NULL; p = p->next) {
    if(strcmp(p->data.question, s) == 0) {
      return position;
    }
    ++position;
  }
  return -1;
}

Quiz updateQuizAt(Quiz head, int index, Question newData) {
  int k = 0;
  Quiz p = head;
  while(p->next != NULL && k != index) {
    ++k;
    p = p->next;
  }
  p->data = newData;
  return head;
}