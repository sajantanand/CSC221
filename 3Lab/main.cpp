#include <stdio.h>
#include <cstdlib>


#include "TStack.h"
#include "Token.h"
#include "SyntaxTree.h"

using namespace std;

int main ()
{
	SyntaxTree * treeS = new ( nothrow ) SyntaxTree ();
	treeS->parse();
	treeS->print();
	cout << endl;
	
	delete treeS;
	return 0;
}
