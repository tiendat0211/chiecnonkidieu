#ifndef __QUESTION_H__
#define __QUESTION_H__

typedef struct {
  char question[200];
  char answer[100];
  char hidden[100];
}Question;

struct Linkdist{
  Question data;
  struct Linkdist*next;
};
typedef struct Linkdist *Quiz;

Question createQuiz(char *question, char *answer,char* hidden);
Quiz readfile(char *fileName);
Quiz createNodeQuiz(Question data);
Quiz initQuiz();
Quiz addHeadQuiz(Quiz head, Question data);
Quiz addTailQuiz(Quiz head, Question data);
Quiz getNodeQuiz(Quiz head, int index);
Question getDataQuiz(Quiz head, int index);
int checkQuiz(Quiz head, char *s);
int sumQuiz(Quiz head);
void printQuiz(Quiz head);
Quiz updateQuizAt(Quiz head, int index, Question newData);

void hiddenAnswer(char *s,char*temp);

#endif