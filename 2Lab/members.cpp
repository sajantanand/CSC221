#include <cstdlib>
#include <assert.h>
#include <cstring>
#include <iostream>

#include "members.h"
#include "namelist.h"

using namespace std;

member::member()
{
	//cout << "member 1" << endl;
	name = new (nothrow) char();
	friends = new (nothrow) namelist();
	invitations_rcvd = new (nothrow) namelist();
	invitations_sent = new (nothrow) namelist();
	next = NULL;
	prev = NULL;
	//cout << "member 2" << endl;
}

member::member ( const char * data )
{
	//cout << "member contstructor 1" << endl;
	int length = strlen( data );
	name = new (nothrow) char[length+1];
	memcpy( name, data, sizeof(char) * (length+1) );
	friends = new (nothrow) namelist();
	invitations_rcvd = new (nothrow) namelist();
	invitations_sent = new (nothrow) namelist();
	next = NULL;
	prev = NULL;
	//cout << "member contstructor 2 " << name << endl;
}

member::~member()
{
	//cout << "member destructor 1" << endl;
	if ( name ) {	delete [] name;	/*cout << "name" << endl;*/	}
	if ( friends ) {	delete friends;	/*cout << "friends" << endl;*/	}
	if ( invitations_rcvd ) {	delete invitations_rcvd;	/*cout << "received" << endl;*/	}
	if ( invitations_sent ) {	delete  invitations_sent;	/*cout << "sent" << endl;*/	}
	if ( next ) {	delete next;	/*cout << "next" << endl;*/	}
	//cout << "member destructor 2" << endl;
}

memberlist::memberlist()
{
	//cout << "memberlist construc 1" << endl;
	head = NULL;
	tail = NULL;
	count = 0;
	//cout << "memberlist construc 2" << endl;
}

memberlist::~memberlist()
{
	//cout << "memberlist destruc 1" << endl;
	if ( head ) {	delete head;	}
	//cout << "memberlist destruc 2" << endl;
}

member * memberlist::search ( char * data)
{
	//cout << "memberlist search 1" << endl;
	bool notFound = true;
	member * current = head;
	
	if ( current )
	{
		while( current && notFound )
		{
			notFound = strcmp(current->name, data);
			if ( notFound )
			{
				current = current->next;
			}
		}
	}
	//cout << "memberlist search 2" << endl;
	
	return current;
}

void memberlist::join ( char * data )
{
	//cout << "memberlist join 1" << endl;
	member * temp = search ( data );
	if ( temp )
	{
		cout << "Error:  " << data << " is already a member of PhaseBook!" << endl;
	}
	else
	{
		member * newMember = new (nothrow) member(data);
		assert ( newMember );
		if ( head == NULL )
		{
			head = newMember;
			tail = newMember;
			newMember = 0;
		}		
		else
		{
			member * p = tail;
			tail->next = newMember;
			tail = tail->next;
			tail->prev = p;
			newMember = 0;
			p = 0;
		}
		count++;
	}
	//cout << "memberlist join 2" << endl;
}

void memberlist::quit ( char * data )
{
	//cout << "memberlist quit 1" << endl;
	member * temp = search ( data );
	if ( temp == NULL )
	{
		cout << "Error:  " << data << " is not a member of PhaseBook!" << endl;
	}
	else
	{
		listcell * memFriends = temp->friends->head;
		while ( memFriends ) 
		{
			member * aFriend = search ( memFriends->name );
			aFriend->friends->delete_here ( data );
			memFriends = memFriends->next;
			aFriend = 0;
		}

		memFriends = temp->invitations_rcvd->head;
		while ( memFriends ) 
		{
			member * aFriend = search ( memFriends->name );
			aFriend->invitations_sent->delete_here ( data );
			memFriends = memFriends->next;
			aFriend = 0;
		}

		memFriends = temp->invitations_sent->head;
		while ( memFriends ) 
		{
			member * aFriend = search ( memFriends->name );
			aFriend->invitations_rcvd->delete_here ( data );
			memFriends = memFriends->next;
			aFriend = 0;
		}

		if ( temp == head && temp == tail )
		{
			head = 0;
			tail = 0;
		}
		else if ( temp ==  head )
		{
			head = head->next;
		}
		else if ( temp == tail )
		{
			tail = tail->prev;
			tail->next = NULL;
		}
		else
		{
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
		}
		temp->next = 0;
		temp->prev = 0;
		delete temp;

		count--;
	}
	//cout << "memberlist quit 2" << endl;
}

void memberlist::sendRequest ( char * data1, char * data2 )
{
	//cout << "memberlist sentR 1" << endl;
	member * sender = search ( data1 );
	member * receiver = search ( data2 );

	if ( sender == NULL )
	{
		cout << "Error:  " << data1 << " is not a member of Phasebook!" << endl;
	}
	else if ( receiver == NULL )
	{
		cout << "Error:  " << data2 << " is not a member of Phasebook!" << endl;
	}
	else
	{
		listcell * prevR = receiver->invitations_rcvd->search( data1 );
		listcell * prevS = sender->invitations_rcvd->search( data2 );
		listcell * friendR = receiver->friends->search( data1 );

		if ( prevR )
		{
			cout << "Error:  " << data1 << " has already sent a friend request to " << data2 << endl;
		}
		else if ( friendR )
		{
			cout << "Error:  " << data1 << " is already friends with " << data2 << endl;
		}
		else if ( prevS )
		{
			receiver->friends->append( data1 );
			sender->friends->append( data2 );
			receiver->invitations_sent->delete_here( data1 );
			sender->invitations_rcvd->delete_pointer( prevS );
		}
		else
		{
			sender->invitations_sent->append( data2 );
			receiver->invitations_rcvd->append( data1 );
		}

		receiver = 0;
		sender = 0;
		prevR = 0;
		prevS = 0;
		friendR = 0;
	}
}

void memberlist::acceptRequest ( char * data1, char * data2 )
{
	//cout << "memberlist recR 1" << endl;
	member * receiver = search ( data1 );
	member * sender = search ( data2 );

	if ( receiver == NULL )
	{
		cout << "Error:  " << data1 << " is not a member of Phasebook!" << endl;
	}
	else if ( sender == NULL )
	{
		cout << "Error:  " << data2 << " is not a member of Phasebook!" << endl;
	}
	else
	{
		listcell * prevR = receiver->invitations_rcvd->search( data2 );
		listcell * prevS = sender->invitations_sent->search( data1 );

	
		if ( prevR == NULL )
		{
			cout << "Error:  " << data1 << " has not received a friend request from " << data2 << endl;
		}
		else if ( prevS == NULL ) 		// these conditions might not be mutually exclusive
		{
			cout << "Error:  " << data2 << " has not sent a friend request to " << data1 << endl;
		}
		else
		{
			receiver->friends->append( data2 );
			sender->friends->append( data1 );
			receiver->invitations_rcvd->delete_pointer( prevR );
			sender->invitations_sent->delete_pointer( prevS );
		}
		prevR = 0;
		prevS = 0;
	}
	receiver = 0;
	sender = 0;
	//cout << "memberlist recR 2" << endl;
}

void memberlist::rejectRequest ( char * data1, char * data2 )
{
	//cout << "memberlist rejR 1" << endl;
	member * receiver = search ( data1 );
	member * sender = search ( data2 );

	if ( sender == NULL )
	{
		cout << "Error:  " << data2 << " is not a member of Phasebook!" << endl;
	}
	else if ( receiver == NULL )
	{
		cout << "Error:  " << data1 << " is not a member of Phasebook!" << endl;
	}
	else
	{
		listcell * prevR = receiver->invitations_rcvd->search( data2 );
		listcell * prevS = sender->invitations_sent->search( data1 );

	
		if ( prevR == NULL )
		{
			cout << "Error:  " << data1 << " has not received a friend request from " << data2 << endl;
		}
		else if ( prevS == NULL ) 		// these conditions might not be mutually exclusive
		{
			cout << "Error:  " << data2 << " has not sent a friend request to " << data1 << endl;
		}
		else
		{
			receiver->invitations_rcvd->delete_pointer( prevR );
			sender->invitations_sent->delete_pointer( prevS );
		}
		prevR = 0;
		prevS = 0;
	}
	receiver = 0;
	sender = 0;
	//cout << "memberlist rejR 2" << endl;
}

void memberlist::unfriend ( char * data1, char * data2 )
{	
	//cout << "memberlist unfriend 1" << endl;
	member * agent = search ( data1 );
	member * unfriend = search ( data2 );

	if ( agent == NULL )
	{
		cout << "Error:  " << data1 << " is not a member of Phasebook!" << endl;
	}
	else if ( unfriend == NULL )
	{
		cout << "Error:  " << data2 << " is not a member of Phasebook!" << endl;
	}
	else
	{

		listcell * friend1 = agent->friends->search( data2 );
		listcell * friend2 = unfriend->friends->search( data1 );

		if ( friend1 == NULL )
		{
			cout << "Error:  " << data2 << " is not a friend of " << data1 << "!" << endl;
		}
		else if ( friend2 == NULL )
		{
			cout << "Error:  " << data1 << " is not a friend of " << data2 << "!" << endl;
		}
		else
		{
			agent->friends->delete_pointer ( friend1 );
			unfriend->friends->delete_pointer ( friend2 );
		}

		friend1 = 0;
		friend2 = 0;
	}
	agent = 0;
	unfriend = 0;
	//cout << "memberlist unfriend 2" << endl;
}

void memberlist::print ( char * data)
{
	//cout << "memberlist print 1" << endl;
	member * agent = search ( data );
	if ( agent == NULL )
	{
		cout << "Error:  " << data << " is not a member of Phasebook!" << endl;
	}
	else
	{
		cout << endl << "User: " << agent->name << endl;
	
		cout << "\tFriends: " << flush;
		cout << agent->friends;

		cout << endl << "\tFriend Requests Received: " << flush;
		cout << agent->invitations_rcvd;

		cout << endl << "\tFriend Requests Sent: " << flush;
		cout << agent->invitations_sent;

		cout << endl << endl;
	}
	//cout << "memberlist print 2" << endl;
}

void memberlist::printAll ()
{
	//cout << "memberlist printAll 1" << endl;
	member * current = head;
	if ( current == NULL )
	{
		cout << "Error:  " << "No members of Phase Book! " << endl;
	}
	else
	{
		cout << "Count:  " << count << flush;
		while (current)
		{
			print ( current->name );
			current = current->next;
		}
	}
	//cout << "memberlist printAll 2" << endl;
}
