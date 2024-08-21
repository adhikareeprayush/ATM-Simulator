#include "../include/utilities.h"
#include<iostream>

int main() {
    int option;
    do {
        clearScreen();
        std::cout << GREEN << "1. Register\n2. Login\n3. Quit" << std::endl <<RESET;
        option = getValidOption();

        switch (option) {
            case 1:
                userRegister();
                break;
            case 2:
                login();
                break;
            case 3:
                std::cout << GREEN<< "Thank you for using the ATM Simulator!" << std::endl <<RESET;
                break;
            default:
                std::cout << RED << "Invalid option. Please try again." << std::endl;
                break;
        }
    } while (option != 3);
    return 0;
}
