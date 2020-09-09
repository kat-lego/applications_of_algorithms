
CFLAGS = -std=c++11 -Wall -pedantic
CC = g++

main: src/main.cpp src/order_statistics.cpp
	$(CC) $(CFLAGS) src/main.cpp src/order_statistics.cpp -o program.o -I inc/

clean:
	rm *.o *.txt