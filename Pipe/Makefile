## CONSTANTS
CC = gcc
CFLAGS = -g -Wall
CCFLAGS = $(CC) $(CFLAGS)

SRC_PIPES = $(wildcard *.c)
OBJ_PIPES = $(SRC_PIPES:.c=.o) 


all: ServRout Client

ServRout : log.o pipe.o ServRout.c
	$(CCFLAGS) -o $@ $^ -lm

Client : log.o pipe.o Client.c
	$(CCFLAGS) -o $@ $^ -lm

#pipes: $(OBJ_PIPES)
#	$(CCFLAGS) -o $@ $^

%.o: %.c
	$(CCFLAGS) -o $@ -c $<


.PHONY: clean

clean: 
	rm -f *.o ServRout ServDonne Client
	rm -f *.pipe

