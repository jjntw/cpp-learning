#include <cmath>
#include <iostream>

class Vector3D {
	double x;
	double y;
	double z;

  public:
	// Member initializer list constructors
	Vector3D() : x{0.0}, y{0.0}, z{0.0} {}
	Vector3D(double x, double y, double z) : x{x}, y{y}, z{z} {}

	// Member getters
	double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }

	// Overload ops for vector sums, differences, and scalar multiplication
	Vector3D operator+(const Vector3D &V) const {
		return Vector3D(x + V.x, y + V.y, z + V.z);
	}

	Vector3D operator-(const Vector3D &V) const {
		return Vector3D(x - V.x, y - V.y, z - V.z);
	}

	Vector3D operator*(double c) const { return Vector3D(x * c, y * c, z * c); }

	// Define unique vector operations dot product, cross product, magnitude.
	double dot(const Vector3D &V) const { return x * V.x + y * V.y + z * V.z; }

	Vector3D cross(const Vector3D &V) const {
		return Vector3D(y * V.z - z * V.y, z * V.x - x * V.z,
						x * V.y - y * V.x);
	}

	double norm() const { return sqrt(x * x + y * y + z * z); }

	// Normalize vector
	Vector3D normalize() const {
		double inv_norm = 1 / Vector3D(x, y, z).norm();
		return Vector3D(x, y, z) * inv_norm;
	}

	friend std::ostream &operator<<(std::ostream &os, const Vector3D &V) {
		os << "(" << V.x << ", " << V.y << ", " << V.z << ")";
		return os;
	}

	// Adding function to make scalar multiplication commute
	friend Vector3D operator*(const double c, const Vector3D &V) {
		return V * c;
	}
};

//int main() { return 0; }
