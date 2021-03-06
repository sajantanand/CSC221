#include <cstdlib>
#include <assert.h>
#include <cstring>
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
	strcpy(name, data_);
	next = NULL;
	prev = NULL;
}

listcell::~listcell()
{
	if ( name ) { delete [] name; }
	if ( next ) { delete next; }
	if ( prev ) { delete prev; }
}

namelist::namelist()
{
	head = NULL;
	tail = NULL;
}

bool namelist::append(char * data)
{
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
			temp = 0;
			p = 0;
		}
		added = true;
	}
	
	return added;
}

listcell * namelist::search( char * data )
{
	bool notFound = true;
	listcell * current = head;
	
	if ( head )
	{
		while( current && notFound )
		{
			notFound = strcmp(current->name, data);
			current = current->next;
		}

		if ( !notFound ) 
		{
			current = current->prev;
		}
	}
	
	return current;
}

namelist::~namelist()
{
	if ( head ) {	delete head;  }
}

void namelist::delete_here( char * data )
{
	listcell * p = search ( data );

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
	}
	else
	{
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}

	delete p;		
}


































