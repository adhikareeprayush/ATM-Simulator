//ATM SIMULATOR
// USER CLASS
// VIEW, WITHDRAW, DEPOSIT, CHANGE PIN
// CHECK USER PIN, BALANCE CHECK IF TRANSACTION IS POSSIBLE OR NOT, HISTORY MAINTAINANCE


#include<iostream>
using namespace std;

class User{
    private:
        string name;
        string accountNumber;
        int pin[4];
        double balance;
    public:
        bool checkPin(int pinNum[]);
        bool deposit(double amount);
        bool withdraw(double withdrawBalance);
        double getBalance();
        bool changePin(int newPin[]);
};

// class ATM: public User{
//     private:
        

// }

int main()
{
    return 0;
}