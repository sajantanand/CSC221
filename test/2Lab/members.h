#ifndef MEMBERS_H
#define MEMBERS_H

#include "namelist.h"

class member
{
	private:
		char * name;
		namelist * friends;
		namelist * invitations_rcvd;
		namelist * invitations_sent;
		member * next;
		member * prev;
	public:
		member();
		member( const char * data );
		~member();
		friend class memberlist;
};

class memberlist
{
	private:
		member * head;
		member * tail;
	public:
		memberlist();
		~memberlist();
		member * search ( char * data);
		void join ( char * data );
		void quit ( char * data );
		void sendRequest ( char * data1, char * data2 );
		void acceptRequest ( char * data1, char * data2 );
		void rejectRequest ( char * data1, char * data2 );
		void unfriend ( char * data1, char * data2 );
		void print ( char * data);
		void printALL();
};

#endif
