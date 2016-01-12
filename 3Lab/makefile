#	Programmer:	Sajant Anand		Course:		CSC221 Fall
#	Assignment:	Lab3			Date:		11/11/2015
CC = g++
CFLAGS = -Wall -pedantic -g
LFLAGS = -L/usr/local/lib -lppm_graphic
main:	main.o Token.o TStack.h SyntaxTree.o
	$(CC) -o main main.o Token.o SyntaxTree.o
main.o:	main.cpp Token.o TStack.h
	$(CC) $(CFLAGS) -c main.cpp
Token.o:	Token.cpp Token.h
	$(CC) $(CFLAGS) -c Token.cpp
SyntaxTree.o:	SyntaxTree.cpp SyntaxTree.h
	$(CC) $(CFLAGS) -c SyntaxTree.cpp

clean:
	\rm -f *.o main
