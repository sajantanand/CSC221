#	Programmer:	Sajant Anand		Course:		CSC221 Fall
#	Assignment:	Lab2			Date:		9/20/2015
CC = g++
CFLAGS = -Wall -pedantic
LFLAGS = -L/usr/local/lib -lppm_graphic
main:	main.o namelist.o members.o
	$(CC) -o main main.o namelist.o members.o
main.o:	main.cpp namelist.o members.o
	$(CC) $(CFLAGS) -c main.cpp
namelist.o:	namelist.cpp namelist.h
	$(CC) $(CFLAGS) -c namelist.cpp
members.o:	members.cpp members.h
	$(CC) $(CFLAGS) -c members.cpp

clean:
	\rm -f *.o main
