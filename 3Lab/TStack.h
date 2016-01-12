#ifndef TSTACK_H
#define TSTACK_H

#include <string.h>
#include <cstdlib>
#include <iostream>

#define DEBUG 0

using namespace std;

template<class T>

class TStack
{
	private:
		T * array;
		int elements;
		int maxSize;
	public:
		TStack ( int size );
		~TStack ();
		T pop ();
		void push ( T temp );
		T & top_of_stack () const;
		int size () const;
		void build_tree ( T tree );
		bool isEmpty() const
		{
			return (( elements == 0 ) ? true : false);
		}
};

template<class T>
TStack<T>::TStack ( int size )
{
	if ( DEBUG ) cout << "TStack consstructor BEGIN" << endl;
	array = new ( nothrow ) T [ ( int ) ( size * 1.4 ) ];
	elements = 0;
	maxSize = size * 1.4;
	if ( DEBUG ) cout << "TStack consstructor END" << endl;
}

template<class T>
TStack<T>::~TStack ()
{
	
	if ( DEBUG ) cout << "TStack destructor BEGIN" << endl;
	if ( array ) delete [] array;
	array = 0;
	elements = 0;
	if ( DEBUG ) cout << "TStack destructor END" << endl;
	
}


template<class T>
void TStack<T>::push ( T temp )
{
	if ( DEBUG ) cout << "TStack push BEGIN" << endl;
	if ( elements == maxSize )
	{
		maxSize *= 1.4;
		T * tempArray = new ( nothrow ) T [ ( int ) ( maxSize ) ];
		memcpy ( tempArray, array, elements * sizeof ( T ) );
		delete [] array;
		array = tempArray;
		tempArray= 0;
	}

	array [ elements++ ] = temp;
	if ( DEBUG ) cout << "TStack push END" << endl;
}

template<class T>
T TStack<T>::pop ()
{
	if ( DEBUG ) cout << "TStack pop" << endl;
	if (elements < 1 )
	{
		cout << "Stack is empty when it shouldn't be. . ." << endl;
		exit ( 1 );
	}
	T temp = array [ --elements ];
	array [ elements ] = 0;
	return temp;
}

template<class T>
T & TStack<T>::top_of_stack() const
{
	if ( DEBUG ) cout << "TStack top_of_stack" << endl;
	
	if (elements < 1 )
	{
		cout << "Stack is empty when it shouldn't be. . ." << endl;
		exit ( 1 );
	}
	return array [ elements - 1 ];
}

template<class T>
int TStack<T>::size () const
{
	return elements;
}

template<class T>
void TStack<T>::build_tree ( T tree )		//This function is only used when T = treeNode *
{

	if ( DEBUG ) cout << "TStack build_tree BEGIN" << endl;
	if ( elements > 1 )
	{
		T second = pop();
		T first = pop();

		tree->getLeft() = first;
		tree->getRight() = second;

		push ( tree );
	}
	else
	{
		cout << "Stack is empty when it shouldn't be. . ." << endl;
		exit ( 1 );
	}
	if ( DEBUG ) cout << "TStack build_tree END" << endl;
}
#endif
