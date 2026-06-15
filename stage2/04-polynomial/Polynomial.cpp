#include "Polynomial.hpp"
#include "../02-complex-nums/complex.hpp"
#include <math.h>
#include <string>

Polynomial::Polynomial(std::vector<double> coeffs)
	: m_coeffs(std::move(coeffs)) {
	strip_trailing_zeros();
}

Polynomial Polynomial::zero() { return Polynomial({0.0}); }

Polynomial Polynomial::one() { return Polynomial({1.0}); }

int Polynomial::degree() const { return static_cast<int>(m_coeffs.size()) - 1; }

double Polynomial::coefficient(int d) const {
	if (d < 0 || d > degree())
		return 0.0;
	return m_coeffs[static_cast<size_t>(d)];
}

const std::vector<double> &Polynomial::coefficients() const { return m_coeffs; }

// Horner's Method
double Polynomial::evaluate(double x) const {
	if (m_coeffs.empty())
		return 0.0;

	int n = degree();
	double result = m_coeffs.back();

	for (int i = n - 1; i >= 0; --i) {
		result = result * x + m_coeffs[static_cast<size_t>(i)];
	}
	return result;
}

Polynomial Polynomial::operator+(const Polynomial &p) const {
	std::vector<double> coeffs;
	size_t m = m_coeffs.size();
	size_t n = p.m_coeffs.size();

	if (m >= n) {
		coeffs = m_coeffs;
		for (size_t i = 0; i < n; ++i)
			coeffs[i] += p.m_coeffs[i];
	} else {
		coeffs = p.m_coeffs;
		for (size_t i = 0; i < m; ++i)
			coeffs[i] += m_coeffs[i];
	}
	return Polynomial(coeffs);
}

Polynomial Polynomial::operator-() const {
	std::vector<double> coeffs = m_coeffs;

	for (auto &coeff : coeffs)
		coeff = -coeff;
	return Polynomial(coeffs);
}

Polynomial Polynomial::operator-(const Polynomial &p) const {
	return *this + (-p);
}

std::vector<Complex> fft(std::vector<Complex> a, bool inverse) {
	size_t n = a.size(); // must be power of 2
	if (n == 1)
		return a;

	Complex omega = Complex(0.0, inverse ? -2 * M_PI / static_cast<double>(n)
										 : 2 * M_PI / static_cast<double>(n))
						.exp();

	std::vector<Complex> P_e;
	std::vector<Complex> P_o;
	std::vector<Complex> y;

	for (size_t i = 0; i < n; ++i) {
		y.push_back(Complex());
		if (i % 2 == 0)
			P_e.push_back(a[i]);
		else
			P_o.push_back(a[i]);
	}

	std::vector<Complex> y_e = fft(P_e, inverse);
	std::vector<Complex> y_o = fft(P_o, inverse);

	Complex omega_i(1.0, 0.0);

	for (size_t i = 0; i < n / 2; ++i) {
		y[i] = y_e[i] + omega_i * y_o[i];
		y[i + n / 2] = y_e[i] - omega_i * y_o[i];
		omega_i = omega_i * omega;
	}
	return y;
}

// O(n log n) with fft
Polynomial Polynomial::operator*(const Polynomial &p) const {
	size_t result_size = m_coeffs.size() + p.m_coeffs.size() - 1;

	size_t padded_size = 1;
	while (padded_size < result_size)
		padded_size <<= 1;

	std::vector<Complex> a;
	std::vector<Complex> b;

	for (size_t i = 0; i < padded_size; ++i) {
		a.push_back(i < m_coeffs.size() ? Complex(m_coeffs[i], 0.0)
										: Complex());
		b.push_back(i < p.m_coeffs.size() ? Complex(p.m_coeffs[i], 0.0)
										  : Complex());
	}

	a = fft(a, false);
	b = fft(b, false);

	std::vector<Complex> c(padded_size);

	for (size_t i = 0; i < padded_size; ++i)
		c[i] = a[i] * b[i];

	c = fft(c, true);
	std::vector<double> result;

	for (size_t i = 0; i < result_size; ++i)
		result.push_back((c[i] / static_cast<double>(padded_size)).real());

	return Polynomial(result);
}

Polynomial Polynomial::operator*(double c) const {
	std::vector<double> coeffs = m_coeffs;

	for (auto &coeff : coeffs)
		coeff = c * coeff;
	return Polynomial(coeffs);
}

Polynomial Polynomial::derivative() const {
	std::vector<double> coeffs;

	for (size_t i = 1; i < m_coeffs.size(); ++i)
		coeffs.push_back(static_cast<double>(i) * m_coeffs[i]);

	return Polynomial(coeffs);
}

bool Polynomial::operator==(const Polynomial &p) const {
	if (m_coeffs.size() != p.m_coeffs.size())
		return false;

	for (size_t i = 0; i < m_coeffs.size(); ++i)
		if (p.m_coeffs[i] != m_coeffs[i])
			return false;

	return true;
}

Polynomial operator*(double c, const Polynomial &p) { return p * c; }

std::ostream &operator<<(std::ostream &os, const Polynomial &p) {
	int n = p.degree();

	for (int i = n; i > 0; --i) {
		double coeff = p.m_coeffs[static_cast<size_t>(i)];
		std::string sign = coeff > 0 ? " + " : " - ";

		if (i != n)
			os << sign;

		if (i == n && p.m_coeffs[static_cast<size_t>(n)] < 0.0)
			os << "-";

		os << (std::abs(coeff) != 1.0
				   ? std::to_string(static_cast<int>(std::abs(coeff)))
				   : "");

		std::string exp = (i != 1 ? "x^" + std::to_string(i) : "x");

		os << exp;
	}

	double c = p.m_coeffs[0];

	if (n > 0)
		os << (c > 0 ? " + " : " - ")
		   << std::to_string(static_cast<int>(abs(c)));
	else
		os << c;

	return os;
}

void Polynomial::strip_trailing_zeros() {
	while (m_coeffs.size() > 1 && m_coeffs.back() == 0.0)
		m_coeffs.pop_back();
}
