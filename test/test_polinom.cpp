#include "gtest.h"
#include "polinom.h"

TEST(TMonom, can_create_monom)
{
	ASSERT_NO_THROW(TMonom m);
}

TEST(TMonom, can_create_monom_none_empty)
{
	TMonom m;
	m.px = 0;
	m.py = 0;
	m.pz = 0;
	ASSERT_NO_THROW(m.coeff = 1);
}


TEST(TMonom, can_compare_monoms)
{
	TMonom m1, m2;
	m1.coeff = 5;
	m1.px = 1;
	m1.py = 1;
	m1.pz = 1;
	m2.coeff = 7;
	m2.px = 1;
	m2.py = 1;
	m2.pz = 1;
	EXPECT_EQ(m1 == m2, 1);
}

TEST(TMonom, can_compare_not_equal_monoms)
{
	TMonom m1, m2;
	m1.coeff = 1;
	m1.px = 1;
	m1.py = 1;
	m1.pz = 1;
	m2.coeff = 2;
	m2.px = 2;
	m2.py = 2;
	m2.pz = 2;
	EXPECT_EQ(m1 != m2, 1);
}

TEST(TMonom, can_compare_less_monoms)
{
	TMonom m1, m2;
	m1.coeff = 1;
	m1.px = 1;
	m1.py = 1;
	m1.pz = 1;
	m2.coeff = 2;
	m2.px = 2;
	m2.py = 2;
	m2.pz = 2;
	EXPECT_EQ(m1 < m2, 1);
}

TEST(TMonom, can_compare_more_monoms)
{
	TMonom m1, m2;
	m1.coeff = 1;
	m1.px = 1;
	m1.py = 1;
	m1.pz = 1;
	m2.coeff = 2;
	m2.px = 1;
	m2.py = 2;
	m2.pz = 2;
	EXPECT_EQ(m1 > m2, 0);
}

TEST(TPolynomial, can_create_polynomial)
{
	ASSERT_NO_THROW(TPolynomial p);
}

TEST(TPolynomial, can_create_polynomial_with_arr)
{
	int** arr;
	arr = new int* [2];

	for (int i = 0; i < 2; i++)
		arr[i] = new int[2];

	arr[0][0] = 1;
	arr[0][1] = 123;
	arr[1][0] = 3;
	arr[1][1] = 234;

	ASSERT_NO_THROW(TPolynomial pol(arr, 2));
	TPolynomial pol(arr, 2);

	pol.Reset();
	EXPECT_EQ(pol.GetMonom().coeff, 3);
	EXPECT_EQ(pol.GetMonom().px, 2);
	EXPECT_EQ(pol.GetMonom().py, 3);
	EXPECT_EQ(pol.GetMonom().pz, 4);
	pol.GoNext();
	EXPECT_EQ(pol.GetMonom().coeff, 1);
	EXPECT_EQ(pol.GetMonom().px, 1);
	EXPECT_EQ(pol.GetMonom().py, 2);
	EXPECT_EQ(pol.GetMonom().pz, 3);

}

TEST(TPolynomial, are_inverse_polynomials_reduced)
{
	int** arr;
	arr = new int* [2];
	for (int i = 0; i < 2; i++)
		arr[i] = new int[2];
	arr[0][0] = 1;
	arr[0][1] = 123;
	arr[1][0] = 3;
	arr[1][1] = 321;
	TPolynomial pol(arr, 2);

	int** arr2;
	arr2 = new int* [2];

	for (int i = 0; i < 2; i++)
		arr2[i] = new int[2];

	arr2[0][0] = -1;
	arr2[0][1] = 123;
	arr2[1][0] = -3;
	arr2[1][1] = 321;

	TPolynomial pol1(arr2, 2);

	int** arr3;
	arr3 = new int* [1];

	for (int i = 0; i < 1; i++)
		arr3[i] = new int[2];

	arr3[0][0] = 0;
	arr3[0][1] = 0;
	TPolynomial pol2(arr3, 1);

	pol += pol1;

	pol.Reset();

	EXPECT_EQ(pol.GetMonom().coeff, 0);
	EXPECT_EQ(pol.GetMonom().px, 0);
	EXPECT_EQ(pol.GetMonom().py, 0);
	EXPECT_EQ(pol.GetMonom().pz, -1);


}

TEST(TPolynomial, can_add_monom)
{
	TPolynomial p;
	TMonom a;
	a.coeff = 1;
	a.px = 1;
	a.py = 1;
	a.pz = 1;
	ASSERT_NO_THROW(p.AddMonom(a));
	ASSERT_NO_THROW(p * 5);
	ASSERT_NO_THROW(p *= 5);
	ASSERT_NO_THROW(p * a);
	ASSERT_NO_THROW(p *= a);
}

TEST(TPolynomial, can_copy_polynom)
{
	int** arr;
	arr = new int* [2];
	for (int i = 0; i < 2; i++)
		arr[i] = new int[2];
	arr[0][0] = 1;
	arr[0][1] = 123;
	arr[1][0] = 3;
	arr[1][1] = 321;
	TPolynomial pol(arr, 2);
	ASSERT_NO_THROW(TPolynomial p_copy(pol));
}

TEST(TPolynomial, can_add_monoms_with_opposite_signs)
{
	TPolynomial pol;
	TMonom m[3];
	for (int i = 0; i < 3; i++)
	{
		m[i].coeff = 7 * pow(-1, i);
		m[i].px = i / 2;
		m[i].py = 2;
		m[i].pz = i;
		pol.AddMonom(m[i]);
	}
	m[2].coeff = -7;
	pol.AddMonom(m[2]);
	pol.Reset();

	EXPECT_EQ(pol.GetCurrEl() == m[1], 1);
}

TEST(TPolynomial, set_to_zero) {
	TPolynomial pol;
	TMonom m;
	m.coeff = 5;
	m.px = 1;
	m.py = 1;
	m.pz = 1;
	pol.AddMonom(m);
	m.coeff = -5;
	pol.AddMonom(m);
	pol.Reset();

	EXPECT_EQ(pol.GetCurrEl().pz == -1, 1);
}

TEST(TPolynomial, check_coeff) {
	TPolynomial pol;
	TMonom m;
	m.coeff = 5;
	m.px = 1;
	m.py = 1;
	m.pz = 1;
	pol.AddMonom(m);
	pol.AddMonom(m);
	pol.Reset();
	EXPECT_EQ(pol.GetCurrEl().coeff == 10, 1);
}


TEST(TPolynom, stop)
{
	system("pause");
}