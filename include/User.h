#ifndef USER_H
#define USER_H

#include<string>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"

class User{
    private:
        std::string name;
        std::string accountNumber;
        std::string pin;
        double balance;
    public:
        User(const std::string& name,const std::string& accountNumber,const std::string& pin,const double& balance);

        bool checkPin(const std::string& pinNumber);
        void deposit(double amount);
        bool withdraw(double amount);
        double getBalance();
        bool changePin(const std::string& pinNumber);
        std::string getName();
        std::string getAccountNumber();
        std::string getPin();
};

#endif