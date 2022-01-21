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

Rank createData(char *username,int score);
URank readf(char *fileName);
URank createNode(Rank data);
URank init();
URank addHead(URank head, Rank data);
URank addTail(URank head, Rank data);
URank getNode(URank head, int index);
Rank getData(URank head, int index);
void printRank(URank head);

#endif
