
CFLAGS=-g -Wall -ansi -pedantic -c

all: myVirusDetector

myVirusDetector:
	@gcc $(CFLAGS) myVirusDetector

#tell make that "clean" is not a file name!
.PHONY: clean run debug

clean:
	@rm -vf myVirusDetector

run: myVirusDetector
	./myVirusDetector

debug: myVirusDetector
	@gdb myVirusDetector

memcheck: myVirusDetector
	valgrind --leak-check=full --show-leak-kinds=all ./myVirusDetector