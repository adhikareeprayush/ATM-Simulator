#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include <iomanip>  // For formatting
#include <cstdlib>  // For system("clear") or system("cls") depending on the OS

using namespace std;

// function to clear the screen 
void clearScreen() {
    #ifdef _WIN32
    system("cls");
    #else
        system("clear");
    #endif
}

void enterToContinue() {
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

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
            return true;
        }

        string getName(){
            return name;
        }

        string getAccountNumber()
        {
            return accountNumber;
        }

        string getPin()
        {
            return pin;
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
            ifstream file(filename);
            if (!file) {
                cerr << "Error opening file: " << filename << endl;
                return;
            }

            string line;
            // Skip the first header line
            getline(file, line);

            while (getline(file, line)) {
                stringstream ss(line);
                string name, accountNumber, pin, balanceStr;
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

                try {
                    balance = stod(balanceStr);
                } catch (const invalid_argument& e) {
                    cerr << "Invalid balance format: " << balanceStr << " in line: " << line << std::endl;
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
            //save and write the changes to the file
            ofstream file("../user_cred.txt");
            if (!file) {
                cerr << "Error opening file: " << "../user_cred.txt" << endl;
                return;
            }
            file << "Name,Account Number,PIN,Balance\n";
            for(auto& user: users)
            {
                file << user.getName() << "," << user.getAccountNumber() << "," << user.getPin() << "," << user.getBalance() <<
                ";" << "\n";
            }
            file.close();


            currentUser = nullptr;
            std::cout << "Logged Out Successfully!"<<endl;
        }
        
        void performTransaction() {
        if (!currentUser) {
            cout << "No User Logged in!" << endl;
            return;
        }

        int choice;
        do {
            clearScreen();

            // Display user information at the top
            cout << left << setw(30) << "Name: " + currentUser->getName()
                << setw(30) << "Account Number: " + currentUser->getAccountNumber()
                << "Current Balance: $" << fixed << setprecision(2) << currentUser->getBalance() << endl;

            // Display a separator
            cout << string(80, '=') << endl;

            // Display the ATM menu
            cout << "\nATM MENU:\n";
            cout << "1. View Balance\n";
            cout << "2. Deposit Money\n";
            cout << "3. Withdraw Money\n";
            cout << "4. Change PIN\n";
            cout << "5. Logout\n";
            cout << "\nENTER YOUR CHOICE: ";
            cin >> choice;

            // Handle the user's choice
            switch (choice) {
                case 1:
                    cout << "\nYour Current Balance: $" << currentUser->getBalance() << endl;
                    enterToContinue();
                    break;
                case 2: {
                    double amount;
                    cout << "\nEnter the amount to deposit: ";
                    cin >> amount;
                    currentUser->deposit(amount);
                    enterToContinue();
                    break;
                }
                case 3: {
                    double amount;
                    cout << "\nEnter the amount to withdraw: ";
                    cin >> amount;
                    currentUser->withdraw(amount);
                    enterToContinue();
                    break;
                }
                case 4: {
                    string newPin;
                    cout << "\nEnter new PIN: ";
                    cin >> newPin;
                    currentUser->changePin(newPin);
                    enterToContinue();
                    break;
                }
                case 5:
                    logout();
                    enterToContinue();
                    break;
                default:
                    cout << "\nInvalid Choice. Please Try Again." << endl;
                    enterToContinue();
            }

        } while (choice != 5);
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
    ATM atm("../user_cred.csv");

    string accountNumber, pin;
    cout<< "Enter Account Number: ";
    cin >> accountNumber;
    cout<< "Enter PIN: ";
    cin >> pin;

    if(atm.login(accountNumber, pin))
    {
        atm.performTransaction();
    }

    return 0;
}