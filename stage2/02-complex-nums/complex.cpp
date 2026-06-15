#include "complex.hpp"

#include <cmath>

Complex::Complex(double re, double im) : re{re}, im{im} {}

Complex::Complex() : re{0.0}, im{0.0} {}

Complex::Complex(double r, double theta, polar_tag)
	: re{r * std::cos(theta)}, im{r * std::sin(theta)} {}

Complex Complex::from_polar(double r, double theta) {
	return Complex(r * std::cos(theta), r * std::sin(theta));
}

Complex Complex::operator+(const Complex &z) const {
	return Complex(re + z.re, im + z.im);
}

Complex Complex::operator-(const Complex &z) const {
	return Complex(re - z.re, im - z.im);
}

Complex Complex::operator*(double c) const { return Complex(re * c, im * c); }

Complex Complex::operator*(const Complex &z) const {
	return Complex(re * z.re - im * z.im, re * z.im + im * z.re);
}

Complex Complex::operator/(double c) const { return Complex(re / c, im / c); }

Complex Complex::operator/(const Complex &z) const {
	Complex conj = z.conjugate();
	double denom = z.re * z.re + z.im * z.im;
	return (*this * conj) / denom;
}

bool Complex::operator==(const Complex &z) const {
	double eps = 1e-9;
	return std::abs(re - z.re) < eps && std::abs(im - z.im) < eps;
}

Complex Complex::conjugate() const { return Complex(re, -im); }

double Complex::modulus() const { return std::sqrt(re * re + im * im); }

double Complex::arg() const { return std::atan2(im, re); }

Complex Complex::exp() const {
	return Complex(std::cos(im), std::sin(im)) * std::exp(re);
}

Complex Complex::pow(int n) const {
	double r = modulus();
	double theta = arg();
	return Complex(std::cos(n * theta), std::sin(n * theta)) * std::pow(r, n);
}

Complex operator*(double c, const Complex &z) { return z * c; }

std::ostream &operator<<(std::ostream &os, const Complex &z) {
	os << z.re << " + " << z.im << "i";
	return os;
}
