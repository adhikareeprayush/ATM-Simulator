#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>

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
        ATM(const std::string& filename) {
            loadUsersFromFile(filename);
        }

        void loadUsersFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    // Skip the first header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        // Remove the trailing semicolon if present
        if (line.back() == ';') {
            line.pop_back();
        }

        std::stringstream ss(line);
        std::string name, accountNumber, pin, balanceStr;
        double balance;

        std::getline(ss, name, ',');
        std::getline(ss, accountNumber, ',');
        std::getline(ss, pin, ',');
        std::getline(ss, balanceStr, ',');

        // Trim any extra whitespace (optional)
        name.erase(0, name.find_first_not_of(" \t"));
        name.erase(name.find_last_not_of(" \t") + 1);
        accountNumber.erase(0, accountNumber.find_first_not_of(" \t"));
        accountNumber.erase(accountNumber.find_last_not_of(" \t") + 1);
        pin.erase(0, pin.find_first_not_of(" \t"));
        pin.erase(pin.find_last_not_of(" \t") + 1);
        balanceStr.erase(0, balanceStr.find_first_not_of(" \t"));
        balanceStr.erase(balanceStr.find_last_not_of(" \t") + 1);

        try {
            balance = std::stod(balanceStr);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid balance format: " << balanceStr << " in line: " << line << std::endl;
            continue;
        }

        users.push_back(User(name, accountNumber, pin, balance));
    }

    file.close();
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

        void getUsers()
        {
            for(auto& user: users)
            {
                cout<< user.getName() << endl;
            }
        }
};

int main()
{
    ATM atm("user_cred.txt");

    // string accountNumber, pin;
    // cout<< "Enter the account number: "; nice note
    // cin>>accountNumber;
    // cout<<"Enter the PIN: ";
    // cin>>pin;

    // if (atm.login(accountNumber, pin)) {
    //     atm.performTransaction();
    // }
    // else{
    //     cout<<"Invalid Credentials!"<<endl;
    // }
    return 0;
}