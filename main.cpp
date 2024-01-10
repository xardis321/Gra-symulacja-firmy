#include <iostream>
#include <vector>
#include <memory>
#include <variant>
#include <random>
#include <algorithm>
#include <unistd.h>
#include <cstdlib>
#include "RandomNameGenerator.hpp"
#include "firma.hpp"

int main() {
    Firma firma;

    firma.zatrudnianie(std::make_shared<Inz>("inzyniera1"));
    firma.zatrudnianie(std::make_shared<Mag>("mag1"));
    firma.zatrudnianie(std::make_shared<Mkt>("mkt1"));
    firma.zatrudnianie(std::make_shared<Robotnik>("robotnik1"));

    firma.balance = 50000;
    firma.companyValue = 0;
    double M = 4;

    while (firma.balance >= 0) {
        std::cout << "\n";
        sleep(0.5);
        std::cout << "Wybierz opcję: "<<std::endl; 
        std::cout << "Opcje:\n";
        sleep(0.5);
        std::cout << "1. Zatrudnij inz -4000 miesięcznie\n";
        std::cout << "2. Zatrudnij mag -3000 miesięcznie\n";
        std::cout << "3. Zatrudnij mkt -3500 miesięcznie\n";
        std::cout << "4. Zatrudnij pracownika -2500 miesięcznie\n";
        std::cout << "5. Wydrukuj listę pracowników\n";
        std::cout << "6. Pożyczka\n";
        std::cout << "7. Koniec tury\n";
        std::cout << "8. Wyjście\n";
        sleep(1);

        std::cout << std::endl;
        int option;
        std::cin >> option;

        sleep(1);
        std::cout << "\n" << std::endl;

        switch (option) {
            case 1:
                firma.zatrudnianie(std::make_shared<Inz>());
                break;
            case 2:
                firma.zatrudnianie(std::make_shared<Mag>());
                break;
            case 3:
                firma.zatrudnianie(std::make_shared<Mkt>());
                break;
            case 4:
                firma.zatrudnianie(std::make_shared<Robotnik>());
                break;
            case 5:
                firma.listowanie();
                break;
            case 6: {
                double amount;
                int repaymentPeriod;
                std::cout << "Wpisz kwotę pożyczki (nie może przekraczać 4-krotnej wartości twojej firmy): ";
                std::cin >> amount;
                if (amount <= firma.companyValue * M) {
                    std::cout << "Czas pożyczki (w miesiącach): ";
                    std::cin >> repaymentPeriod;
                    firma.pozyczka(amount, repaymentPeriod);
                } else {
                    std::cout << "Błąd w pobraniu pożyczki >" << M << " krotnie przekracza wartość firmy." << std::endl;
                }
                break;
            }
            case 7:
                firma.koniectury();
                break;
            case 8:
                std::cout << "Wyjście z gry.\n";
                return 0;
            default:
                std::cout << "Błędna opcja, wybierz inną.\n";
        }
    }
}
