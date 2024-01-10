#ifndef PRACOWNIK_H
#define PRACOWNIK_H

#include <iostream>
#include <cstdlib>

class Pracownik {
protected:
    std::string name;
    double salary;

public:
    Pracownik(std::string name, double salary) : name(std::move(name)), salary(salary) {}
    virtual ~Pracownik() = default;

    virtual void printDetails() const = 0;

    virtual double getSalary() const { return salary; }
};

#endif
