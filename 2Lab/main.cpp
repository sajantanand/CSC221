#include <iostream>
#include "namelist.h"
#include "members.h"

using namespace std;

void printInstructions();
void transactions();
bool read1Name ( char * line, char * first );	//Multiple spaces can be between instruction and first name are OK
bool read2Names ( char * line, char * first, char * second );	//Multiple spaces can be between instruction and first name are OK. A space can be in the second name
void blank ( char * line, int type );

int main ()
{
	
	transactions();	

	return 0;
}

void printInstructions()
{
	cout << "LIST OF INSTRUCTIONS" << endl;
	cout << "J [name] - join Phasebook\n"
	     << "Q [name] - quit Phasebook\n"
	     << "S [name1][name2] - send friend request from name1 to name2\n"
	     << "A [name1][name2] - accept friend request by name1 of name2\n"
	     << "R [name1][name2] - reject friend request by name1 of name2\n"
	     << "U [name1][name2] - unfriend friend request by name1 of name2\n"
	     << "L [name] - print information of name" << endl;
}

void transactions()
{
	memberlist phasebook;
	char instruction[50];
	char name1[20];
	char name2[20];
	cin.getline( instruction,50 );
	while ( !cin.eof() )
	{
		switch(instruction[0])
		{
			case 'J':
				if ( read1Name ( instruction, name1 ) ) phasebook.join( name1 );
				break;
			case 'Q':
				read1Name ( instruction, name1 );
				phasebook.quit( name1 );
				break;
			case 'S':
				if ( read2Names ( instruction, name1, name2 ) ) phasebook.sendRequest( name1, name2 );
				break;
			case 'A':
				if ( read2Names ( instruction, name1, name2 ) ) phasebook.acceptRequest( name1, name2 );
				break;
			case 'R':
				if ( read2Names ( instruction, name1, name2 ) ) phasebook.rejectRequest( name1, name2 );
				break;
			case 'U':
				if ( read2Names ( instruction, name1, name2 ) ) phasebook.unfriend( name1, name2 );
				break;
			case 'L':
				if ( read1Name ( instruction, name1 ) )
				{
					if ( name1[0] == '*' )
					{
						phasebook.printAll();
					}
					else
					{
						phasebook.print( name1 );
					}
				}
				break;
			default:
				cout << "Error:  " << instruction[0] << " is not a valid transaction!" << endl;
		}
		blank ( instruction, 0 );
		blank ( name1, 1 );
		blank ( name2, 2 );
		cin.getline( instruction,50 );
	}
}

bool read1Name ( char * line, char * first )
{
	int i = 2;
	int nonSpace = 0;
	bool noSpace = true;
	bool result;
	if ( line[i] == '\0' )
	{
		cout << "Error:  Please provide a name!" << endl;
		result = false;
	}
	else
	{
		while ( line[i] != '\0' && i < 50)
		{
			if ( line[i] == ' ' && noSpace)
			{
				i++;
	
			}
			else
			{
				first[nonSpace] = line[i];
				i++;
				nonSpace++;
				noSpace = false;
			}
		}
		first[nonSpace] = '\0';
		result = true;
	}
	return result;
}

bool read2Names ( char * line, char * first, char * second )
{
	//cout << "read2Names 1" << endl;
	int i = 2;
	//int j = 0;
	int firstNonSpace = 0;
	int secondNonSpace = 0;
	bool firstWord = true;
	bool firstSpace = false;
	bool secondSpace = false;
	if ( line[i] == '\0' )
	{
		cout << "Error:  Please provide a name!" << endl;
		return false;
	}
	else
	{
		while ( line[i] != '\0'  && i < 50)
		{
			if ( line[i] == ' ' && !firstSpace )
			{
			
			}
			else if ( line[i] == ' ' && !secondSpace)
			{
				firstWord = false;
				secondNonSpace = i + 1;
				first[firstNonSpace] = '\0';
				if ( line[i+1] == '\0' )
				{
					cout << "Error:  Please provide a second name!" << endl;
					return false;
				}
			}
			else if ( firstWord )
			{
				first[firstNonSpace] = line[i];
				firstSpace = true;
				firstNonSpace++;
			}
			else
			{
				second[i - secondNonSpace] = line[i];
				secondSpace = true;
			}

			i++;
		}
	}
	if ( firstWord ) 
	{
		cout << "Error:  Please provide a second name!" << endl;		
		return false;
	}
	second[i - secondNonSpace] = '\0';
	//cout << "First " << first << endl;
	//cout << "Second " << second << endl;
	return true;

	//cout << "read2Names 2" << endl;
}

void blank ( char * line, int type )
{
	if ( type )
		for ( int i = 0; i < 20; i++ )
			line[i] = '\0';
	else
		for ( int i = 0; i < 50; i++ )
			line[i] = '\0';
}
