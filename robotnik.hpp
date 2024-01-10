#ifndef ROBOTNIK_H
#define ROBOTNIK_H

#include "pracownik.hpp"

class Robotnik : public Pracownik {
private:
    std::string department;

public:
    Robotnik(std::string name) : Pracownik(std::move(name), 2500.0), department("MEiL") {}

    Robotnik() : Pracownik(get_random_name(), 2500.0) {
        std::cout << "Wpisz oddzial ";
        std::cin >> department;
    }

    Robotnik(const Robotnik &other) : Pracownik(other.name, other.salary), department(other.department) {}

    void printDetails() const override {
        std::cout << "Robotnik: " << name << ", wyplata: " << salary << std::endl;
    }
};

#endif
