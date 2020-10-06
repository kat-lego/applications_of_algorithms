CFLAGS = -std=c++11 -Wall -pedantic -ggdb3
CC = g++

main: src/main.cpp src/tree.cpp
	$(CC) $(CFLAGS) src/main.cpp src/tree.cpp -o program.o -I inc/

clean:
	rm *.o
