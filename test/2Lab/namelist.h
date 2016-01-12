#ifndef NAMELIST_H
#define NAMELIST_H

class listcell {
	private:
		char * name;
		listcell * next;
		listcell * prev;
	public:
		listcell();
		listcell(const char * data_);
		~listcell();

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
		listcell * search( char * data );

		friend class memberlist;
};

#endif

