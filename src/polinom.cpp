#include "polinom.h"
#include "monom.h"


using std::string;
using std::ostream;
using std::cout;
using std::cin;
using std::istringstream;
using std::istream;
using std::endl;


Polinom::Polinom ()
{
	list.GetHead()->m = Monom(0, -1);
}

void Polinom::AddMonom(const Monom& _m) 
{
	Node* current = list.GetHead()->next;
	Node* previous = list.GetHead();

	while (_m.GetPower() < current->m.GetPower())
	{
		previous = current;
		current = current->next;
	}

	if(_m.GetPower() == current->m.GetPower())
	{
		current->m.SetCoeff(current->m.GetCoef() + _m.GetCoef());
		if(current->m.GetCoef() == 0)
		{
			List::DeleteNext(previous);
		}
	}
	else
	{
		List::Insert(previous, new Node(_m));
	}
}

Polinom Polinom:: operator + (Polinom& P)
{
	Polinom Q(*this);
	Node* p = P.list.GetHead()->next;
	Node* q = Q.list.GetHead()->next;
	Node* q1 = Q.list.GetHead();

	while(true)
	{
		if(p->m.GetPower() == q->m.GetPower())
		{
			if(p->m.GetPower() == -1)
			{
				break;
			}
			else
			{
				q->m.SetCoeff(q->m.GetCoef() + p->m.GetCoef());
				p = p->next;

				if(q->m.GetCoef() == 0)
				{
					List::DeleteNext(q1);
					q = q1->next;
				}
				else
				{
					q1 = q;
					q = q->next;
				}
			}
		}
		else
		{
			if(p->m.GetPower() < q->m.GetPower())
			{
				q1 = q;
				q = q->next;
			}
			else
			{
				List::Insert(q1, new Node(p->m));
				q1 = q1->next;
				p = p->next;
			}
		}
	}
	return Q;
}

Polinom Polinom::operator - (Polinom& p)
{
	return *this + p*(-1);

}

Polinom Polinom::operator*(Polinom& p)
{
	Polinom temp;
	Node * current1 = this->list.GetHead()->next;

	while (current1->m.GetPower() != -1)
	{
		Node * current2 = p.list.GetHead()->next;

		while (current2->m.GetPower() != -1)
		{
			temp.AddMonom(current1->m * current2->m);
			current2 = current2->next;
		}

		current1 = current1->next;
	}

	return temp;
}

Polinom Polinom::operator * (double number)
{
	if (number == 0)
	{
		Polinom Q;

		return Q;
	}

	Polinom Q(*this);
	Node* current = Q.list.GetHead()->next;

	while (current->m.GetPower() != -1)
	{
		current->m.SetCoeff(current->m.GetCoef() * number);
		current = current->next;
	}

	return Q;
}

string Polinom::toStr()
{
	string res;

	Node* current = this->list.GetHead()->next;
	res += current->m.toStr();
	current = current->next;

	while (current->m.GetPower() != -1)
	{
		if (current->m.GetCoef() > 0)
			res += " + " + current->m.toStr();
		else
			res += " " + current->m.toStr();
		current = current->next;
	}

	return res;
}

ostream& operator << (ostream& ostr, Polinom& p)
{
	Node * current = p.list.GetHead()->next;
	cout << current->m;
	current = current->next;

	while (current->m.GetPower() != -1)
	{
		if (current->m.GetCoef()>0)
			cout << " + " << current->m;
		else
			cout << " " << current->m;
		current = current->next;
	}

	cout << endl;

	return ostr;
}

istream& operator >> (std::istream& istr, Polinom& p)
{
	string input;
	getline(istr, input);
	string temporary;

	for (int j = 0; j < input.length(); j++)
	{
		if (input[j]!=' ')
			temporary.push_back(input[j]);
	}

	for (int i = 0; i < temporary.length(); i++)
	{
		Monom m;
		int coeff;
		if (temporary[i]=='+')
			i++;
		int x=0, y=0, z=0;
		if ((isdigit(temporary[i])) || ((temporary[i]) == '-') && (isdigit(temporary[i+1])))
		{
			string temp;
			while ((temporary[i] != 'x')&&(temporary[i] != 'y')&&(temporary[i] != 'z')&&(i!=temporary.length()))
			{
				temp += temporary[i];

				if (i!=temporary.length()-1)
				{
					i++;
				}
				else	
					break;
				
				if ((temporary[i]=='+')||(temporary[i]=='-'))
				{
					break;
				}
			}

			istringstream(temp) >> coeff;
			m.SetCoeff(coeff);

			if (((temporary[i]!='x')&&(temporary[i]!='y')&&(temporary[i]!='z'))&&((temporary[i]=='+')||(temporary[i]=='-')))
			{
				m.SetPower(x, y, z);
				p.AddMonom(m);
				i--;

				continue;
			}

			if (((temporary[i]!='x')&&(temporary[i]!='y')&&(temporary[i]!='z'))&&(i==temporary.length()-1))
			{
				m.SetPower(x, y, z);
				p.AddMonom(m);
				i--;

				break;
			}

		}
		else
		{
			if ((temporary[i] == 'x')||(temporary[i] == 'y')||(temporary[i] == 'z'))
			{
				m.SetCoeff(1);
			}
			else if ((temporary[i]=='-')&&((temporary[i+1] == 'x')||(temporary[i+1] == 'y')||(temporary[i+1] == 'z')))
				{
					m.SetCoeff(-1);
					i++;
				}
				else
				{
					throw "Incorrect entries";
				}

		}

		if ((temporary[i]!='+')&&(temporary[i]!='-'))
		{

			if (temporary[i]=='x')
			{
				if(i!=temporary.length()-1)
				{
					i++;

					if ((temporary[i]!='+')&&(temporary[i]!='-'))
					{
						if ((temporary[i]!='^'))
						{
							if((temporary[i]!='y')&&(temporary[i]!='z'))
							{
								throw "Incorrect entries";
							}
							else
								x=1;
						}
						else
							if(i==temporary.length()-1)
							{
								throw "Incorrect entries";
							}
					}
					else
					{
						i--;
						x = 1;
						m.SetPower(x, y, z);
						p.AddMonom(m);

						continue;
					}
				}
				else
				{

					x = 1;
					m.SetPower(x, y, z);
					p.AddMonom(m);
					break;
				}

				if (temporary[i]=='^')
				{
					if ((isdigit(temporary[i+1])))
					{
						i++;
						string temp_x;
						temp_x = temporary[i];
						istringstream(temp_x) >> x;

						if (i!=temporary.length()-1)
						{
							i++;
						}
						else
						{
							m.SetPower(x, y, z);
							p.AddMonom(m);

							break;
						}

						if ((temporary[i]=='+')||(temporary[i]=='-'))
						{
							i--;
							m.SetPower(x, y, z);
							p.AddMonom(m);

							continue;
						}
					}
					else 
						throw "Incorrect entries";
				}

			}
			else
				if ((temporary[i]!='y')&&(temporary[i]!='z'))
					throw "Incorrect entries";
		}

		if ((temporary[i]!='+')&&(temporary[i]!='-'))
		{
			if (temporary[i]=='y')
			{
				if(i!=temporary.length()-1)
				{
					i++;

					if ((temporary[i]!='+')&&(temporary[i]!='-'))
					{
						if ((temporary[i]!='^'))
						{
							if(temporary[i]!='z')
							{
								throw "Incorrect entries";
							}
							else
								y = 1;
						}
						else
							if(i==temporary.length()-1)
							{
								throw "Incorrect entries";
							}
					}
					else
					{
						i--;
						y = 1;
						m.SetPower(x, y, z);
						p.AddMonom(m);
						continue;
					}
				}
				else
				{
					y = 1;
					m.SetPower(x, y, z);
					p.AddMonom(m);
					break;
				}

				if (temporary[i]=='^')
				{
					if (isdigit(temporary[i+1]))
					{
						i++;
						string temp_y;
						temp_y = temporary[i];
						istringstream(temp_y) >> y;
						if (i!=temporary.length()-1)
						{
							i++;
						}
						else
						{
							m.SetPower(x, y, z);
							p.AddMonom(m);
							break;
						}
						if ((temporary[i]=='+')||(temporary[i]=='-'))
						{
							i--;
							m.SetPower(x, y, z);
							p.AddMonom(m);
							continue;
						}
					}
					else 
						throw "Incorrect entries";
				}
			}

			else
				if (temporary[i]!='z')
					throw "Incorrect entries";
		}


		if ((temporary[i]!='+')&&(temporary[i]!='-'))
		{
			if (temporary[i]!='z')
			{
				throw "Incorrect entries";
			}
			else
				if(i!=temporary.length()-1)
				{
					i++;

					if ((temporary[i]!='+')&&(temporary[i]!='-'))
					{
						if ((temporary[i]!='^'))
						{
							throw "Incorrect entries";
						}
						else
							if(i==temporary.length()-1)
							{
								throw "Incorrect entries";
							}
					}
					else
					{
						i--;
						z = 1;
						m.SetPower(x, y, z);
						p.AddMonom(m);

						continue;
					}
				}
				else
				{
					z = 1;
					m.SetPower(x, y, z);
					p.AddMonom(m);

					break;
				}
				if (temporary[i]=='^')
				{

					if (isdigit(temporary[i+1]))
					{
						i++;
						string temp_z;
						temp_z = temporary[i];
						istringstream(temp_z) >> z;
					}
					else 
						throw "Incorrect entries";
				}
		}
		m.SetPower(x, y, z);
		p.AddMonom(m);
	}
	return istr;
}