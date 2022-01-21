#ifndef __HANDLE_H__
#define __HANDLE_H__


void EnterUsername(char * s);
void EnterPassword1(char * s);
void EnterPassword2(char * s);

void PasswordAgain(char * s);
int getRandom(int max,int min);

void CutQuiz(char *s,char *question, char *answer,char *request,char*name1,char*name2,int round,char* username);
void EnterAnswer(char * s);
int checkAnswer(char *s,char *request,char *hidden);
void CutAnswer(char *s,char *question, char *answer,char* username);
void CutWait(char *s,char *sumuser,char*username,char *request);
int nextplayer(int a);

void Updatehidden(char*hidden,char *a,char*answer);
void CutScore(char* s);

void CutFinal(char *s);

#endif
