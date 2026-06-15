#pragma once

#include <iostream>

class Complex {
  public:
	Complex(double re, double im);
	Complex();

	struct polar_tag {};
	Complex(double r, double theta, polar_tag);

	static Complex from_polar(double r, double theta);

	double real() const { return re; }
	double imag() const { return im; }

	Complex operator+(const Complex &z) const;
	Complex operator-(const Complex &z) const;
	Complex operator*(double c) const;
	Complex operator*(const Complex &z) const;
	Complex operator/(double c) const;
	Complex operator/(const Complex &z) const;
	bool operator==(const Complex &z) const;

	Complex conjugate() const;
	double modulus() const;
	double arg() const;
	Complex exp() const;
	Complex pow(int n) const;

	friend Complex operator*(double c, const Complex &z);
	friend std::ostream &operator<<(std::ostream &os, const Complex &z);

  private:
	double re;
	double im;
};
