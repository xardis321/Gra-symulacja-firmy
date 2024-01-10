#ifndef Firma_H
#define Firma_H

#include "inz.hpp"
#include "mag.hpp"
#include "mkt.hpp"
#include "robotnik.hpp"
#include "kredyt.hpp"

class Firma {
public:
    using EmployeeType = std::variant<std::shared_ptr<Inz>, std::shared_ptr<Mag>,
                                      std::shared_ptr<Mkt>, std::shared_ptr<Robotnik>>;

    void zatrudnianie(EmployeeType employee) {
        employees.push_back(std::move(employee));
    }

    template <typename EmployeeType>
    int countEmployeesOfType() const {
        int count = 0;
        for (const auto &employee : employees) {
            if (std::holds_alternative<std::shared_ptr<EmployeeType>>(employee)) {
                count++;
            }
        }
        return count;
    }

    void listowanie() const {
        for (const auto &employee : employees) {
            std::visit([](const auto &emp) {
                emp->printDetails();
            }, employee);
        }
    }

    double calykoszt() const {
        double totalCost = 0.0;
        for (const auto &employee : employees) {
            std::visit([&totalCost](const auto &emp) {
                totalCost += emp->getSalary();
            }, employee);
        }
        return totalCost;
    }

    void pozyczka(double amount, int repaymentPeriod) {
        if (repaymentPeriod <= 48) {
            credit.emplace<Kredyt>(amount, repaymentPeriod);
            balance += amount;
        } else {
            std::cout << "Nie mozna wziac pozyczki." << std::endl;
        }
    }

    void koniectury() {
        std::cout << "\n" << std::endl;
        std::cout << "Kolejny miesiac" << std::endl;

        int CR = 20;
        int CI = 160;
        int CMag = 40;
        int CMar = 80;

        pojemnoscMagazynu = countEmployeesOfType<Mag>() * CMag;
        popyt = CMar * countEmployeesOfType<Mkt>();

        double teoretycznaProdukcja = CR * countEmployeesOfType<Robotnik>();
        double faktycznaProdukcja = std::min(teoretycznaProdukcja, pojemnoscMagazynu);
        sprzedaz = std::min(popyt, faktycznaProdukcja);

        cenaProduktu = CI * countEmployeesOfType<Inz>();
        przychodFirmy = sprzedaz * cenaProduktu;

        double totalOwed = 0.;

        for (auto it = loans.begin(); it != loans.end();) {
            balance -= it->getMonthlyPayment();
            it->installments--;

            totalOwed += it->getAmountOwed();
            std::cout << "Ilosc kredytu: -" << it->getMonthlyPayment() << std::endl;

            if (it->installments <= 0) {
                it = loans.erase(it);
            } else {
                ++it;
            }
        }

        salaries = this->calykoszt();

        balance = balance + przychodFirmy - salaries;
        historicalIncome.emplace_back(przychodFirmy);

        int N = 12;
        size_t len = historicalIncome.size();
        companyValue = 0.;
        if (len > N) {
            for (int i = 0; i < N; i++) {
                companyValue += historicalIncome[len - i];
            }
        } else {
            for (int i = 0; i < len; i++) {
                companyValue += historicalIncome[len - i];
            }
        }

        std::cout << "Przychod firmy: +" << przychodFirmy << std::endl;
        std::cout << "Wyplaty: -" << salaries << std::endl;

        if (std::holds_alternative<Kredyt>(credit)) {
            auto &loan = std::get<Kredyt>(credit);
            std::cout << "Zaplaty raty: -" << loan.getMonthlyPayment() << std::endl;
        }

        sleep(1.5);

        if (companyValue - totalOwed > 100000.) {
            std::cout << "BRAWO! WYGRANA" << std::endl;
            sleep(10);
            exit(1);
        }

        std::cout << "Twoj balans: " << balance << std::endl;
        std::cout << "Wartosc rynkowa firmy: " << companyValue << std::endl;

        turnCounter++;
    }

    double balance;
    double companyValue;
    int turnCounter;
    double przychodFirmy;
    double salaries;

private:
    std::vector<EmployeeType> employees;
    double maxDebtMultiplier;
    std::vector<Kredyt> loans;
    std::vector<double> historicalIncome;
    std::variant<std::monostate, Kredyt> credit;
    double pojemnoscMagazynu;
    double cenaProduktu;
    double popyt;
    double sprzedaz;
};

#endif
