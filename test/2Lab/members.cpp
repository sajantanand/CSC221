#include <cstdlib>
#include <assert.h>
#include <cstring>
#include <iostream>

#include "members.h"
#include "namelist.h"

using namespace std;

member::member()
{
	name = NULL;
	friends = NULL;
	invitations_rcvd = NULL;
	invitations_sent = NULL;
	next = NULL;
	prev = NULL;
}

member::member ( const char * data )
{
	strcpy(name, data);
	friends = NULL;
	invitations_rcvd = NULL;
	invitations_sent = NULL;
	next = NULL;
	prev = NULL;
}

member::~member()
{
	if ( name ) {	delete [] name;	}
	if ( friends ) {	delete [] friends;	}
	if ( invitations_rcvd ) {	delete [] invitations_rcvd;	}
	if ( invitations_sent ) {	delete [] invitations_sent;	}
	if ( next ) {	delete [] next;	}
	if ( prev ) {	delete [] prev;	}
}

memberlist::memberlist()
{
	head = NULL;
	tail = NULL;
}

memberlist::~memberlist()
{
	if ( head ) {	delete head;	}
}

member * memberlist::search ( char * data)
{
	bool notFound = true;
	member * current = head;
	
	if ( current )
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

void memberlist::join ( char * data )
{
	member * temp = search ( data );
	if ( temp )
	{
		cout << *data << " is already a member of PhaseBook!" << endl;
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
	}
}

void memberlist::quit ( char * data )
{
	member * temp = search ( data );
	if ( temp == NULL )
	{
		cout << *data << " is not a member of PhaseBook!" << endl;
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
			aFriend->invitations_sent->delete_here ( data );
			memFriends = memFriends->next;
			aFriend = 0;
		}
	}
}

void memberlist::sendRequest ( char * data1, char * data2 )
{
	member * sender = search ( data1 );
	member * receiver = search ( data2 );

	if ( sender == NULL )
	{
		cout << *data1 << "is not a member of Phasebook!" << endl;
	}
	if ( receiver == NULL )
	{
		cout << *data2 << "is not a member of Phasebook!" << endl;
	}

	listcell * prevR = receiver->invitations_rcvd->search( data1 );
	listcell * prevS = sender->invitations_rcvd->search( data2 );
	listcell * friendR = receiver->friends->search( data1 );
	
	if ( prevR && prevS )
	{
		receiver->friends->append( data1 );
		sender->friends->append( data2 );

		receiver->invitations_rcvd->delete_here( data1 );
		receiver->invitations_sent->delete_here( data1 );
		sender->invitations_rcvd->delete_here( data2 );
		sender->invitations_sent->delete_here( data2 );
	}
	else if ( prevR )
	{
		cout << *data1 << " has already sent a friend request to " << *data2 << endl;
	}
	else if ( friendR )
	{
		cout << *data1 << " is already friends with " << *data2 << endl;
	}
	else if ( prevS )
	{
		receiver->friends->append( data1 );
		sender->friends->append( data2 );

		receiver->invitations_sent->delete_here( data1 );
		sender->invitations_rcvd->delete_here( data2 );
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

void memberlist::acceptRequest ( char * data1, char * data2 )
{
	member * receiver = search ( data1 );
	member * sender = search ( data2 );

	if ( sender == NULL )
	{
		cout << *data1 << "is not a member of Phasebook!" << endl;
	}
	if ( receiver == NULL )
	{
		cout << *data2 << "is not a member of Phasebook!" << endl;
	}

	listcell * prevR = receiver->invitations_rcvd->search( data2 );
	listcell * prevS = sender->invitations_sent->search( data1 );

	
	if ( prevR == NULL )
	{
		cout << *data1 << " has not received a friend request from " << *data2 << endl;
	}
	else if ( prevS == NULL ) 		// these conditions might not be mutually exclusive
	{
		cout << *data2 << " has not sent a friend request to " << *data1 << endl;
	}
	else
	{
		receiver->friends->append( data2 );
		sender->friends->append( data1 );

		receiver->invitations_rcvd->delete_here( data2 );
		sender->invitations_sent->delete_here( data1 );
	}

	receiver = 0;
	sender = 0;
	prevR = 0;
	prevS = 0;
}

void memberlist::rejectRequest ( char * data1, char * data2 )
{
	member * receiver = search ( data1 );
	member * sender = search ( data2 );

	if ( sender == NULL )
	{
		cout << *data1 << "is not a member of Phasebook!" << endl;
	}
	if ( receiver == NULL )
	{
		cout << *data2 << "is not a member of Phasebook!" << endl;
	}

	listcell * prevR = receiver->invitations_rcvd->search( data2 );
	listcell * prevS = sender->invitations_sent->search( data1 );

	
	if ( prevR == NULL )
	{
		cout << *data1 << " has not received a friend request from " << *data2 << endl;
	}
	else if ( prevS == NULL ) 		// these conditions might not be mutually exclusive
	{
		cout << *data2 << " has not sent a friend request to " << *data1 << endl;
	}
	else
	{
		receiver->invitations_rcvd->delete_here( data2 );
		sender->invitations_sent->delete_here( data1 );
	}
	
	receiver = 0;
	sender = 0;
	prevR = 0;
	prevS = 0;
}

void memberlist::unfriend ( char * data1, char * data2 )
{	
	member * agent = search ( data1 );
	member * unfriend = search ( data2 );

	if ( agent == NULL )
	{
		cout << *data1 << "is not a member of Phasebook!" << endl;
	}
	if ( unfriend == NULL )
	{
		cout << *data2 << "is not a member of Phasebook!" << endl;
	}

	listcell * friend1 = agent->friends->search( data2 );
	listcell * friend2 = unfriend->friends->search( data1 );

	if ( friend1 == NULL )
	{
		cout << *data2 << "is not a friend of " << data1 << " !" << endl;
	}
	else if ( friend2 == NULL )
	{
		cout << *data1 << "is not a friend of " << data2 << " !" << endl;
	}
	else
	{
		agent->friends->delete_here ( data2 );
		unfriend->friends->delete_here ( data1 );
	}

	agent = 0;
	unfriend = 0;
	friend1 = 0;
	friend2 = 0;
}

void memberlist::print ( char * data)
{
	member * agent = search ( data );
	
	cout << "User: " << agent->name << endl;
	cout << "Friends: ";

	listcell * aFriends = agent->friends->head;
	while ( aFriends )
	{
		cout << aFriends->name << ", ";
		aFriends->next;
	}

	cout << endl << "Friend Requests Received: ";
	aFriends = agent->invitations_rcvd->head;
	while ( aFriends )
	{
		cout << aFriends->name << ", ";
		aFriends->next;
	}

	cout << endl << "Friend Requests Sent: ";
	aFriends = agent->invitations_sent->head;
	while ( aFriends )
	{
		cout << aFriends->name << ", ";
		aFriends->next;
	}

	cout << endl;
}

void memberlist::printALL ()
{
	member * current = head;
	while (current)
	{
		print ( current->name );
	}
}


























			
			
