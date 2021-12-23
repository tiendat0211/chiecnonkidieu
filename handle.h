#ifndef __HANDLE_H__
#define __HANDLE_H__

#include "user.h"

void EnterUsername(char * s);
void EnterPassword(char * s);
void PasswordAgain(char * s);
int getRandom(int max,int min);

void CutQuiz(char *s,char *question, char *answer,char *request,char*name);
void EnterAnswer(char * s);
int checkAnswer(char *s,char *request,char *hidden);
void CutRequest(char *s,char *question, char *answer,char* username);
void CutWait(char *s,char *sumuser,char*username,char *request);
int nextplayer(int a);

void Updatehidden(char*hidden,char *a,char*answer);

#endif
