#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <ctype.h>
#include <string.h>
#include <cstdlib>

#define DEBUG 0

using namespace std;

union value
{
	int number;
	char * oper;
};

enum tokentype { add, subtract, multiply, divide, exponent, leftP, rightP, no_more, number, variable };

int precedence ( tokentype t );
bool isOperator ( tokentype t );
void realloc ( char * & orig, const char & added );

class Token
{
	private:
		tokentype type;
		value extra_info;
	public:
		Token();
		~Token();
		friend bool operator!= ( const Token * t, const tokentype& u );
		friend bool operator!= ( const tokentype& u, const Token * t );
		void get_next ( char * s, int & position );
		const Token & operator= ( const Token & rhs );
		tokentype get_type () const;
		int get_number () const;
		char * get_variable () const;
		void print() const;
};

#endif
