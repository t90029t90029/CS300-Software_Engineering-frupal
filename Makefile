CC = g++
PROJECT = frupal
AUTHOR = group10
CFLAGS = -g -o $(PROJECT) -Wall -Werror -lncurses

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

# Cheats
nofog:
	make clean
	$(CC) *.cpp $(CFLAGS) -g -D NOFOG
	./$(PROJECT)

noclip:
	make clean
	$(CC) *.cpp $(CFLAGS) -g -D NOCLIP
	./$(PROJECT)

ghost:
	make clean
	$(CC) *.cpp $(CFLAGS) -g -D NOCLIP -D NOFOG -D GODMODE
	./$(PROJECT)

test:
	make clean
	$(CC) *.cpp $(CFLAGS) -g -D TEST
	./$(PROJECT)

godmode:
	make clean
	$(CC) *.cpp $(CFLAGS) -g -D GODMODE
	./$(PROJECT)

