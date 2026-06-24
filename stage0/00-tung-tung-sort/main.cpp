#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <limits>
#include <bits/stdc++.h>
#include <format>
#include <cmath>
#include "../../stage2/01-vector3d/vector.cpp"


struct Sahur {
    bool operator()(const Vector3D& v1, const Vector3D& v2) const {
        return v1.norm() > v2.norm();
    }
};

constexpr std::string stringify_vector_vector(std::vector<Vector3D> vec) {
    return "[" + std::accumulate(vec.begin(), vec.end(),
                      std::string(), [](std::string s, Vector3D& tung3) {
                      return s + (s.empty() ? "" : ", ")
                              + "("
                              + std::format("{:.2f}, {:.2f}, {:.2f}",
                                      std::floor(tung3.getX() * 100.0) / 100.0,
                                      std::floor(tung3.getY() * 100.0) / 100.0,
                                      std::floor(tung3.getZ() * 100.0) / 100.0
                              )
                              + ")";
    }) + "]";
}

void tung_tung_sort(const size_t size) {
    using Tung = std::priority_queue<Vector3D, std::vector<Vector3D>, Sahur>;
    std::vector<Vector3D> tung; tung.reserve(size);

    Tung tungtung(Sahur{}, std::move(tung));
    std::vector<Vector3D> sortSpace(size);

    for (size_t i = 0; i < size; ++i) {
        std::string rawLine;
        double t1 = 0.0, t2 = 0.0, t3 = 0.0;

        std::cout
        << "Enter coordinates for the next 3D vector (format: <x> <y> <z>)."
        << std::endl;

        for (;;) {
            std::cin >> t1 >> t2 >> t3;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter valid coordinates (format: <x> <y> <z>)." << std::endl;
                continue;
            }

            Vector3D tung3{t1, t2, t3};
            tungtung.push(tung3);
            sortSpace[i] = tung3;
            break;
        }
    }

    std::cout << "\nYour vector (2.d.p):" << std::endl;
    std::cout << stringify_vector_vector(sortSpace) << std::endl;

    std::cout << "\nSorting Sahur...\n" << std::endl;

    Sahur tun;
    Vector3D gTun, gSahur;
    for (size_t i = 0; i < size; ++i) {
        gSahur = tungtung.top();
        tungtung.pop();

        for (size_t j = i; j < size; ++j) {
            gTun = sortSpace[j];
            if (tun(gTun, gSahur)) {
                continue;
            }

            std::swap(sortSpace[i], sortSpace[j]);
            break;
        }

        std::cout << "Tung..." << std::endl;
        std::cout << stringify_vector_vector(sortSpace) << '\n' << std::endl;
    }
}

int main() {
    std::string rawSize;
    size_t inputSize = 0;

    std::cout << "Enter the size for your vector." << std::endl;
    for (;;) {
        std::cin >> inputSize;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter a valid size." << std::endl;
            continue;
        }
        break;
    }

    tung_tung_sort(inputSize);

    std::cout << "Shaur" << std::endl;
    return 0;
}