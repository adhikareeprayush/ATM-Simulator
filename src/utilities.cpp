#include "../include/utilities.h"
#include "../include/ATM.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include<iomanip>

using namespace std;

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int getValidOption() {
    int option;
    while(true) {
        cout <<GREEN << "Enter an option: ";
        cin >> option;
        cout<<RESET;

        if(cin.fail()) {
            cout <<RED<< "Invalid input. Please enter a valid integer." << endl <<RESET;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return option;
        }
    }
}

void enterToContinue() {
    cout << CYAN << "Press Enter to continue..." <<RESET;
    cin.ignore();
    cin.get();
}

bool isPinValid(const string& pinNumber, const string& confirmPIN) {
    if(pinNumber.length() != 4) {
        cout << "The PIN should contain 4 Digits!" << endl;
        return false;
    } else if(pinNumber != confirmPIN) {
        cout <<RED<< "PIN didn't match! Please try again." << endl <<RESET;
        return false;
    }
    return true;
}

string generateAccountNumber() {
    string accNum;
    for (int i = 0; i < 12; i++) {
        accNum += to_string(rand() % 10);
    }
    return accNum;
}

void login() {
    ATM atm(USER_CRED);
    string accountNumber, pin;
    cout << CYAN << "Enter Account Number: ";
    cin >> accountNumber;
    cout << "Enter PIN: ";
    cin >> pin;
    cout<<RESET;
    if(atm.login(accountNumber, pin)) {
        atm.performTransaction(accountNumber);
    }
}

void userRegister() {
    ATM atm(USER_CRED);
    string name, accountNumber, pinNumber, confirmPin;
    double balance;
    cout << GREEN << "Enter the name of the user: ";
    getline(cin, name);
    
    do {
        accountNumber = generateAccountNumber();
    } while(atm.userExists(accountNumber));

    do {
        cout << RED<<"Enter the PIN: ";
        cin >> pinNumber;
        cout << "Re-enter the PIN: ";
        cin >> confirmPin;
    } while(!isPinValid(pinNumber, confirmPin));

    cout << CYAN <<"Enter the balance: ";
    cin >> balance;

    User user(name, accountNumber, pinNumber, balance);
    atm.addUser(user);
    cout<<RESET;
    clearScreen();
    // Display the new user's information

    string balanceStr = "$" + to_string(balance);

     // Ensure the widths match the box length
    int boxWidth = 61;
    int nameWidth = boxWidth - 16 - 18; // Adjust the padding accordingly
    int accountWidth = 20;
    int balanceStrLength = balanceStr.length();
    int balancePadding = boxWidth - 16 - balanceStrLength - 3; // -3 for the spaces and | at the end

    // Display user information in a boxed layout with colors
    cout << CYAN << "+-----------------------------------------------------------+" << RESET << endl;
    cout << CYAN << "| " << RESET << left << setw(nameWidth) << ("Name: " + name)
        << CYAN << "| " << RESET << setw(accountWidth) << ("Account Number: " + accountNumber) << CYAN << " |\n";
    cout << CYAN << "+-----------------------------------------------------------+" << RESET << endl;
    cout << CYAN << "| " << RESET << "Current Balance:" 
        << setw(balancePadding-1) << " " << YELLOW << balanceStr << RESET << CYAN << " |\n";
    cout << CYAN << "+-----------------------------------------------------------+" << RESET << endl;

    cout<<GREEN<<"\n\nSuccessfully Created Account! Please note the credentials."<<endl;
    enterToContinue();
}
