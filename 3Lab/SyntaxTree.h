#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include <iostream>
#include <cassert>
#include <stdio.h>

#define DEBUG 0

using namespace std;

class TreeNode
{
	private:
		Token * data;
		TreeNode * leftC;
		TreeNode * rightC;

	public:
		TreeNode ( Token * contents );
		~TreeNode ();
		Token * getContent () const;
		TreeNode * & getLeft ();
		TreeNode * & getRight ();
		void print() const;

		friend class SyntaxTree;
};

class SyntaxTree
{
	private:
		TreeNode * root;
		int parenNeeded ( TreeNode * node ) const;
		void printInOrder ( TreeNode * ptr ) const;
	public:
		SyntaxTree ();
		~SyntaxTree ();
		TreeNode * getRoot () const;
		void parse ();
		void print () const;
};

bool operatorW ( TreeNode * ptr );
int precedenceW ( TreeNode * ptr );


#endif
