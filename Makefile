CC = gcc
CFLAGS = -Wall -pedantic -ansi
OBJ = main.o box.o random.o terminal.o LinkedList.o
EXEC = eat

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o: main.c random.h LinkedList.h
	$(CC) -c main.c $(CFLAGS)

box.o : box.c box.h terminal.h random.h LinkedList.h
	$(CC) -c box.c $(CFLAGS)

random.o : random.c random.h
	$(CC) -c random.c $(CFLAGS)

terminal.o : terminal.c terminal.h
	$(CC) -c terminal.c $(CFLAGS)

LinkedList.o: LinkedList.c LinkedList.h
	$(CC) -c LinkedList.c $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJ)

