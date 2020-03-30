#include <iostream>
#include "polinom.h"

using namespace std;

int main() {

	int size;
	int column = 2;
	int** arr;
	cout << "Polynomial P" << endl;
	cout << "Enter the first polynomial's size: " << endl;
	cin >> size;
	arr = new int* [size];
	for (int i = 0; i < size; i++)
		arr[i] = new int[column];

	for (int i = 0; i < size; i++) {
		cout << "Enter " << i << " coefficient" << endl;
		cin >> arr[i][0];
		cout << "Enter the powers" << endl;
		cin >> arr[i][1];
	}
	TPolynomial pol(arr, size);
	cout << "The first polynom: " << pol;


	int** arr2;
	cout << "Polynom Q" << endl;
	cout << "Enter the second polynomial's size: " << endl;
	cin >> size;
	arr2 = new int* [size];
	for (int i = 0; i < size; i++)
		arr2[i] = new int[column];

	for (int i = 0; i < size; i++) {
		cout << "Enter " << i << " coefficient" << endl;
		cin >> arr2[i][0];
		cout << "Enter powers" << endl;
		cin >> arr2[i][1];
	}
	TPolynomial pol1(arr2, size);
	cout << "The second polynomial: " << arr2 << endl;

	pol += pol1;
	cout << "P + Q = " << pol << endl;

	int monomMas[1][2];
	cout << "Enter monom's coefficient" << endl;
	cin >> monomMas[0][0];
	cout << "Enter monom's powers" << endl;
	cin >> monomMas[0][1];
	TMonom mon2(monomMas);
	pol1.AddMonom(mon2);
	cout << pol1 << endl;

}