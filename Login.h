#ifndef Login_h
#define Login_h
#include <string>
#include "supportfunction.h"
using namespace std;


void setCurrentAccount(User account);
void getCurrentAccount(User &account);
void getAccounts(User* &accounts);
User login(string username, string password, User* accounts);
void readPassword(std::string &password, int x, int y);
void Login();
void changePassword();

#endif // Login_h
