#pragma once
#include <iostream>
#include <string>

class Monom
{
private:
	double coef;
	int power;
public:
	Monom(int _coef, int x, int y, int z);
	Monom(int _coef = 0, int _power = 0);
	int GetCoef() const;
	int GetX() const;
	int GetY() const;
	int GetZ() const;
	int GetPower() const;
	void SetCoeff(int _coef);
	void SetPower (int x, int y, int z);
	Monom operator* (const Monom& m);
	std::string toStr();
};

std::ostream& operator << (std::ostream& ostr, const Monom& m);
