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
    std::cout<< CYAN << "Your new Balance is: " << balance <<std::endl <<RESET;
}

bool User::withdraw(double amount)
{
    if(amount <=balance)
    {
        balance-=amount;
        std::cout<< GREEN <<"Withdrawal Successful! Your new Balance is: " << balance <<std::endl <<RESET;
        return true;
    }
    else{
        std::cout<<RED<<"Insufficient Balance" <<std::endl << RESET;
        return false;
    }
}

double User::getBalance()
{
    return balance;
}

bool User::changePin(const std::string& pinNumber)
{
    if(pinNumber.length() !=4 )
    {
        std::cout <<RED << "The PIN should contain only 4 Digits!"<<RESET <<std::endl;
        return false;
    } 
    pin = pinNumber;
    std::cout<<GREEN<<"PIN Changed Successfully"<<std::endl<<GREEN;
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
