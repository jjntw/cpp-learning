#include "Polynomial.hpp"
#include <iostream>

int main() {
	Polynomial p({1.0, 2.0, 3.0}); // 3x^2 + 2x + 1
	Polynomial q({4.0, 1.0});	   // x + 4

	std::cout << "p = " << p << "\n";
	std::cout << "q = " << q << "\n\n";

	std::cout << "evaluate p at x=2:  " << p.evaluate(2.0)
			  << " (expected 17)\n";

	std::cout << "p + q = " << (p + q) << " (expected 3x^2 + 3x + 5)\n";
	std::cout << "p - q = " << (p - q) << " (expected 3x^2 + x - 3)\n";
	std::cout << "p * q = " << (p * q) << " (expected 3x^3 + 14x^2 + 9x + 4)\n";

	std::cout << "p * 2.0 = " << (p * 2.0) << " (expected 6x^2 + 4x + 2)\n";
	std::cout << "2.0 * p = " << (2.0 * p) << " (expected 6x^2 + 4x + 2)\n";

	std::cout << "-p = " << (-p) << " (expected -3x^2 - 2x + -1)\n";

	std::cout << "p' = " << p.derivative() << " (expected 6x + 2)\n";
	std::cout << "q' = " << q.derivative() << " (expected 1)\n";

	std::cout << "p * zero = " << (p * Polynomial::zero()) << " (expected 0)\n";

	std::cout << "p == p: " << (p == p) << " (expected 1)\n";
	std::cout << "p == q: " << (p == q) << " (expected 0)\n";

	return 0;
}
