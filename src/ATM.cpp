#include"../include/ATM.h"
#include"../include/utilities.h"
#include<fstream>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<limits>


ATM::ATM(const std::string& filename)
{
    loadUsersFromFile(filename);
}

void ATM::loadUsersFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    // Skip the first header line
    getline(file, line);

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string name, accountNumber, pin, balanceStr;
        double balance;

        getline(ss, name, ',');
        getline(ss, accountNumber, ',');
        getline(ss, pin, ',');
        getline(ss, balanceStr, ',');

        // Trim any extra whitespace (optional)
        name.erase(0, name.find_first_not_of(" \t"));
        name.erase(name.find_last_not_of(" \t") + 1);
        accountNumber.erase(0, accountNumber.find_first_not_of(" \t"));
        accountNumber.erase(accountNumber.find_last_not_of(" \t") + 1);
        pin.erase(0, pin.find_first_not_of(" \t"));
        pin.erase(pin.find_last_not_of(" \t") + 1);
        balanceStr.erase(0, balanceStr.find_first_not_of(" \t"));
        balanceStr.erase(balanceStr.find_last_not_of(" \t") + 1);

        balance = stod(balanceStr);
        users.push_back(User(name, accountNumber, pin, balance));
    }

    file.close();
}       

User* ATM::findUser(const std::string& accountNumber)
{
    for(auto& user: users)
    {
        if(user.getAccountNumber() == accountNumber)
            {
                return &user;
            }
    }
    return nullptr;
}

bool ATM::login(const std::string& accountNumber, const std::string& pinNumber)
{
    currentUser = findUser(accountNumber);
    if(currentUser && currentUser->checkPin(pinNumber)){
        std::cout<<"LOGIN SUCCESSFUL. Welcome, " <<currentUser->getName() << "!" <<std::endl;
        return true;
    }
    else{
        std::cout<<"LOGIN FAILED! Incorrect Account Number or PIN" <<std::endl;
        enterToContinue();
        return false;
    }
}

void ATM::updateFile()
{
    std::ofstream file(USER_CRED);
    if(!file)
    {
        std::cerr <<"ERROR OPENING FILE: " <<"user_cred.txt" <<std::endl;
        return;
    }
    file << "Name,Account Number,PIN,Balance\n";
    for(auto& user: users)
    {
        file << user.getName() << "," << user.getAccountNumber() << "," << user.getPin() << "," << user.getBalance() << "\n";
    }
    file.close();
}

void ATM::logout()
{
    currentUser = nullptr;
    std::cout << "Logged Out Successfully!"<<std::endl;
}

void ATM::performTransaction(const std::string& accountNumber)
{
    currentUser = findUser(accountNumber);
     if (!currentUser) 
     {
        std::cout << RED << "No User Logged in!" << RESET << std::endl;
        return;
    }

    int choice;
    do {
        clearScreen();

        // Calculate the lengths for proper alignment
        std::string name = currentUser->getName();
        std::string accountNumber = currentUser->getAccountNumber();
        double balance = currentUser->getBalance();
        std::string balanceStr = "$" + std::to_string(balance);

        // Ensure the widths match the box length
        int boxWidth = 61;
        int nameWidth = boxWidth - 16 - 18; // Adjust the padding accordingly
        int accountWidth = 20;
        int balanceStrLength = balanceStr.length();
        int balancePadding = boxWidth - 16 - balanceStrLength - 3; // -3 for the spaces and | at the end

        // Display user information in a boxed layout with colors
        std::cout << CYAN << "+-----------------------------------------------------------+" << RESET << std::endl;
        std::cout << CYAN << "| " << RESET << std::left << std::setw(nameWidth) << ("Name: " + name)
            << CYAN << "| " << RESET << std::setw(accountWidth) << ("Account Number: " + accountNumber) << CYAN << " |\n";
        std::cout << CYAN << "+-----------------------------------------------------------+" << RESET << std::endl;
        std::cout << CYAN << "| " << RESET << "Current Balance:" 
            << std::setw(balancePadding-1) << " " << YELLOW << balanceStr << RESET << CYAN << " |\n";
        std::cout << CYAN << "+-----------------------------------------------------------+" << RESET << std::endl;

        // Display the ATM menu
        std::cout << GREEN << "\nATM MENU:\n" << RESET;
        std::cout << "1. Deposit Money\n";
        std::cout << "2. Withdraw Money\n";
        std::cout << "3. Change PIN\n";
        std::cout << "4. Logout\n";
        choice = getValidOption();

        // Handle the user's choice
        switch (choice) {
            case 1: {
                double amount;
                std::cout << "\nEnter the amount to deposit: ";
                std::cin >> amount;
                currentUser->deposit(amount);
                enterToContinue();
                updateFile();
                break;
            }
            case 2: {
                double amount;
                std::cout << "\nEnter the amount to withdraw: ";
                std::cin >> amount;
                currentUser->withdraw(amount);
                updateFile();
                enterToContinue();
                break;
            }
            case 3: {
                std::string newPin;
                std::cout << "\nEnter new PIN: ";
                std::cin >> newPin;
                currentUser->changePin(newPin);
                enterToContinue();
                updateFile();
                break;
            }
            case 4:
                logout();
                break;
            default:
                std::cout << RED << "\nInvalid Choice. Please Try Again." << RESET << std::endl;
                enterToContinue();
        }

    } while (choice != 4);
        
}


void ATM::getUsers() {
    for (auto& user : users) {
        std::cout << user.getName() << std::endl;
    }
}

bool ATM::userExists(const std::string& accountNumber) {
    for (auto& user : users) {
        if (user.getAccountNumber() == accountNumber)
            return true;
    }
    return false;
}

void ATM::addUser(const User& user) {
    users.push_back(user);
    updateFile();
    std::cout << "User added Successfully!" << std::endl;
}
