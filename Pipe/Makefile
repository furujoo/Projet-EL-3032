.PHONY: all clean format

## CONSTANTS

#OBJECTS_BASE = $(notdir $(basename $(wildcard Pipe/*.h)))

##all: clean

##format: $(wildcard Pipe/*.c) $(wildcard Pipe/*.h)
##	clang-format -i $^

clean: 
	rm -f *.o
	rm -f *.pipe

##tests: $(foreach i, $(OBJECTS_BASE), $(i).test)

Pipe: Client.o Serv.o pipe.o log.o 
	gcc -Wall -o $@ $^

%.o: %.c
	gcc -Wall -o $@ -c $< 


##FORCE:
##%.test: tests/% 
##	$^
