
CFLAGS = -std=c++11 -Wall -pedantic
CC = g++

run: main
	./program.o

main: src/main.cpp src/order_statistics.cpp
	$(CC) $(CFLAGS) src/main.cpp src/order_statistics.cpp -o program.o -I inc/

clean:
	rm *.o