#include <cstdlib>
#include <assert.h>
#include <string.h>
#include <iostream>

#include "namelist.h"

using namespace std;

listcell::listcell()
{
	name = NULL;
	next = NULL;
	prev = NULL;
}

listcell::listcell( const char * data_ )
{
	//cout << "listcell construc 1" << endl;
	int length = strlen( data_ );
	name = new (nothrow) char[length+1];
	strcpy(name, data_);
	next = NULL;
	prev = NULL;
	//cout << "listcell construc 2" << endl;
}

listcell::~listcell()
{
	//cout << "listcell destruc 1" << endl;
	if ( name )
	{
		delete [] name;
		name = 0;
	}
	//cout << "listcell destruc 2" << endl;
}

ostream& operator<<(ostream& out, listcell * pointer)
{
	while ( pointer )
	{
		cout << pointer->name;
		pointer = pointer->next;
		//char x[] = ((aFriends == NULL) ? '\n' : ", ")
		//cout << ((aFriends) ? ", " : "\n");
		if ( pointer )
		{
			cout << ", " << flush; 
		}
	}
	return out;
}

namelist::namelist()
{
	//cout << "namelist construc 1" << endl;
	head = NULL;
	tail = NULL;
	//cout << "namelist construc 1" << endl;
}

bool namelist::append(char * data)
{
	//cout << "namelist append 1" << endl;
	bool added = false;
	if ( search( data ) == NULL)
	{
	
		listcell * temp = new (nothrow) listcell(data);
		assert ( temp );
		if ( head == NULL )
		{
			head = temp;
			tail = temp;
			temp = 0;
		}		
		else
		{
			listcell * p = tail;
			tail->next = temp;
			tail = tail->next;
			tail->prev = p;
			tail->next = NULL;
			temp = 0;
			p = 0;
		}
		added = true;
	}
	//cout << "namelist append 2" << endl;
	return added;
}

listcell * namelist::search( char * data )
{
	//cout << "namelist search 1" << endl;
	bool notFound = true;
	listcell * current = head;
	
	while( current && notFound )
	{
		notFound = strcmp(current->name, data);
		if ( notFound )
		{
			current = current->next;
		}
	}

	//cout << "namelist search 2" << endl;
	return current;
}

namelist::~namelist()
{
	//cout << "namelist destructor 1" << endl;
	if ( head )
	{
		delete head;
		head = 0;
	}
	//cout << "namelist destruc 2" << endl;
}

void namelist::delete_here( char * data )
{
	//cout << "namelist delete here 1" << endl;
	listcell * p = search ( data );

	delete_pointer( p );		
}

void namelist::delete_pointer( listcell * p )
{
	//cout << "namelist delete pointer 1" << endl;
	if ( p == NULL ) {}
	else if ( head == p && tail == p )
	{
		head = NULL;
		tail = NULL;
	}
	else if ( head == p ) 
	{
		head = head->next;
	}
	else if ( tail == p )
	{
		tail = tail->prev;
		tail->next = 0;
	}
	else
	{
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}
	delete p;
	p = NULL;								//NOT HAVING ANY EFFECT
	//cout << "namelist delete pointer 2" << endl;		
}

ostream& operator<<(ostream& out, const namelist * RHS)
{
	cout << RHS->head;
	
	return out;
}
