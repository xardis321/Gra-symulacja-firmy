#include <iostream>
#include <vector>
#include <memory>
#include <variant>
#include <random>
#include <algorithm>
#include <unistd.h>
#include <cstdlib>
#include "RandomNameGenerator.hpp"

class Mkt : public Pracownik {
private:
    std::string department;

public:
    Mkt(std::string name) : Pracownik(std::move(name), 3500.0), department("MEiL") {}

    // Default constructor
    Mkt() : Pracownik(get_random_name(), 3500.0) {
        std::cout << "Podaj oddział ";
        std::cin >> department;
    }

    // Copy constructor
    Mkt(const Mkt &other) : Pracownik(other.name, other.salary), department(other.department) {}

    void printDetails() const override {
        std::cout << "MKT " << name << ", wypłata: " << salary << std::endl;
    }
};
