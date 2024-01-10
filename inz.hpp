#ifndef Inz_H
#define Inz_H

#include "RandomNameGenerator.hpp"
#include "pracownik.hpp"

class Inz : public Pracownik {
private:
    std::string department;

public:
    Inz(std::string name) : Pracownik(std::move(name), 4000.0), department("MEiL") {}

    Inz() : Pracownik(get_random_name(), 4000.0) {
        std::cout << "Wpisz wydzial: ";
        std::cin >> department;
    }

    Inz(const Inz &other) : Pracownik(other.name, other.salary), department(other.department) {}

    void printDetails() const override {
        std::cout << "Inz: " << name << ", wydzial: " << department << ", wyplata: " << salary << std::endl;
    }
};

#endif
