#include"../include/User.h"
#include<iostream>

User::User(const std::string& name,const std::string& accountNumber, const std::string& pin,const double& balance) : name(name), accountNumber(accountNumber),
    pin(pin), balance(balance){};

bool User::checkPin(const std::string& pinNumber)
{
    if(pin==pinNumber)
    {
        return true;
    }
    return false;
}

void User::deposit(double amount)
{
    balance+=amount;
    std::cout<< "Your new Balance is: " << balance <<std::endl;
}

bool User::withdraw(double amount)
{
    if(amount <=balance)
    {
        balance-=amount;
        std::cout<< "Withdrawal Successful! Your new Balance is: " << balance <<std::endl;
        return true;
    }
    else{
        std::cout<<"Insufficient Balance" <<std::endl;
        return false;
    }
}

double User::getBalance()
{
    return balance;
}

bool User::changePin(const std::string& pinNumber)
{
    pin = pinNumber;
    std::cout<<"PIN Changed Successfully"<<std::endl;
    return true;
}

std::string User::getName()
{
    return name;
}

std::string User::getAccountNumber()
{
    return accountNumber;
}

std::string User::getPin(){
    return pin;
}
