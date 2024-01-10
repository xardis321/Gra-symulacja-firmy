#ifndef Kredyt_H
#define Kredyt_H

#include <iostream>
#include <vector>
#include <memory>
#include <variant>
#include <random>
#include <algorithm>
#include <unistd.h>
#include <cstdlib>
#include "RandomNameGenerator.hpp"

class Kredyt {
public:
    double borrowed;
    int installments;
    double interest;

    int installmentsTotal; // Not needed

    double getMonthlyPayment() const {
        return (borrowed + interest) / installments;
    }

    double getAmountOwed() const {
        return borrowed + interest;
    }

    int getRemainingPayments() {
        return installments;
    }

    // Constructors
    Kredyt() : borrowed(0.0), installments(1), interest(0.0) {}

    Kredyt(double aborrowed, int ainstallments)
        : borrowed(aborrowed), installments(ainstallments), interest(0.05 + (ainstallments / 8.0) / 100), installmentsTotal(ainstallments) {}

    // Copy constructor
    Kredyt(const Kredyt &other)
        : borrowed(other.borrowed), installments(other.installments), interest(other.interest) {}

    // Move constructor
    Kredyt(Kredyt &&other) noexcept
        : borrowed(std::move(other.borrowed)), installments(std::move(other.installments)),
          interest(std::move(other.interest)) {}

    Kredyt& operator=(const Kredyt &other) {
        if (this != &other) {
            borrowed = other.borrowed;
            installments = other.installments;
            interest = other.interest;
        }
        return *this;
    }

    // Destructor
    ~Kredyt() {}
};

#endif
