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
        User(string name,string accountNumber, string pin, double balance) : name(name), accountNumber(accountNumber),
        pin(pin), balance(balance){};
        bool checkPin(string pinNumber)
        {
            return pin == pinNumber;
            // match true else false
        }
        void deposit(double amount)
        {
            balance+=amount;
            cout<< "Your new Balance is: " << balance <<endl;
        }
        bool withdraw(double amount)
        {
            if(amount <=balance)
            {
                balance-=amount;
                cout<< "Withdrawal Successful! Your new Balance is: " << balance <<endl;
                return true;
            }
            else{
                cout<<"Insufficient Balance" <<endl;
                return false;
            }
        }
        double getBalance()
        {
            return balance;
        }
        bool changePin(const string& pinNumber){
            pin = pinNumber;
            cout<< "PIN Changed Successfully" <<endl;
        }
        string getName(){
            return name;
        }
        string getAccountNumber()
        {
            return accountNumber;
        }
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