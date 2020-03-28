#include "list.h"
#include "polinom.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

void main()
{
	try
	{
		Polinom p;
		Polinom q;
		Polinom res;
		int operation;

		cout << "Enter polinom P" << endl;
		cin >> p;
		cout << endl;

		cout << "Enter polinom Q" << endl;
		cin >> q;
		cout << endl;

		cout << "Select an operation:" << endl;
		cout << "1: P + Q" << endl;
		cout << "2: P - Q" << endl;
		cout << endl;

		cin >> operation;
		cout << endl;

		bool fl = true;

		switch(operation)
		{
			case 1:
			{
				res = p + q;
				break;
			}
			case 2:
			{
				res = p - q;
				break;
			}
			default:
			{
				fl = false;
				cout << "Incorrect input!" << endl;
				break;
			}
		}

		if (fl)
		{
			cout << "Result: " << res << endl;
			cout << res.toStr() << endl;
		}
	}
	catch (const char* error)
	{
		cout<< error <<endl;
	}
}