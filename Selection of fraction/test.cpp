#include "pch.h"
#include "Approximations.h"

TEST(TestCase, Pi) {
	double error = 1.0e-10;
	Approximations obj(3.1415926535);
	obj(error);
	std::vector<Fraction> result = obj.get_fractions();
	std::vector<Fraction> expected = { {3, 1, 5.000000e-02},
		{22, 7, 4.000000e-04},
		{355, 113, 8.000000e-08},
		{104348, 33215, 1.000000e-10}
	};
	for (size_t i = 0; i < expected.size(); i++) {
		ASSERT_EQ(result[i].get_numerator(), expected[i].get_numerator());
		ASSERT_EQ(result[i].get_denominator(), expected[i].get_denominator());
		ASSERT_EQ(result[i].get_epsilon(), expected[i].get_epsilon());
	}
}

TEST(TestCase, AnotherNumber) {
	double error = 1.0e-10;
	Approximations obj(8.9815962335);
	obj(error);
	std::vector<Fraction> result = obj.get_fractions();
	std::vector<Fraction> expected = { {9, 1, 2.000000e-03},
		{485, 54, 1.000000e-05},
		{1464, 163, 1.000000e-07},
		{47827, 5325, 1.000000e-09},
		{144945, 16138, 1.000000e-10}
	};
	for (size_t i = 0; i < expected.size(); i++) {
		ASSERT_EQ(result[i].get_numerator(), expected[i].get_numerator());
		ASSERT_EQ(result[i].get_denominator(), expected[i].get_denominator());
		ASSERT_EQ(result[i].get_epsilon(), expected[i].get_epsilon());
	}
}

TEST(TestCase, Integer) {
	double error = 1.0e-10;
	Approximations obj(8.0);
	obj(error);
	std::vector<Fraction> result = obj.get_fractions();
	std::vector<Fraction> expected = { {8, 1, 0.000000e+00}	};
	for (size_t i = 0; i < expected.size(); i++) {
		ASSERT_EQ(result[i].get_numerator(), expected[i].get_numerator());
		ASSERT_EQ(result[i].get_denominator(), expected[i].get_denominator());
		ASSERT_EQ(result[i].get_epsilon(), expected[i].get_epsilon());
	}
}
