## CONSTANTS
CC = gcc
CFLAGS = -g -Wall
CCFLAGS = $(CC) $(CFLAGS)
EXEC = pipes

SRC_PIPES = $(wildcard *.c)
OBJ_PIPES = $(SRC_PIPES:.c=.o) 

#OBJECTS_BASE = $(notdir $(basename $(wildcard Pipe/*.h)))

##all: clean

##format: $(wildcard Pipe/*.c) $(wildcard Pipe/*.h)
##	clang-format -i $^



##tests: $(foreach i, $(OBJECTS_BASE), $(i).test)

all: pipes

pipes: $(OBJ_PIPES)
	$(CCFLAGS) -o $@ $^

%.o: %.c
	$(CCFLAGS) -o $@ -c $< 


.PHONY: clean

clean: 
	rm -f *.o
	rm -f *.pipe

##FORCE:
##%.test: tests/% 
##	$^
