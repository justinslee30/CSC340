#include <iostream>
using namespace std;

int main()
{
	int *p1 = new int;
	int *p2 = new int;
	*p1 = 10;
	p2 = &*p1;
	cout << "Address of p1: " << p1 << endl;
	cout << "Address of p2: " << p2 << endl;
	cout << "Value at p1: " << *p1 << endl;
	cout << "Value at p2: " << *p2 << endl;
	delete p1;
	cout << "--- DELETED P1 ---" << endl;
	cout << "Address of p1: " << p1 << endl;
	cout << "Address of p2: " << p2 << endl;
	cout << "Value at p1: " << *p1 << endl;
	cout << "Value at p2: " << *p2 << endl;
	delete p2;
	cout << "--- DELETED P2 ---" << endl;
	cout << "Address of p1: " << p1 << endl;
	cout << "Address of p2: " << p2 << endl;
	cout << "Value at p1: " << *p1 << endl;
	cout << "Value at p2: " << *p2 << endl;
	return 0;
}