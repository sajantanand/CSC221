#ifndef NAMELIST_H
#define NAMELIST_H

#include <iostream>
using namespace std;

class listcell {
	private:
		char * name;
		listcell * next;
		listcell * prev;
	public:
		listcell();
		listcell(const char * data_);
		~listcell();

		friend ostream& operator<<(ostream& out, listcell * pointer);

		friend class namelist;
		friend class memberlist;
};

class namelist {
	private:
		listcell * head;
		listcell * tail;
	public:
		namelist();
		~namelist();
		bool append(char * data);
		void delete_here( char * data );
		void delete_pointer( listcell * p );
		listcell * search( char * data );

		friend ostream& operator<<(ostream& out, const namelist * RHS);

		friend class memberlist;
};

#endif

