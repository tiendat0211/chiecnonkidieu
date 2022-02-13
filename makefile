CFLAGS = -c -Wall
CC = gcc
LIBS =  -lm 

all: client server

client: client.o menu.o handle.o rank.o
	${CC} client.o  handle.o  menu.o rank.o -o client

server: server.o user.o handle.o question.o rank.o
	${CC} server.o user.o handle.o question.o rank.o -o server

server.o: server.c
	${CC} ${CFLAGS} server.c

client.o: client.c 
	${CC} ${CFLAGS} client.c

user.o: user.c
	${CC} ${CFLAGS} user.c

handle.o: handle.c 
	${CC} ${CFLAGS} handle.c 

menu.o: menu.c
	${CC} ${CFLAGS} menu.c

question.o: question.c	
	${CC} ${CFLAGS} question.c

rank.o: rank.c	
	${CC} ${CFLAGS} rank.c


clean:
	rm -f *.o *~