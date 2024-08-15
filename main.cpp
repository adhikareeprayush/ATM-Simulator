//ATM SIMULATOR
// USER CLASS
// VIEW, WITHDRAW, DEPOSIT, CHANGE PIN
// CHECK USER PIN, BALANCE CHECK IF TRANSACTION IS POSSIBLE OR NOT, HISTORY MAINTAINANCE


#include<iostream>
#include<vector>
#include<string>
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
        void addUser(const User& user){
            users.push_back(user);
        }
        User* findUser(const string& accountNumber){
            for(auto& user: users)
            {
                if(user.getAccountNumber() == accountNumber)
                    return &user;
            }
            return nullptr;
        }
        bool login(const string& accountNumber, const string& pinNumber)
        {
            currentUser = findUser(accountNumber);
            if(currentUser && currentUser->checkPin(pinNumber))
            {
                cout<< "LOGIN SUCCESSFUL. Welcome, " << currentUser->getName() << "!" << endl;
                return true;
            }
            else{
                cout<< "Login Failed! Incorrect Account Number or PIN" <<endl;
                return false;
            }
        }
        void logout()
        {
            currentUser = nullptr;
            std::cout << "Logged Out Successfully!"<<endl;
        }
        void performTransaction()
        {
            if(!currentUser)
            {
                cout<<"No User Logged in!" <<endl;
                return;
            }

            int choice;
            do{
                cout << "\nATM MENU:\n";
                cout << "1. View Balance:\n";
                cout << "2. Deposit Money\n";
                cout << "3. Withdraw Money\n";
                cout << "4. Change PIN\n";
                cout << "5. Logout\n";
                cout<<"ENTER YOUR CHOICE: ";
                cin>>choice;

                switch(choice)
                {
                case 1:
                    cout<< "Current Balance $" << currentUser->getBalance() << endl;
                    break;
                case 2:
                {
                    double amount;
                    cout<< "Enter the amount to deposit: ";
                    cin >> amount;
                    currentUser->deposit(amount);
                    break;
                }
                case 3:
                {
                    double amount;
                    cout<< "Enter the amount to withdraw: ";
                    cin >> amount;
                    currentUser->withdraw(amount);
                    break;
                }
                case 4:{
                    string newPin;;
                    cout<<"Enter new PIN:";
                    cin >> newPin;
                    currentUser->changePin(newPin);
                    break;
                }
                case 5:
                    logout();
                    break;
                default:
                    cout<< "Invalid Choice. Please Try Again" <<endl;
                }

            }while(choice != 5);
        }
};

int main()
{
    ATM atm;

    atm.addUser(User("John Doe", "123456789", "1234", 1000.00));
    atm.addUser(User("Jane Smith", "987654321", "5678", 500.00));

    std::string accountNumber, pin;

    std::cout << "Enter account number: ";
    std::cin >> accountNumber;
    std::cout << "Enter PIN: ";
    std::cin >> pin;

    if (atm.login(accountNumber, pin)) {
        atm.performTransaction();
    }
    return 0;
}