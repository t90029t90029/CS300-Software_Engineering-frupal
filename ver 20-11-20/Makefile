CC = g++
PROJECT = frupal
AUTHOR = group10
CFLAGS = -o $(PROJECT) -Wall -lncurses
# Not using -Werror for now

all: main.cpp
	make clean
	$(CC) *.cpp $(CFLAGS)

run:
	make clean
	$(CC) *.cpp $(CFLAGS)
	./$(PROJECT)

debug:
	make clean
	$(CC) *.cpp $(CFLAGS) -g
	gdb ./$(PROJECT)

leak:
	make clean
	$(CC) *.cpp $(CFLAGS) -g
	valgrind --leak-check=full ./$(PROJECT)

clean:
	rm -f $(PROJECT)

zip:
	make clean
	zip $(AUTHOR)-$(PROJECT).zip *.cpp *.h Makefile README.md map1.txt
