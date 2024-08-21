#ifndef ATM_H
#define ATM_H

#include<vector>
#include<string>
#include"User.h"

class ATM{
    private:
        std::vector<User> users;
        User* currentUser = nullptr;
    public:
        ATM(const std::string& filename);
        User* findUser(const std::string& accountNumber);
        void updateFile();
        void loadUsersFromFile(const std::string& filename);
        bool login(const std::string& accountNumber, const std::string& pinNumber);
        void logout();
        void performTransaction(const std::string& accountNumber);
        void getUsers();
        bool userExists(const std::string& accountNumber);
        void addUser(const User& user);
};

#endif