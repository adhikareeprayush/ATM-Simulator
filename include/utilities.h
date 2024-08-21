#ifndef UTILITIES_H
#define UTILITIES_H

#include<string>

#define USER_CRED "user_cred.csv"

void clearScreen();
int getValidOption();
void enterToContinue();
std::string generateAccountNumber();
void login();
void userRegister();

#endif