#ifndef UTILITIES_H
#define UTILITIES_H

#include<string>
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"

#define USER_CRED "user_cred.csv"

void clearScreen();
int getValidOption();
void enterToContinue();
bool isPinValid(const std::string& pinNumber, const std::string& confirmPIN);
std::string generateAccountNumber();
void login();
void userRegister();

#endif