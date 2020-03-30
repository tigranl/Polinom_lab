#pragma once
#include <iostream>
#include "list.h"

using namespace std;

struct TMonom {
	double coeff;
	int px, py, pz;

	TMonom() {
		coeff = 0;
		px = py = pz = 0;
	}

	TMonom(int arr[1][2]) {
		coeff = arr[0][0];
		px = arr[0][1] / 100;
		py = arr[0][1] / 10 % 10;
		pz = arr[0][1] % 10;
	}

	bool operator< (TMonom& m) {
		int st_f, st_s;
		st_f = px * 100 + py * 10 + pz;
		st_s = m.px * 100 + m.py * 10 + m.pz;
		if (st_f < st_s)
		{
			return true;
		}
		else {
			return false;
		}
	}

	bool operator<= (TMonom& m) {
		int st_f, st_s;
		st_f = px * 100 + py * 10 + pz;
		st_s = m.px * 100 + m.py * 10 + m.pz;
		if (st_f < st_s)
		{
			return true;
		}
		else {
			return false;
		}
	}

	bool operator> (TMonom& m) {
		int st_f, st_s;
		st_f = px * 100 + py * 10 + pz;
		st_s = m.px * 100 + m.py * 10 + m.pz;
		if (st_f > st_s)
		{
			return true;
		}
		else {
			return false;
		}
	}

	bool operator>= (TMonom& m) {
		int st_f, st_s;
		st_f = px * 100 + py * 10 + pz;
		st_s = m.px * 100 + m.py * 10 + m.pz;
		if (st_f > st_s)
		{
			return true;
		}
		else {
			return false;
		}
	}

	bool operator== (TMonom& mon) {
		if ((px == mon.px) && (py == mon.py) && (pz == mon.pz))
			return true;
		else
			return false;
	}
	bool operator!= (TMonom& mon) {
		if (*this == mon)
			return false;
		else
			return true;
	}

};
class TPolynomial : public THeadList<TMonom> {
public:

	TPolynomial() : THeadList<TMonom>() {
		pHead->val.pz = -1;
	}

	TPolynomial(int** arr, int sizep) : THeadList<TMonom>() {
		pHead->val.pz = -1;
		for (int i = 0; i < sizep; i++) {
			TMonom mon;
			mon.coeff = arr[i][0];
			mon.px = arr[i][1] / 100;
			mon.py = arr[i][1] / 10 % 10;
			mon.pz = arr[i][1] % 10;
			AddMonom(mon);
		}
	}

	TPolynomial(TPolynomial& p) : THeadList<TMonom>() {
		pHead->val.pz = -1;
		for (p.Reset(); !p.IsEnd(); p.GoNext()) {
			TMonom mon = p.pCurr->val;
			AddMonom(mon);
		}
	}

	void operator= (TPolynomial& p) {
		DelList();
		Reset();
		for (p.Reset(); !p.IsEnd(); p.GoNext()) {
			AddMonom(p.pCurr->val);
		}
	}

	TMonom& GetMonom() {
		return pCurr->val;
	}


	void AddMonom(TMonom mon) {
		for (Reset(); !IsEnd(); GoNext()) {
			if (mon == GetMonom()) {
				double tmp = mon.coeff + GetMonom().coeff;
				if (tmp)
					pCurr->val.coeff = tmp;
				else
					DelCurr();
				return;
			}
			if (mon > GetMonom()) {
				InsCurr(mon);
				return;
			}
		}
		InsLast(mon);
	}


	void operator *= (double a) {
		for (Reset(); !IsEnd(); GoNext()) {
			pCurr->val.coeff *= a;
		}
	}

	void operator*= (TMonom mon) {
		for (Reset(); !IsEnd(); GoNext()) {
			pCurr->val.coeff *= mon.coeff;
			pCurr->val.px += mon.px;
			pCurr->val.py += mon.py;
			pCurr->val.pz += mon.pz;
		}
		return;
	}

	TPolynomial operator* (TMonom mon) {
		TPolynomial res = *this;
		res *= mon;
		return res;
	}

	void operator+=(TPolynomial& q) {
		TMonom pm, qm, rm;
		Reset();
		q.Reset();
		while (!q.IsEnd()) {

			pm = pCurr->val;
			qm = q.pCurr->val;

			if (pm > qm) GoNext();
			else {
				if (pm < qm) {

					InsCurr(qm);
					q.GoNext();

				}
				else {
					if (pm == qm) {

						rm = pm;
						rm.coeff += qm.coeff;

						if (rm.coeff == 0) {
							DelCurr();
							q.GoNext();
						}

						else {

							pCurr->val = rm;

							if (&q == this) {
								GoNext();
							}
							else
							{
								q.GoNext();
								GoNext();

							}
						}
					}
				}
			}
		}
	}
	TPolynomial operator+ (TPolynomial& pol) {
		TPolynomial res = *this;
		res += pol;
		return res;
	}

	TPolynomial operator* (double a) {
		TPolynomial res(*this);
		for (res.Reset(); !res.IsEnd(); res.GoNext())
		{
			res.pCurr->val.coeff *= a;
			if (res.pCurr->val.coeff == 0)
			{
				res.DelCurr(); break;
			}
		}
		return res;
	}


	friend std::ostream& operator<<(std::ostream& os, TPolynomial& p) {
		for (p.Reset(); !p.IsNextLast(); p.GoNext()) {
			std::cout << p.pCurr->val.coeff << "*x^" << p.pCurr->val.px << "y^" << p.pCurr->val.py << "z^" << p.pCurr->val.pz << " + ";//<<  std::endl;
		}

		std::cout << p.pCurr->val.coeff << "*x^" << p.pCurr->val.px << "y^" << p.pCurr->val.py << "z^" << p.pCurr->val.pz << std::endl;
		return os;
	}
};
