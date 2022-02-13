#ifndef __RANK_H__
#define __RANK_H__

typedef struct {
  char username[100];
  int score;
}Rank;

struct Link{
  Rank data;
  struct Link*next;
};
typedef struct Link *URank;

Rank createDataR(char *username,int score);

URank readf(char *fileName);
URank createNoderR(Rank data);
URank initR();
URank addHeadR(URank head, Rank data);
URank addTailR(URank head, Rank data);
URank getNodeR(URank head, int index);
Rank getDataR(URank head, int index);
void printRank(URank head);

void writef(Rank data, char *fileName);

void bubbleSort(URank start);
void swap(URank a,URank b);
void writeFR(URank head, char *fileName);


#endif
