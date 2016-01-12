#	Programmer:	Sajant Anand		Course:		CSC221 Fall
#	Assignment:	Lab1			Date:		9/4/2015
CC = g++
CFLAGS = -Wall -pedantic
LFLAGS = -L/usr/local/lib -lppm_graphic
zview:	main.o array3d.o
	$(CC) -o zview main.o array3d.o $(LFLAGS)
array3d.o:	array3d.cpp array3d.h
	$(CC) $(CFLAGS) -c array3d.cpp

clean:
	\rm -f array3d.o zview
