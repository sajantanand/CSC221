#include<iostream>
using namespace std;

int main()
{
	int * x = new (nothrow) int(4);
	cout << x << endl;
	cout << *x << endl;

	return 0;
}
