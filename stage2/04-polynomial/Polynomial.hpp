#pragma once

#include <ostream>
#include <vector>

class Polynomial {
  public:
	explicit Polynomial(std::vector<double> coeffs);

	static Polynomial zero();
	static Polynomial one();

	int degree() const;
	double coefficient(int degree) const;
	const std::vector<double> &coefficients() const;

	double evaluate(double x) const;

	Polynomial operator+(const Polynomial &p) const;
	Polynomial operator-(const Polynomial &p) const;
	Polynomial operator-() const;
	Polynomial operator*(const Polynomial &p) const;
	Polynomial operator*(double c) const;

	Polynomial derivative() const;

	bool operator==(const Polynomial &p) const;

	friend Polynomial operator*(double c, const Polynomial &p);

	friend std::ostream &operator<<(std::ostream &os, const Polynomial &p);

  private:
	std::vector<double> m_coeffs;
	void strip_trailing_zeros();
};
