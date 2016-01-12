#include <iostream>
using namespace std;

int main()
{
	char instruction[50];
	char data1[20];
	char data2[20];
	//cin >> instruction;
	cin.getline(instruction, 50);
	cout << instruction << endl;
	return 0;
}
