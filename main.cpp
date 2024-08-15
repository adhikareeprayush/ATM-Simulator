//ATM SIMULATOR
// USER CLASS
// VIEW, WITHDRAW, DEPOSIT, CHANGE PIN
// CHECK USER PIN, BALANCE CHECK IF TRANSACTION IS POSSIBLE OR NOT, HISTORY MAINTAINANCE


#include<iostream>
#include<vector>
using namespace std;

class User{
    private:
        string name;
        string accountNumber;
        string pin;
        double balance;
    public:
        bool checkPin(string pinNumber);
        bool deposit(double amount);
        bool withdraw(double withdrawBalance);
        double getBalance();
        bool changePin(string& pinNumber);
};

class ATM{
    private:
        vector<User> users;
        User* currentUser = nullptr;
    public:
        void addUser(const User& user);
        User* findUser(const string& accountNumber);
        bool login(const string& accountNumber, const string& pinNumber);
        void logout();
        void performTransaction();
};

int main()
{
    return 0;
}