#include <iostream>
#include <cstring>


//#include "Token.h"
//#include "Token.cpp"

using namespace std;

enum tokentype { add, subtract, multiply, divide, exponent, leftP, rightP, no_more, number, variable };

int main ()
{
	/*
	int * joe = new int(5);
	delete joe;
	joe = 0;
	delete joe;
	*/
	/*
	value * test = new ( nothrow ) value ();

	test->number = 5;

	cout << test->number << endl;
	//cout << test->oper << endl;
	cout << "here" << endl;
	//delete test;
	*/
	/*
	char * rand = 0;

	 if ( rand ) cout << strlen ( rand ) << endl;;

	Token * test = new ( nothrow ) Token ();
	int dummy = 0;

	//rand = new ( nothrow ) char [ 6 ];

	rand = strdup ( "5" );
	//memcpy ( rand, "sajant", sizeof ( char ) * 6 );

	test->get_next ( rand, dummy );
	

	test -> print ();

	cout << endl;

	free ( rand );

	delete test;

	return 0;
	*/



	/*
	char * orig = new ( nothrow ) char [ 6 ];
	memcpy ( orig, "sajant", sizeof ( char ) * 6 );
	//orig [ 6 ] = '\0';
	cout << orig[6] << endl;

	char added = 's';



	int n = 0;
	if ( orig != NULL ) n = strlen ( orig );
	char * temp = new ( nothrow ) char [ n + 1 ];
	memcpy ( temp, orig, sizeof ( char ) *  n );
	temp [ n ] = added;
	delete [] orig;
	orig = temp;
	temp = 0;

	cout << orig << endl;

	delete [] orig;	

	return 0;
	*/
	char ch = 0;
	int num = 0;
	tokentype t = no_more;
	
	do {
		cin >> ch;
		//cout << ch << endl;
		if ( isdigit ( ch ) )
		{
			t = number;
			do {
				num = 10*num + ( ch-48 );
				cin >> ch;
			} while ( isdigit ( ch ) );
		}
		cout << "Number: " << num << endl;

	} while ( !cin.eof() );

}
