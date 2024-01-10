#ifndef Mag_H
#define Mag_H

#include "pracownik.hpp"

class Mag : public Pracownik {
private:
    std::string department;

public:
    Mag(std::string name) : Pracownik(std::move(name), 3000.0), department("MEiL") {}

    Mag() : Pracownik(get_random_name(), 3000.0) {
        std::cout << "Wpisz oddzial: ";
        std::cin >> department;
    }

    Mag(const Mag &other) : Pracownik(other.name, other.salary), department(other.department) {}

    void printDetails() const override {
        std::cout << "Mag " << name << ", wyplata: " << salary << std::endl;
    }
};

#endif
