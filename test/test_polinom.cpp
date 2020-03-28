#include <gtest.h>
#include "polinom.h"


TEST(Polynom, can_use_constructor)
{
	ASSERT_NO_THROW(Polinom p());
}

TEST(Polynom, can_use_toStr)
{
	Polinom p;
	Monom m(5, 123);

	p.AddMonom(m);

	ASSERT_NO_THROW(p.toStr());
}

TEST(Polynom, can_correct_use_toStr)
{
	Polinom p;
	Monom m(4, 123);

	p.AddMonom(m);

	EXPECT_EQ(p.toStr(), "4x^1y^2z^3");
}

TEST(Polynom, can_correct_add_monom)
{
	Polinom p;
	Monom m(5, 123);

	p.AddMonom(m);

	EXPECT_EQ(p.toStr(), "5x^1y^2z^3");
}

TEST(Polynom, can_add_monom)
{
	Polinom p;
	Monom m(5, 123);

	ASSERT_NO_THROW(p.AddMonom(m));
}

TEST(Polynom, can_correct_use_plus)
{
	Polinom p, q, res;
	Monom m(1, 123);
	Monom n(1, 123);

	p.AddMonom(m);
	q.AddMonom(n);

	res = p + q;

	EXPECT_EQ(res.toStr(), "2x^1y^2z^3");
}

TEST(Polynom, can_sort_monoms)
{
	Polinom p, q, res;
	Monom m(2, 111);
	Monom n(3, 333);

	q.AddMonom(n);
	p.AddMonom(m);


	res = p + q;

	EXPECT_EQ(res.toStr(), "3x^3y^3z^3 + 2x^1y^1z^1");
}


TEST(Polynom, can_correctly_use_minus)
{
	Polinom p, q, res;
	Monom m(4, 456);
	Monom n(5, 456);

	p.AddMonom(m);
	q.AddMonom(n);

	res = p - q;

	EXPECT_EQ(res.toStr(), "-1x^4y^5z^6");
}
