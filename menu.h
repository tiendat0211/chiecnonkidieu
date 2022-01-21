#ifndef __MENU_H__
#define __MENU_H__

void menuLogin(int sockfd);
void menuPlay(int sockfd, char *username, char *password);

void display();

#endif
