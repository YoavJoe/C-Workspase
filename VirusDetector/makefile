# All Targets
BIN=./bin/
SOURCE=./src/
INCLUDE=./include/

CFLAGS=-g -Wall -ansi -pedantic -c
C=-g -Wall -o

all: myVirusDetector

myVirusDetector: viruslist.o main.o
	@gcc $(C) myVirusDetector $(BIN)/viruslist.o $(BIN)/main.o

main.o: $(SOURCE)/main.c
	@gcc $(CFLAGS) $(SOURCE)/main.c -o $(BIN)/main.o

viruslist.o: $(SOURCE)/viruslist.c $(INCLUDE)/viruslist.h
	@mkdir -p bin
	@gcc $(CFLAGS) $(SOURCE)/viruslist.c -o $(BIN)/viruslist.o

#tell make that "clean" is not a file name!
.PHONY: clean run debug

clean:
	@rm -vf myVirusDetector

run: myVirusDetector
	@./myVirusDetector infected.txt signatures

debug: myVirusDetector
	@gdb ./myVirusDetector

memcheck: myVirusDetector
	valgrind --leak-check=full --show-leak-kinds=all ./myVirusDetector infected.txt signatures



