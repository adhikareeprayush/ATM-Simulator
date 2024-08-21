#include "../include/utilities.h"
#include<iostream>

int main() {
    int option;
    do {
        clearScreen();
        std::cout << "1. Register\n2. Login\n0. Exit" << std::endl;
        option = getValidOption();

        switch (option) {
            case 1:
                userRegister();
                break;
            case 2:
                login();
                break;
            case 0:
                std::cout << "Thank you for using the ATM Simulator!" << std::endl;
                break;
            default:
                std::cout << "Invalid option. Please try again." << std::endl;
                break;
        }
    } while (option != 0);
    return 0;
}
