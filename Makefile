CC = g++

CompileParms = -c -Wall

OBJS = lettersom.o main.o

Opdr: $(OBJS)
	$(CC) $(OBJS) -o Puzzel

lettersom.o: lettersom.cc lettersom.h
	$(CC) $(CompileParms)  lettersom.cc

main.o: main.cc lettersom.h
	$(CC) $(CompileParms)  main.cc

