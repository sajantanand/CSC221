#include "Token.h"
#include "TStack.h"
#include "SyntaxTree.h"

TreeNode::TreeNode ( Token * contents )
{
	if ( DEBUG ) cout << "TreeNode constructor BEGIN" << endl;
	data = contents;
	leftC = NULL;
	rightC = NULL;
	if ( DEBUG ) cout << "TreeNode constructor END" << endl;
}

TreeNode::~TreeNode ()
{
	
	if ( DEBUG ) cout << "TreeNode destructor BEGIN" << endl;
	delete data;
	if ( leftC )delete leftC;
	leftC = 0;
	if ( rightC )delete rightC;
	rightC = 0;
	if ( DEBUG ) cout << "TreeNode destructor END" << endl;
	
}

Token * TreeNode::getContent () const
{
	if ( DEBUG ) cout << "TreeNode getContent BEGIN" << endl;
	return data;
	if ( DEBUG ) cout << "TreeNode getContent END" << endl;
}

TreeNode * & TreeNode::getLeft ()
{
	if ( DEBUG ) cout << "TreeNode getLeft BEGIN" << endl;
	return leftC;
	if ( DEBUG ) cout << "TreeNode getLeft END" << endl;
}

TreeNode * & TreeNode::getRight ()
{
	if ( DEBUG ) cout << "TreeNode getRight BEGIN" << endl;
	return rightC;
	if ( DEBUG ) cout << "TreeNode getRight END" << endl;
}

void TreeNode::print() const
{
	if ( DEBUG ) cout << "TreeNode print BEGIN" << endl;
	data->print ();
	if ( DEBUG ) cout << "TreeNode print END" << endl;
}

SyntaxTree::SyntaxTree ()
{
	if ( DEBUG ) cout << "SyntaxTree constructor BEGIN" << endl;
	root = 0;
	if ( DEBUG ) cout << "SyntaxTree constructor END" << endl;
}

SyntaxTree::~SyntaxTree ()
{
	
	if ( DEBUG ) cout << "SyntaxTree destructor BEGIN" << endl;
	if ( root ) delete root;
	if ( DEBUG ) cout << "SyntaxTree destructor END" << endl;
	
}

TreeNode * SyntaxTree::getRoot () const
{
	if ( DEBUG ) cout << "SyntaxTree getRoot BEGIN" << endl;
	return root;
	if ( DEBUG ) cout << "SyntaxTree getRoot END" << endl;
}

void SyntaxTree::parse ()
{
	if ( DEBUG ) cout << "SyntaxTree parse BEGIN" << endl;
	TStack< Token * > stackO ( 5 );
	TStack< TreeNode * > stackT ( 5 );
	TreeNode * nodeT;
	tokentype placeHolder;

	char * test = NULL;
	size_t n;
	int place = 0;
	getline ( &test, &n, stdin );

	if ( DEBUG ) cout << "Entry String: " << test << endl;

	do
	{
		Token * temp = new ( nothrow ) Token ();
		temp->get_next ( test, place );
		placeHolder = temp->get_type();
		if ( DEBUG ) cout << "Got token" << endl;
		if ( DEBUG ) temp->print();
		if ( DEBUG ) cout << "Printed token" << endl;
		switch ( placeHolder )
		{
			case no_more:
			{
				break;
			}

			case leftP:
			{
				stackO.push ( temp );
				break;
			}

			case number:
			case variable:
			{
				nodeT = new ( nothrow ) TreeNode ( temp );
				stackT.push ( nodeT ); 
				break;
			}
		
			case rightP:
			{
				while ( stackO.top_of_stack()->get_type() != leftP )
				{
					if ( stackO.isEmpty() )
					{
						cout << "Stack is empty when it shouldn't be. . ." << endl;
						exit ( 1 );
					}
				
					nodeT = new ( nothrow ) TreeNode ( stackO.pop() );
					stackT.build_tree ( nodeT );
				}
				stackO.pop();
				break;
			}
			
			case add:
			case subtract:
			case multiply:
			case divide:
			{
				while ( ( stackO.size() > 0 ) && precedence ( placeHolder ) <= precedence ( stackO.top_of_stack()->get_type() ) )
				{
					nodeT = new ( nothrow ) TreeNode ( stackO.pop() );
					stackT.build_tree ( nodeT );
				}
				stackO.push ( temp );
				break;
			}

			case exponent:
			{
				stackO.push ( temp );
				break;
			}
		}
		if ( placeHolder == no_more ) delete temp;
		nodeT = 0;
	} while ( placeHolder != no_more );

	if ( test ) free ( test );
	while ( ! ( stackO.isEmpty() ) )
	{
		nodeT = new ( nothrow ) TreeNode ( stackO.pop() );
		stackT.build_tree ( nodeT );
	}
										//LOOK INTO THIS
	if ( stackT.isEmpty() )
	{
		cout << "Stack is empty when it shouldn't be. . ." << endl;
		exit ( 1 );
	}

	root = stackT.pop ();

	if ( ! ( stackT.isEmpty() ) )
	{
		cout << "Stack isn't empty when it should be. . ." << endl;
		exit ( 1 );;
	}

	if ( DEBUG ) cout << "Assign root" << endl;

	if ( DEBUG ) cout << "SyntaxTree parse END" << endl;

	//delete & temp;
}

void SyntaxTree::print () const
{
	if ( DEBUG ) cout << "SyntaxTree print BEGIN" << endl;
	printInOrder( root );
	if ( DEBUG ) cout << "SyntaxTree print END" << endl;
}

void SyntaxTree::printInOrder ( TreeNode * ptr ) const
{
	if ( DEBUG ) cout << "SyntaxTree printPreOrder BEGIN" << endl;
	int parens = parenNeeded ( ptr );

	if ( parens == 1 || parens == 3 ) cout << "(";
	if ( ptr->leftC ) printInOrder ( ptr->leftC );
	if ( parens == 1 || parens == 3 ) cout << ")";

	ptr->print();

	if ( parens == 2 || parens == 3 ) cout << "(";
	if ( ptr->rightC ) printInOrder ( ptr->rightC );
	if ( parens == 2 || parens == 3 ) cout << ")";

	if ( DEBUG ) cout << "SyntaxTree printPreOrder END" << endl;
}

int SyntaxTree::parenNeeded ( TreeNode * node ) const
{
	int total = 0;
	int place = 0;
	if ( DEBUG ) cout << "SyntaxTree parenNeeded BEGIN" << endl;
	if ( !( node->leftC  && node->rightC ) )
	{
		if ( DEBUG ) cout << "SyntaxTree parenNeeded 1" << endl;
		return 0;
	}
	if ( ( precedenceW ( node ) == precedenceW ( node->leftC ) ) && ( node->getContent()->get_type () == exponent ) )
	{
		if ( DEBUG ) cout << "SyntaxTree parenNeeded 2" << endl;
		place = 1;
		total++;
	}
	if ( ( precedenceW ( node ) == precedenceW ( node->rightC ) ) && ( node->getContent()->get_type () != exponent ) )
	{
		if ( DEBUG ) cout << "SyntaxTree parenNeeded 3" << endl;
		place = 2;
		total++;
	}
	if ( operatorW ( node->leftC ) )
	{
		if ( precedenceW ( node ) > precedenceW ( node->leftC ) )
		{
			if ( DEBUG ) cout << "SyntaxTree parenNeeded 4" << endl;
			place = 1;
			total++;
		}
	}
	if ( operatorW ( node->rightC ) )
	{
		if ( precedenceW ( node ) > precedenceW ( node->rightC ) )
		{
			if ( DEBUG ) cout << "SyntaxTree parenNeeded 5" << endl;
			place = 2;
			total++;
		}
	}
	if ( DEBUG ) cout << "SyntaxTree parenNeeded 6" << endl;
	if ( total >= 2 ) return 3;
	else return place;
	return 0;
}

bool operatorW ( TreeNode * ptr )
{
	if ( DEBUG ) cout << "SyntaxTree operatorW" << endl;
	return isOperator ( ptr->getContent()->get_type () );
}

int precedenceW ( TreeNode * ptr )
{
	if ( DEBUG ) cout << "SyntaxTree precedenceW" << endl;
	return precedence ( ptr->getContent()->get_type () );
}


