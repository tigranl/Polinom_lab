#include <gtest.h>
#include "monom.h"


TEST(Monom, can_create_monom)
{
	ASSERT_NO_THROW(Monom a(5, 123));
}

TEST(Monom, can_get_power)
{
	Monom m(2, 123);

	EXPECT_EQ(123, m.GetPower());
}

TEST(Monom, can_set_power)
{
	Monom m(5, 123);
	m.SetPower(4, 5, 6);

	EXPECT_EQ(456, m.GetPower());
}

TEST(Monom, can_get_x)
{
	Monom m(2, 123);

	EXPECT_EQ(1, m.GetX());
}

TEST(Monom, can_get_y)
{
	Monom m(2, 123);

	EXPECT_EQ(2, m.GetY());
}

TEST(Monom, can_get_z)
{
	Monom m(2, 123);

	EXPECT_EQ(3, m.GetZ());
}

TEST(Monom, can_get_coef)
{
	Monom m(5, 123);

	EXPECT_EQ(5, m.GetCoef());
}

TEST(Monom, can_set_coef)
{
	Monom m(5, 321);
	m.SetCoeff(10);

	EXPECT_EQ(10, m.GetCoef());
}

TEST(Monom, can_multiply_coeffs)
{
	Monom a(5, 321);
	Monom b(10, 123);
	Monom res = a * b;

	EXPECT_EQ(50, res.GetCoef());
}

TEST(Monom, can_multiply_powers)
{
	Monom a(2, 123);
	Monom b(4, 456);
	Monom res = a * b;

	EXPECT_EQ(579, res.GetPower());
}