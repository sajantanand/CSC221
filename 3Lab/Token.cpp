#include "Token.h"

Token::Token ()
{
	if ( DEBUG ) cout << "Token constructor BEGIN" << endl;
	type  = no_more;
	extra_info.oper = 0;
	if ( DEBUG ) cout << "Token constructor END" << endl;
}

Token::~Token ()
{
	
	if ( DEBUG ) cout << "Token destructor BEGIN" << endl;
	if ( DEBUG ) cout << "Type: " << type << endl;
	if ( type != number && type != no_more)
	{
		if ( DEBUG ) cout << "Delete: " << ( char * )extra_info.oper << endl;
		if ( extra_info.oper ) delete [] extra_info.oper;
		extra_info.oper = 0;
	}
	if ( DEBUG ) cout << "Token destructor END" << endl;	
}

const Token & Token::operator= ( const Token & rhs )
{
	if ( DEBUG ) cout << "Token operator= BEGIN" << endl;
	if ( this != &rhs )
	{
		type = rhs.type;
		if ( type == no_more )
		{}
		else if ( type == number )
		{
			extra_info.number = rhs.extra_info.number;
		}
		else
		{
			extra_info.oper = strdup ( rhs.extra_info.oper );
		}
	}
	if ( DEBUG ) cout << "Token operator= END" << endl;

	return *this;
}

bool operator!= ( const Token * t, const tokentype& u )
{
	if ( DEBUG ) cout << "Token operator!= 1" << endl;
	return ( t->type != u );

}

bool operator!= ( const tokentype& u, const Token * t )
{
	if ( DEBUG ) cout << "Token operator!= 2" << endl;
	return ( t != u );		//uses other overloaded operator
}

tokentype Token::get_type () const
{
	if ( DEBUG ) cout << "Token get_type" << endl;
	return type;
}

int Token::get_number () const
{
	if ( DEBUG ) cout << "Token get_number" << endl;
	return extra_info.number;
}

char * Token::get_variable () const
{
	if ( DEBUG ) cout << "Token get_variable" << endl;
	return extra_info.oper;
}

void Token::print () const
{
	if ( DEBUG ) cout << "Token print BEGIN" << endl;
	if ( type == number )
	{
		cout << extra_info.number;
		
	}
	else if ( type == no_more )
	{
		cout << endl;
	}
	else
	{
		if ( extra_info.oper ) cout << extra_info.oper;
	}
	if ( DEBUG ) cout << "Token print END" << endl;
}

void Token::get_next ( char * s, int & position  )
{
	if ( DEBUG ) cout << "Token get_next BEGIN" << endl;

	bool finished = false;

	while ( s [ position ] == ' ' )
	{
		position++;
	}

	while ( s [ position ] != ' ' && s [ position ] != '\n'  && !finished )
	{
		if ( isalpha ( s [ position ] ) )
		{
			finished = true;
			type = variable;
			if ( DEBUG ) cout << "first char " << s [ position ] << endl;
			do
			{
				realloc ( extra_info.oper, s [ position ] );
				position++;
			} while ( isalpha ( s [ position ] ) );
		}
		else if ( isdigit ( s [ position ] ) )
		{
			finished = true;
			type = number;
			
			do
			{
				
				extra_info.number = 10 * extra_info.number + ( s [ position ] - 48 );
				position++;
			} while ( isdigit ( s [ position ] ) );
		}
		else
		{
			finished = true;
			switch ( s [ position ] )
			{
				case '(':
					type = leftP;
					break;
				case ')':
					type = rightP;
					break;
				case '*':
					type = multiply;
					break;
				case '/':
					type = divide;
					break;
				case '^':
					type = exponent;
					break;
				case '+':
					type = add;
					break;
				case '-':
					type = subtract;
					break;
				default:
					cout << "Entered symbol " << s [ position ] << " is not allowed. Please try again." << endl;
					exit ( 1 );
			}
			realloc ( extra_info.oper, s [ position ] );
			position++;
		}
	}

	if ( finished == false )
	{
		type = no_more;
	}

	if ( DEBUG ) cout << "Token get_next END" << endl;
	
}

void realloc ( char * & orig, const char & added )
{
	if ( DEBUG ) cout << "Token realloc BEGIN" << endl;

	int n = 0;
	if ( orig != NULL ) n = strlen ( orig );

	char * temp = new ( nothrow ) char [ n + 2 ];
	memcpy ( temp, orig, sizeof ( char ) *  n );
	temp [ n ] = added;
	temp [ n + 1 ] = '\0';

	delete [] orig;
	orig = temp;
	temp = 0;

	if ( DEBUG ) cout << "Token realloc END" << endl;
}


int precedence ( tokentype t )
{
	if ( DEBUG ) cout << "Token precedence BEGIN" << endl;
	int temp;
	switch ( t )
	{
		case exponent:
			temp = 4;
			break;
		case multiply:
		case divide:
			temp = 3;
			break;
		case add:
		case subtract:
			temp = 2;
			break;
		case leftP:
		case rightP:
			temp = 1;
			break;
		default:
			temp = 0;
			break;
	}
	if ( DEBUG ) cout << "Token precedence END" << endl;

	return temp;
}

bool isOperator ( tokentype t )
{
	return ( ( t < 5 ) ? true : false );
}
